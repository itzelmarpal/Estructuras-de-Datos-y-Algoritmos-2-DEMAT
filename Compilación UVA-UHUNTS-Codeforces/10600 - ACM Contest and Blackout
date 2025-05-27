#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Disjoint set data struture
class DSU {
    vector<int> parent, rank;

public:
    DSU(int n) {
        parent.resize(n);
        rank.resize(n);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            rank[i] = 1;
        }
    }

    int find(int i) {
        return (parent[i] == i) ? i : (parent[i] = find(parent[i]));
    }

    void unite(int x, int y) {
        int s1 = find(x), s2 = find(y);
        if (s1 != s2) {
            if (rank[s1] < rank[s2]) parent[s1] = s2;
            else if (rank[s1] > rank[s2]) parent[s2] = s1;
            else parent[s2] = s1, rank[s1]++;
        }
    }
};

bool comparator(vector<int> &a,vector<int> &b){
    if(a[2]<=b[2])return true;
    return false;
}

vector<int> kruskal_first_secondMST(int V, vector<vector<int>> &edges) {
    vector <int> ans;
    // Sort all edges
    sort(edges.begin(), edges.end(),comparator);

    // Traverse edges in sorted order for MST
    DSU dsu_mst(V);
    int cost_mst = 0, count_mst = 0;
    vector<int> mstEdgesIndices; // Store indices of edges in MST

    for (int i = 0; i < edges.size(); i++) {
        int x = edges[i][0], y = edges[i][1], w = edges[i][2];

        // Make sure that there is no cycle
        if (dsu_mst.find(x) != dsu_mst.find(y)) {
            dsu_mst.unite(x, y);
            cost_mst += w;
            mstEdgesIndices.push_back(i);
            if (++count_mst == V - 1) break;
        }
    }
    ans.push_back(cost_mst);

    int res = INT_MAX;

    // Try removing each edge of the MST and find the new MST cost
    for(int removed_edge_index : mstEdgesIndices) {
        DSU dsu_second(V);
        int cost_second = 0, count_second = 0;

        for (int j = 0; j < edges.size(); j++) {
            if (j == removed_edge_index) continue; // Skip the removed edge

            int x = edges[j][0], y = edges[j][1], w = edges[j][2];

            if (dsu_second.find(x) != dsu_second.find(y)) {
                dsu_second.unite(x, y);
                cost_second += w;
                if (++count_second == V - 1) break;
            }
        }

        if (count_second == V - 1) {
            res = min(res, cost_second);
        }
    }
    ans.push_back(res);
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t; cin >> t;
    for(int i = 0; i < t; i++){
        int n, m; cin >> n >> m;
        vector<vector<int>> edges;
        for(int j = 0; j < m; j++){
            int source, destination, cost;
            cin >> source >> destination >> cost;
            edges.push_back({source-1, destination-1, cost});
        }
        vector<int> answer = kruskal_first_secondMST(n, edges);
        cout << answer[0] << " " << answer[1] << endl;
    }
    return 0;
}
