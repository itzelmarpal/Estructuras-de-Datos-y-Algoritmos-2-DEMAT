#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp> 

using namespace std;
using namespace __gnu_pbds; 

// Definicion del Ordered Set para pairs que guardan
// como primera instancia el valor, y como segunda el indice

typedef tree<
    pair<long long int,int>,  
    less<pair<long long int,int>>,
    rb_tree_tag,
    tree_order_statistics_node_update
> ordered_multiset;
  
/*
    DMKTHNUM
    Segment Tree
    Itzel Berenice Martinez Palacios
    Tarea 3
*/

// Estructura del nodo del segment tree, solo guarda
// un ordered set
struct Node{
    ordered_multiset segment;
};

// Funcion para construir el Segment Tree.
void buildTree(int ss, int se, int idx, vector <long long int> &arr, vector <Node> &tree){
    // Condicion de paro 
    if(ss == se){
        tree[idx].segment.insert({arr[ss],ss});
        return;
    }

    int mid = (ss + se)/2;

    // Se construye el lado izquierdo del arbol
    buildTree(ss, mid, 2*idx+1, arr, tree);

    // Se construye el lado derecho del arbol
    buildTree(mid+1, se, 2*idx+2, arr, tree);

    // Se agregan los nodos hijos al nodo padre
    for (auto val : tree[2 * idx + 1].segment)
        tree[idx].segment.insert(val);
    for (auto val : tree[2 * idx + 2].segment)
        tree[idx].segment.insert(val);
}

// Cuenta la cantidad de elementos en un rango [start, end] del arreglo
// que son menores o iguales a x.
long long int countLessThanK(int start, int end, int x, int ss, int se, int idx, vector <Node> &tree){
    // El intervalo del nodo esta totalmente fuera del rango de la query
    if(ss > end || se < start){                                                                             
        return 0;
    }
    // El intervalo del nodo esta completamente contenido en el de la query
    if(ss >= start && se <= end){
        // Cuenta los elementos menores o iguales que x.
        return tree[idx].segment.order_of_key({x+1,0});
    }
    int mid = (ss + se)/2;

    // Si esta parcialmente contenido se hace el proceso para los hijos y se regresa la suma.
    long long int leftChild = countLessThanK(start, end, x, ss, mid, 2*idx+1, tree);
    long long int rightChild = countLessThanK(start, end, x, mid+1, se, 2*idx+2, tree);
    return leftChild + rightChild;
}

// Responde la query de tipo 0: Dado un rango [start, end]
// y un valor k, encuentra el k-ésimo número (por orden).
long long int queryType0(int start, int end, int k, int ss, int se,
    int idx, vector <Node> &tree, vector <long long int> &arr){
    // Busca el valor mínimo y máximo en el arreglo original
    // para encontrar los límites de la búsqueda binaria.
    int lowerInArray = *min_element(arr.begin(), arr.end());
    int higherInArray = *max_element(arr.begin(), arr.end());

    // Busqueda binaria en el intervalo con el minimo y maximo
    while(lowerInArray < higherInArray){    
        int mid = (lowerInArray + higherInArray)/2;
        // Cuenta cuantos elementos en el rango [start, end] son menores o igaules a mid.
        long long countSubTree = countLessThanK(start, end, mid, ss, se, idx, tree);

        // Se ajusta el intervalo de la busqueda en base a esos 
        if(countSubTree <= k) lowerInArray = mid + 1;
        else higherInArray = mid;
    }
    return lowerInArray;
}

// Responde la query del tipo 1. Actualiza el valor
// en la posición 'positionOld' a 'newValue'.
void queryType1(int ss, int se, int idx, int positionOld, long long int newValue,
    vector<Node>& tree, long long oldValue) {

    // Se elimina el valor anterior, y se inserta el nuevo valor.
    tree[idx].segment.erase({oldValue, positionOld});
    tree[idx].segment.insert({newValue, positionOld});

    // Si se llega a un nodo hoja solo se regresa.
    if (ss == se) return;
    
    // En cualquier otro caso se realiza la misma función para los nodos hijos.
    int mid = (ss + se) / 2;
    if (positionOld <= mid)
        queryType1(ss, mid, 2 * idx + 1, positionOld, newValue, tree, oldValue);
    else
        queryType1(mid + 1, se, 2 * idx + 2, positionOld, newValue, tree, oldValue);
}

int main(){
    int N, M, query;
    cin >> N ;
    vector <long long int> arr(N);
    // Se inicia el arbol con 4*N nodos.
    vector<Node> tree(4 * N);
    for(int i = 0; i< N; i++){
        cin >> arr[i];
    }
    // Construimos nuestro arbol
    buildTree(0, N - 1, 0, arr, tree);
    cin >> M;

    for(int i = 0; i < M; i++){
        cin >> query;
        // Query 0: Pregunta por el k-ésimo número en el rango [l, r] ordenado.
        if(query == 0){
            int l, r , k;
            cin >> l >> r >> k;
            cout << queryType0(l, r, k, 0, N-1, 0, tree, arr) << endl;
        }
        // Query 1: Se actualiza un valor.
        if(query == 1){
            int idx; 
            long long int v;
            cin >> idx >> v;
            queryType1(0, N-1, 0, idx, v, tree, arr[idx]);
            arr[idx] = v;
        }
    }
    return 0;
}