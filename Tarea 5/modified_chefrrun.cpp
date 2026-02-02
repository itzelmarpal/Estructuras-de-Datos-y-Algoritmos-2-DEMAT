#include <iostream>
#include <vector>
#include <queue> 
using namespace std;
#define ull unsigned long long

/*
    Realizamos el mismo algoritmo que en chefrrun.cpp, pero en lugar de utilizar
    una pila, hacemos uso de una cola utilizando el mismo grafo sin invertir, en
    lugar de utilizar la funcion top(), utilizamos front().
    Tambien en el otro codigo adjT era un vector de vectores, ya que al invertir
    el grafo, este podria tener mas de un nodo que apunten al mismo nodo, aqui
    esto no pasa y por lo tanto mandamos solamente un vector.
*/

class chefrrun{
    public:
    void dfs(ull node, vector<bool>& visited, const
        vector<ull>& adj, queue<ull>& queue_dfs){
            if(visited[node]) return;
            visited[node] = 1;
            ull  next = adj[node];
            dfs(next, visited, adj, queue_dfs);
            queue_dfs.push(node);
    }
    void dfs1(ull node, vector<bool>& visited, const vector<ull>& adjT, ull& count){
        visited[node] = 1;
        count++;
        if(!visited[adjT[node]]){
            dfs1(adjT[node], visited, adjT, count);
        }
    }
    vector<ull> kosaraju(ull N, vector<ull>& adj){
        vector<bool> visited(N, false);
        queue<ull> queue_dfs;
        for(ull  i = 0; i < N; i++){
            if(!visited[i])
                dfs(i, visited, adj, queue_dfs);
        }
        fill(visited.begin(), visited.end(), false);
        vector<ull> scc_nodes;
        while(!queue_dfs.empty()){
            ull node = queue_dfs.front();
            queue_dfs.pop();
            if(!visited[node]){
                ull count = 0;
                dfs1(node, visited, adj, count);
                scc_nodes.push_back(count);
            }
        }
        return scc_nodes;
    }
};

int main(){
    ull T, N;
    cin >> T;
    for(ull i = 0; i < T; i++){
        cin >> N;
        vector <ull> adj(N);
        ull  count = 0;
        chefrrun problem;
        for(ull j = 0; j < N; j++){
            ull Ai;
            cin >> Ai;
            adj[j] = (j + Ai + 1) % N;
            if(adj[j] == j) count++;
        }
        vector <ull> kosa = problem.kosaraju(N, adj);
        for(ull sum : kosa){
            if (sum != 1) {
                count += sum;
            }
        }
        cout << count << endl;
    } 

    return 0; 
}