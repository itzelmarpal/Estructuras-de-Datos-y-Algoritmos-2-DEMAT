#include <bits/stdc++.h>
using namespace std;
/*
    Itzel Berenice Martinez Palacios
    Tarea 6 - Flujos
    Drumuri2
    Estructuras de Datos y Algoritmos 2
*/

struct Edge {
    long long c; // Capacidad de la arista
    long long f; // Flujo actual de la arista
    int to;      // Nodo destino de la arista

    Edge(long long capacity, long long flow, int destination)
        : c(capacity), f(flow), to(destination) {}
};

class FordFulkerson {
private:

    vector<vector<pair<int, long long>>> g; // Grafo (to, capacity)
    vector<Edge> edges;                     // Lista de aristas (incluyendo las inversas)
    vector<vector<int>> eIndexes;           // Índices de aristas salientes de cada nodo

    // Inicializa las estructuras de datos
    void init() {
        edges.clear();
        eIndexes.clear();
        eIndexes.resize(g.size());

        for (int i = 0; i < g.size(); i++) {
            for (int j = 0; j < g[i].size(); j++) {
                // Añadir arista original
                edges.push_back({g[i][j].second, 0, g[i][j].first});
                // Añadir arista inversa
                edges.push_back({0, 0, i});

                // Guardar índices de las aristas
                eIndexes[i].push_back(edges.size() - 2); // Índice de la arista original
                eIndexes[g[i][j].first].push_back(edges.size() - 1); // Índice de la arista inversa
            }
        }
    }

    // Encuentra un camino de aumento y actualiza el flujo
    bool findAndUpdate(int s, int t, long long &flow) {
        queue<int> pending; // Cola para BFS
        vector<pair<int, int>> from(g.size(), {-1, -1}); // Para rastrear el camino
        pending.push(s);
        from[s] = {s, -1};
        bool found = false;

        // BFS para encontrar un camino de aumento
        while (pending.size() && (!found)) {
            int u = pending.front();
            pending.pop();

            for (int i = 0; i < eIndexes[u].size(); i++) {
                int eI = eIndexes[u][i]; // Índice de la arista
                if ((edges[eI].c > edges[eI].f) && (from[edges[eI].to].first == -1)) {
                    from[edges[eI].to] = {u, eI};
                    pending.push(edges[eI].to);

                    if (edges[eI].to == t) {
                        found = true;
                    }
                }
            }
        }

        if (!found) return false; // No se encontró un camino de aumento

        // Encontrar la capacidad mínima del camino de aumento
        long long uFlow = LLONG_MAX;
        int current = t;
        while (current != s) {
            uFlow = min(uFlow, edges[from[current].second].c - edges[from[current].second].f);
            current = from[current].first;
        }

        // Actualizar el flujo en el camino de aumento
        current = t;
        while (current != s) {
            edges[from[current].second].f += uFlow; // Aumentar flujo en la arista original
            edges[from[current].second ^ 1].f -= uFlow; // Disminuir flujo en la arista inversa
            current = from[current].first;
        }
        flow += uFlow; // Actualizar el flujo total
        return true;
    }

public:
    // Constructor
    FordFulkerson(vector<vector<pair<int, long long>>> &graph) : g(graph) {}

    // Calcular el flujo máximo desde s hasta t
    long long findMaxFlow(int s, int t) {
        init();
        long long flow = 0;
        while (findAndUpdate(s, t, flow)){} // Mientras haya caminos de aumento
        return flow;
    }
};

int vtx_in(int i){ // Indice del nodo i tipo in
    return 2*i+2;
}
int vtx_out(int i){ // Indice del nodo i tipo out
    return 2*i+1;
}

// DFS recursiva para terminar de llenar el grafo de flujos con los vertices out y vertices in
void DFS_TC(int u, int v, vector<vector<pair<int, long long>>> &graph, vector<vector<int>> &adj, vector<vector<bool>> &visited) {
    if (visited[u][v]) return;
    visited[u][v] = true;
    if(u != v){
        graph[vtx_out(u)].push_back({vtx_in(v),1});
    }
    for (int next : adj[v]) { 
        DFS_TC(u, next, graph, adj, visited);
    }
}

int main() {
    ifstream fin("drumuri2.in");
    ofstream fout("drumuri2.out");
    int n,m;
    fin >> n >> m;
    vector<vector<int>> adj(n);
    // Leemos las aristas del grafo.
    for(int i = 0; i < m; i++){
        int u, v;
        fin >> u >> v;
        adj[u-1].push_back(v-1); // Indexamos en cero
    }
    // Se crea el grafo de flujos para resolver el problema del minimo recubrimiento de caminos
    vector<vector<pair<int, long long>>> graph(2*n+2);

    // Unimos el nodo fuente a todos los nodos out con capacidad 1
    for(int i = 0; i < n; i++) graph[0].push_back({vtx_out(i), 1});

    // Unimos todos los nodos in al nodo sumidero con capacidad 1
    for(int i = 0; i < n; i++) graph[vtx_in(i)].push_back({2*n+1, 1});
    vector<vector<bool>> visited(n, vector<bool>(n, false));
    // Unir nodos out con nodos in
    for (int i = 0; i < n; i++)
        DFS_TC(i, i, graph, adj, visited);

    FordFulkerson ff(graph);

    // Calculamos el flujo maximo en el grafo construido.
    long long maxFlow = ff.findMaxFlow(0, 2*n+1);
    int result = n-maxFlow;
    fout << result << endl;
    
    fin.close();
    fout.close();

    return 0;
}