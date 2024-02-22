#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std;

struct Edge {
    int u;
    int v;
    int profit;
    int weight;
    double profitAdjusted; // Adjusted profit after subtracting c * weight
};

bool compareEdges(const Edge& e1, const Edge& e2) {
    return e1.profitAdjusted > e2.profitAdjusted;
}

int find(int x, int group[]) {
    if (group[x] != x) {
        group[x] = find(group[x], group);
    }
    return group[x];
}

void unite(int x, int y, int group[]) {
    group[find(x, group)] = find(y, group);
}

Edge* kruskal(Edge* edges, int n, int m) {
    Edge* mst = new Edge[n - 1];
    int* group = new int[n + 1];

    // Initialize group array
    iota(group, group + n, 0);

    // Sort edges based on profit-to-weight ratio
    sort(edges, edges + m, compareEdges);

    int mstIndex = 0;
    double lo = 0, hi = 1e4;  // Adjust the range based on the problem constraints

    // Binary search to find the maximum c
    while (hi - lo > 1e-10) {
        double mid = (lo + hi) / 2;

        for (int i = 0; i < m; i++) {
            edges[i].profitAdjusted = edges[i].profit - mid * edges[i].weight;
        }

        sort(edges, edges + m, compareEdges);
        for (int i = 0; i < m; i++) {
            edges[i].profitAdjusted = edges[i].profit;
        }
        for (int i = 0; i < m; i++) {
            int u = edges[i].u;
            int v = edges[i].v;

            if (find(u, group) != find(v, group)) {
                mst[mstIndex++] = edges[i];
                unite(u, v, group);
            }

            if (mstIndex == (n - 1)) {
                break;
            }
        }

        if (mstIndex == (n - 1)) {
            lo = mid;
        } else {
            hi = mid;
        }

        mstIndex = 0;
        iota(group, group + n, 0);
    }

    delete[] group;
    return mst;
}

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    int n, m;
    cin >> n >> m;

    Edge* edges = new Edge[m];

    for (int i = 0; i < m; ++i) {
        int u, v, profit, weight;
        cin >> u >> v >> profit >> weight;

        edges[i] = {u, v, profit, weight};
    }

    Edge* mst = kruskal(edges, n, m);
    delete[] edges;

    int totalProfit = 0;
    int totalWeight = 0;

    for (int i = 0; i < (n - 1); i++) {
        totalProfit += mst[i].profit;
        totalWeight += mst[i].weight;
    }

    delete[] mst;

    int gcd_n = gcd(totalProfit, totalWeight);
    cout << totalProfit / gcd_n << " " << totalWeight / gcd_n << endl;

    return 0;
}