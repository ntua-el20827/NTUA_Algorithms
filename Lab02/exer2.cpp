#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <queue>
#include <limits>

using namespace std;
const int INF = std::numeric_limits<int>::max();

void addEdge(vector<int> adj[], int u, int v) 
{
    adj[u].push_back(v);
    adj[v].push_back(u);
}


// Purpose of this function is to fill prev and dist_to arrays
void Dijkstra(int *prev, int *dist_to, vector<int> adj[], int *dist_edge, int N){
    
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    dist_to[0] = 0; // Needed
    pq.push({0, 0});

    while (!pq.empty()){
        int u = pq.top().second;
        pq.pop();

        for (auto v : adj[u]) // for all neighbors of u
        {
            int weight = dist_edge[u * N + v];

            if (dist_to[u] + weight < dist_to[v])
            {
                dist_to[v] = dist_to[u] + weight;
                prev[v] = u;
                pq.push({dist_to[v], v});
            }
        }
    }
}

void Relay(int *prev, int v, bool *visited, vector<int> adj[], int *dist_to, int *dist_edge, int *p, int *s, int *min_time, int N)  
{  
    visited[v] = true;  
    int min_sum;  
    // Base Case 
    if (v == 0){  
        min_sum = 0;  
    }  
    else{
        // Calculate the minimum time to reach the current node     
        min_sum = p[v] + s[v] * dist_to[v];   

        // Calculate the cost of the edge between the current node and its parent
        int cost;  
        int node = v; 
        if (prev[node] < node)  
            cost = dist_edge[prev[node] * N + node];  
        else  
            cost = dist_edge[node * N + prev[node]];  
  
        int curr_cost = cost;  
        node = prev[node];  

        // Explore the tree up to V1, to calculate min time
        while (prev[node] != -1)  
        {  
  
            int temp = p[v] + curr_cost * s[v] + min_time[node];  
  
            if (prev[node] < node)  // Make the Choise (Same or different sleigh)
                cost = dist_edge[prev[node] * N + node];  
            else  
                cost = dist_edge[node * N + prev[node]];  
  
            curr_cost += cost;  
            if (temp < min_sum)  
                min_sum = temp;  
            node = prev[node];  
        }  
    } 

    //Store the min time for the current node
    min_time[v] = min_sum;  
    for (auto i = adj[v].begin(); i != adj[v].end(); ++i)  
    {  
        if (!visited[*i])  
        {  
            Relay(prev, *i, visited, adj, dist_to, dist_edge, p, s, min_time, N);  
        }  
    }  
}  

int main()
{
    // Reading Inputs
    int N;
    cin >> N;

    // Represent Values Pi and Si with int arrays
    int *p = new int[N];
    int *s = new int[N];
    p[0] = 0;
    s[0] = 0;
    // Represent the Graph with an array of vectors of pairs of int values
    vector<int> adj[N];

    // We will use a one-dimensional array to represent the distance of the edges. We also initialize all elements to 0
    int *dist_edge = new int[N*N]{0};

    for (int i = 1; i < N; i++){
        int Vi, Vj, Dij;
        cin >> Vi >> Vj >> Dij;
        Vi -= 1;
        Vj -= 1;

        addEdge(adj, Vi, Vj);
        if (Vi < Vj)
        {
            dist_edge[Vi * N + Vj] = Dij;
        }
        else
        {
            dist_edge[Vj * N + Vi] = Dij;
        }
    }

    for (int i = 0; i < N-1; i++){
        cin >> p[i+1] >> s[i+1];
    }

    // We also need to initiallize some ancillary arrayes.
    int *prev = new int[N]; // for previous nodes
    prev[0] = -1;
    bool *visited = new bool[N]{false}; // if this node is visited
    int *dist_to = new int[N]; // distance to V1
    dist_to[0] = 0;
    
    // Using Dijkstra to fill dist_to and prev arrays. Dijkstra is prefered because of the structure of our graph (tree)
    fill(dist_to, dist_to + N, INF);
    Dijkstra(prev, dist_to, adj,dist_edge, N);

    int *shortest_paths = new int[N];
    shortest_paths[0] = 0;
    for (int i = 0; i < N; i++) // Make visited false for every node
        visited[i] = false;

    // Find shortest paths
    Relay(prev, 0, visited, adj, dist_to, dist_edge, p, s, shortest_paths, N);

    for (int i = 1; i < N-1; i++)
        cout << shortest_paths[i] << " ";
    cout << shortest_paths[N-1] << endl;

    // Deallocate Memory
    delete[] prev;
    delete[] p;
    delete[] s;
    delete[] dist_edge;
    delete[] visited;
    delete[] dist_to;
    delete[] shortest_paths;

    return 0;
}

