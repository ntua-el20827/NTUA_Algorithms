#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <vector>

using namespace std;

// Problem:
/*
I have N cities and M highways. Each highway connects two cities.
Travelling from one city to another is instantaneous.
Each highway needs repair after a certain moment.
The ith highway needs repair after t[i] time units.
After this time the highway is closed.
I have up to K repairs available.
Every repair is: 1. Fixing a highway or 2. Building a new highway.
My goal is to maximize the last time T* that makes it possible for every citizen 
to travel to their work.
 (The connectivity of the country is the same with the connectivity in the time 0)
*/

// Input:
// N M K
// For every i from 1 to M: u[i] v[i] t[i]

// Output:
// T* that every citizen can travel to their work.
// If the K repairs can ensure infinite time of relaxation for the citizens, print "infinity"

struct Edge
{
    int u,v,t;
};

bool compare(Edge a, Edge b) {
    return a.t < b.t;
}

bool isConnected(int N, const vector<Edge>& edges) {
    vector<vector<int>> adjList(N + 1);
    for (const auto& edge : edges) {
        adjList[edge.u].push_back(edge.v);
        adjList[edge.v].push_back(edge.u);
    }

    vector<bool> visited(N + 1, false);
    queue<int> q;
    q.push(1); // Start BFS from city 1

    while (!q.empty()) {
        int currCity = q.front();
        q.pop();

        // Mark the city as visited here, before checking neighbors
        visited[currCity] = true;

        for (int neighbor : adjList[currCity]) {
            if (!visited[neighbor]) {
                q.push(neighbor);
            }
        }
    }

    // Check if all cities are visited
    for (int i = 1; i <= N; i++) {
        if (!visited[i]) {
            return false;
        }
    }

    return true;
}



int main() {
    int N, M, K;
    cin >> N >> M >> K;
    vector<Edge> edges;
    // vector<Edge> new_edges;
    int u, v, t;
    for (int i = 0; i < M; i++) {
        cin >> u >> v >> t;
        edges.push_back({u, v, t});
    }

    // Sort the edges by their time of repair
    sort(edges.begin(), edges.end(), compare);
    // Iterate over the sorted edges
    // for (int i=0; i<edges.size(); i++) {
    //     // cout << edges[i].u << " " << edges[i].v << " " << edges[i].t << endl;
    // }
    int i=0;
    int deleted = 0;
    bool edge_needed;
    while(K!=0 and i<M)
    {
        // for each edge check if it needed in the graph in order to be connected, using DFS
        // I want to give to isConnected all the edges except the current one
        // Use malloc to create new_edges
        //new_edges.clear();
        //cout << "i: " << i << endl;
        // for (int j=0; j<edges.size(); j++) {
        //     if (j!=i-deleted) {
        //         new_edges.push_back(edges[j]);
        //         //cout << "Edge added: " << edges[j].t << endl;
        //     }
        // }
        // edge_needed = isConnected(N, new_edges);
        int u = edges[i-deleted].u;
        int v = edges[i-deleted].v;
        int t = edges[i-deleted].t;
        edges.erase(edges.begin()+i-deleted);
        edge_needed = isConnected(N, edges); 
               
        // Delete new_edges
        // cout << "Edge needed: " << edge_needed << endl;
        if (edge_needed){
            //K = K-1;
            //int it = edges.begin()+i-deleted;
            //cout << "Edge deleted: " << edges[i-deleted].t << endl;
            //edges.erase(edges.begin()+i-deleted);
            deleted++;
            i++;
            continue;
        }
        // If the edge is not needed in the coherence of the graph, Check again for the next edge in the new graph
        // The new graph will not contain the current edge
        // edges.erase(edges.begin()+i-deleted);
        edges.insert(edges.begin()+i-deleted, {u, v, t});
        K = K-1;
        // deleted++;
        i++;
    }
    // print all edges
    //cout <<"Edges: "<<endl;
    if (K==0) {
        cout << edges[i-deleted].t << endl;
    }
    else {
        cout << "infinity" << endl;
    }
    return 0;
}