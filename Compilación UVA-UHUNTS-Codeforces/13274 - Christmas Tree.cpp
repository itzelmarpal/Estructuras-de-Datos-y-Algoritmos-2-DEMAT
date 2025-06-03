#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#define MAXN 1002
using namespace std;
vector<int> tree[MAXN];

/*
    13274 - Christmas Tree
*/

int maxNodes_KTree(int parent, int actual, int k){
    // Si el nodo actual tiene menos de k hijos, el arbol 
    // maximo solo tiene un nodo, el cual es si mismo
    if(tree[actual].size() < k) return 1;

    // Guarda la cantidad máxima de nodos que tiene cada hijo del nodo actual
    vector<int> maxNodes(tree[actual].size());

    int ans = 1, counter = 0; // ans es la respuesta, y counter cuenta los hijos del nodo actual
    for(int node : tree[actual]){ // Recorremos los nodos hijos del nodo actual
        if(node != parent){
            // Calculamos el maximo no. de nodos para cada sub-arbol con cada hijo del nodo actual como padre
            maxNodes[counter] = maxNodes_KTree(actual, node, k);
            counter++;
        }
    }
    if(counter < k) return 1; // Si el nodo actual no tiene k hijos, regresamos 1
    sort(maxNodes.begin(), maxNodes.begin() + counter, greater<int>()); // Ordenamos de mayor a menor
    
    // Sumamos la cantidad maxima de nodos en el sub-arbol de interes
    for(int i = 0 ; i < k; i++){ 
        ans += maxNodes[i];
    }
    return ans; // Regresamos la respuesta
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; // Leemos la cantidad de casos de prueba
    cin >> t;
    for(int cases = 0; cases < t; cases++){
        int n, k;
        // Leemos la cantidad de nodos y la cantidad de hijos permitida
        cin >> n >> k; 

        //Limpiamos el arbol
        for (int i = 1; i <= n; i++) 
            tree[i].clear();
        for(int i = 0; i < n-1; i++){
            // Leemos las aristas del arbol
            int u, v;
            cin >> u >> v;
            tree[u].push_back(v); 
            tree[v].push_back(u);
        } 
        // Imprimimos la respuesta
        cout << "Case " << cases+1 << ": "<< maxNodes_KTree(-1, 1, k) << "\n";
    }
    return 0;
}
