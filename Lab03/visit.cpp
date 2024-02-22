#include <iostream> 
#include <utility> 
#include <vector> 
#include <map> 
#include <queue> 
#include <bits/stdc++.h> 

using namespace std;

#define INF 0xf3f3f3f // Infinite distance value

void dijkstra(vector<vector<pair<int,int> > > &adj, vector<int> &distance_to, vector<int> &previous, int src){
    priority_queue<pair<int,int>, vector<pair<int,int> >, greater<pair<int,int> > > pq; // Priority queue for Dijkstra's algorithm

    pq.push(make_pair(0, src)); // Push the src node with distance 0
    distance_to[src] = 0; // Set the distance to the src node as 0

    // Dijkstra's algorithm
    while(!pq.empty()){
        int u = pq.top().second; // Get the node with the minimum distance
        pq.pop(); // Remove the node from the priority queue

        vector<pair<int,int> >::iterator it; // Iterator for the adjacency list of the current node
        for(it = adj[u].begin(); it != adj[u].end(); ++it){
            int v = (*it).first; // Get the neighbor node
            int d = (*it).second; // Get the distance to the neighbor node

            if(distance_to[v] > distance_to[u] + d){ // If a shorter path is found
                distance_to[v] = distance_to[u] + d; // Update the distance to the neighbor node
                previous[v] = u; // Update the previous of the neighbor node
                pq.push(make_pair(distance_to[v], v)); // Push the neighbor node into the priority queue
            }
        }
    }
}

int findShortestPath(vector<vector<pair<int,int> > > &adj, vector<int> &distance_to, vector<int> &previous, int src, int dest, int t, map<pair<int,int>, int> &edges, vector<pair<int, pair<int,int> > > &not_available_cities) {
    int n = adj.size();
    vector<bool> cities_available(n,false); // Boolean array to track the presence of cities

    int curr = src-1; 
    int count = t; 
    int l = 0;
    cities_available[not_available_cities[l].second.first] = true; // Mark the first not_avalable_cities city as visited
    cities_available[not_available_cities[l].second.second] = true; // Mark the second not_avalable_cities city as visited
    bool reached_destination = false; // Flag to track if the dest is reached_destination

    // Main loop to find the shortest path!
    while(curr != dest-1){
        while(count >= not_available_cities[l].first && count < not_available_cities[l+1].first && !reached_destination){
            if(cities_available[curr] && cities_available[previous[curr]]){ // If the current node and its previous are visited
                vector<pair<int,int> >::iterator iter;
                iter = adj[curr].begin();
                int temp, saved_node;
                if(iter->first == previous[curr]){ // If the first neighbor is the previous
                    iter++;
                    if(iter == adj[curr].end() and curr == dest-1) {
                        reached_destination = true; 
                        continue;
                    }
                }
                // cout << "Iter: " << iter->first << '\n';
                // cout << "Previous: " << previous[curr] << '\n';
                temp = distance_to[iter->first];
                count = not_available_cities[l+1].first;
                count += edges[{curr, previous[curr]}];
                curr = previous[curr];
                if(curr == dest-1) reached_destination = true; 
                continue;
            }
            else{
                count += edges[{curr, previous[curr]}];
                curr = previous[curr];
                if(curr == dest-1) reached_destination = true;
            }
        }
        if(reached_destination){
            break;
        }
        else{
            cities_available[not_available_cities[l].second.first] = false;
            l++;
            cities_available[not_available_cities[l].second.second] = true;
            continue;
        }
    }

    //cout << "Count: " << count << '\n';
    if(curr != dest-1){
        while(curr != dest-1){
            count += edges[{curr, previous[curr]}];
            curr = previous[curr];
        }
        return count - t; // Return the time taken to reach the dest
    }
    else{
        return count - t; // Return the time taken to reach the dest
    }
}

int main(){
    // Read the input:
    // First n and m 
    // Then src, dest, t, president
    int n, m, t, president, src, dest;
    cin >> n >> m; 
    cin >> src >> dest >> t >> president; // Read 
    vector<vector<pair<int,int> > > adj(n); // Adjacency list for the graph

    // Initializing
    vector<int> distance_to(n, INF); 
    vector<int> president_cities; 
    
    vector<int> previous(n,-1); // Previous

    map<pair<int,int>, int> edges; // Edges

    for(int i = 0; i < president; i++){
        int iter;
        cin >> iter; // Read the president city
        president_cities.push_back(iter-1); // Store the president city in the vector
    }

    // Create the graph
    for(int i = 0; i < m; i++){
        int u,v,d;
        cin >> u >> v >> d; 
        edges[{u-1,v-1}] = d; 
        edges[{v-1,u-1}] = d; 

        adj[u-1].push_back({v-1, d}); 
        adj[v-1].push_back({u-1, d}); 
    }

    // Run Dijkstra's algorithm to find the distance to each node
    dijkstra(adj, distance_to, previous, dest-1); 

    // FIND SHORTEST TIME

    vector<pair<int, pair<int,int> > > not_available_cities(president); 
    vector<int>::iterator iter,iter2;
    iter = president_cities.begin();
    iter2 = iter+1;
    int l = 0;
    int minute_counter = 0;

    while(iter2 != president_cities.end()){
        int counter = *iter;
        int counter_ = *iter2;
        // Store the not_available_cities cities and their time
        not_available_cities[l] = {minute_counter, {counter,counter_}}; 
        minute_counter += edges[{counter,counter_}]; 

        iter++; iter2++; l++;

        // cout << "Minute counter: " << minute_counter << '\n';
    }
    not_available_cities[l] = {minute_counter, {*iter, -1}}; // Store the last not_available_cities city

    int shortest_time = findShortestPath(adj, distance_to, previous, src, dest, t, edges, not_available_cities);
    cout << shortest_time << endl; // Print the shortest time taken to reach the dest

    return 0;
}
