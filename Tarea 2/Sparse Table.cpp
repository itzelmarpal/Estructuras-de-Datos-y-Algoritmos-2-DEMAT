#include <bits/stdc++.h>
using namespace std;

/*
    Tarea 2
    Sparse Table
    Itzel Berenice Martinez Palacios
    Estructuras de Datos y Algoritmos 2
*/

class TreeProblem {
private:
    vector<vector<long long int>> AdjList; // Lista de adyacencia para el arbol
    long long int n; // Numero de nodos en el arbol

public:
    // Constructor de la clase TreeProblem
    TreeProblem(long long int n) {
        this->n = n;
        AdjList.resize(n);
    }
    // Funcion para agregar aristas al arbol
    void addAdjNode(long long int a, long long int b) {
        AdjList[a].push_back(b);
        AdjList[b].push_back(a);
    }
    // Funcion para realizar un recorrido BFS en el arbol
    // y llenar la primera columna de las tablas de saltos y sumas
    void bfs(long long s, vector<vector<long long int>> &jump,
        vector<vector<long long int>> &sums, vector<long long int> &value) {
        queue<long long int> q;
        vector<bool> visited(n, false);
        visited[s] = true;

        q.push(s);
        while (!q.empty()) {
            long long int current = q.front();
            q.pop();

            for (long long int next : AdjList[current]) {
                if (!visited[next]) {
                    visited[next] = true;
                    q.push(next);
                    jump[next][0] = current; // Guarda el salto de un nodo a su padre
                    sums[next][0] = value[current]; // Guarda el valor del nodo padre
                }
            }
        }
    }
};

int main() {

    int N, Q;
    cin >> N >> Q; // Numero de nodos y numero de queries

    // Calcula el logaritmo en base 2 de los numeros de 1 a N
    vector<long long int> log(N + 1, 0);
    for (int i = 2; i <= N; i++) {
        log[i] = log[i / 2] + 1;
    }

    // Se crea un objeto de la clase TreeProblem y un vector
    // para guardar los valores de los nodos
    TreeProblem treeAdj(N);
    vector<long long int> values(N);

    // Se leen los valores de los nodos
    for (int i = 0; i < N; i++) {
        cin >> values[i];
    }

    // Se leen las aristas del arbol
    for (int i = 0; i < N - 1; i++) {
        long long int a, b;
        cin >> a >> b;
        treeAdj.addAdjNode(a, b);
    }
    
    // Se crean las tablas de saltos y sumas
    vector<vector<long long int>> jump(N, vector<long long int>(log[N] + 1, -1));
    vector<vector<long long int>> sums(N, vector<long long int>(log[N] + 1, 0));

    // Se realiza un recorrido BFS en el arbol
    treeAdj.bfs(0, jump, sums, values);

    // Se llena el resto de las columnas de las tablas de saltos y sumas
    for (int j = 1; j <= log[N]; j++) {
        for (int i = 0; i < N; i++) {
            long long int ancestor = jump[i][j - 1]; // Salto de un nodo a su ancestro
            sums[i][j] = sums[i][j - 1]; // Suma de los valores de los nodos
            if (ancestor != -1) {
                jump[i][j] = jump[ancestor][j - 1]; 
                sums[i][j] = sums[i][j - 1] + sums[ancestor][j - 1]; 
            }
        }
    }

    // Se leen los nodos y k de las queries
    for (int i = 0; i < Q; i++) {
        long long int node, k;
        cin >> node >> k;

        long long sum_result = values[node]; // Suma del nodo actual

        // Se realiza el salto de k posiciones en el arbol
        for (int j = log[N]; j >= 0 && node != -1; j--) {
            if ((1 << j) & k) { 
                sum_result += sums[node][j];
                node = jump[node][j]; 
            }
        }
        cout << sum_result << "\n"; // Se imprime el resultado de la query
    }

    return 0;
}