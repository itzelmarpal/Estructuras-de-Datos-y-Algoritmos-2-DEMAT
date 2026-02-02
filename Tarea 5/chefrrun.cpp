#include <iostream>
#include <vector>
#include <stack> 
using namespace std;
#define ull unsigned long long

/*
    Tarea 5
    Algoritmo de Kosaraju
    Itzel Berenice Martinez Palacios
*/

class chefrrun{
    public:
    // Funcion recursiva dfs, que va llenando nuestra pila del kosaraju
    void dfs(ull node, vector<bool>& visited, const
        vector<ull>& adj, stack<ull>& stack_dfs){
            if(visited[node]) return;
            visited[node] = 1;
            ull next = adj[node];
            dfs(next, visited, adj, stack_dfs);
            stack_dfs.push(node);
    }
    void dfs1(ull node, vector<bool>& visited, const
        vector<vector<ull>>& adjT, ull& count){
            visited[node] = 1;
            count++; // Contamos la cantidad de elementos en cada scc
            for(ull next : adjT[node]){
                if(!visited[next]){
                    // Se hace el recorrido en el grafo inverso hasta que
                    // regresa a un nodo anteriormente visitado.
                    dfs1(next, visited, adjT, count);
                }
            }
    }
    vector<ull> kosaraju(ull N, vector<ull>& adj){
        vector<bool> visited(N, false); // Creamos un vector booleano de visitados
        stack<ull> stack_dfs; 
        for(ull  i = 0; i < N; i++){
            if(!visited[i]) // Realizamos la 1era DFS para obtener el camino del grafo.
                dfs(i, visited, adj, stack_dfs);
        }
        vector<vector<ull>> adjT(N); // Creamos un vector de vectores para el grafo inverso.
        // Llenamos el grafo inverso.
        for(ull i = 0; i < N; i++){
            ull next = adj[i];
            adjT[next].push_back(i);
        }
        // Reestablecemos nuestro vector de visitados a false.
        fill(visited.begin(), visited.end(), false);
        vector<ull> scc_nodes;
        while(!stack_dfs.empty()){
            ull node = stack_dfs.top();
            stack_dfs.pop();
            // Realizamos nuestra segunda dfs en donde recorremos el grafo inverso
            // y vamos obteniendo la cuenta de cajas magicas (nodos en un scc)
            if(!visited[node]){
                ull count = 0;
                dfs1(node, visited, adjT, count);
                // Aniadimos al vector scc_nodes la cantidad de cajas magicas en el scc actual
                scc_nodes.push_back(count); 
            }
        }
        return scc_nodes;
    }
};

int main(){
    ull T, N;
    cin >> T;
    // Se inician los casos de prueba
    for(ull i = 0; i < T; i++){
        cin >> N;
        vector <ull> adj(N);
        ull  count = 0;
        chefrrun problem;
        for(ull j = 0; j < N; j++){
            ull Ai;
            // Se lee la cantidad de sabor de cada caja.
            cin >> Ai;
            // Indexamos en 0 nuestras cajas, Ai+1 representa cuantas cajas debe moverse
            // Para saltar desde j, sumamos j. Tomamos modulo N ya que estan en circulo
            // (N y 1) estan contiguos.
            adj[j] = (j + Ai + 1) % N;
            // Si al saltar desde la caja j, regresas a j, se aniade una caja magica.
            if(adj[j] == j) count++;
        }
        // Realizamos Kosaraju con nuestro vector de adyacencias
        vector <ull> kosa = problem.kosaraju(N, adj);
        for(ull sum : kosa){
            // Descarta los nodos que no estan en un componente completamente
            // conexo y evita sumar un uno de mas.
            if (sum != 1) 
                count += sum;
        }
        cout << count << endl;
    } 

    return 0; 
}