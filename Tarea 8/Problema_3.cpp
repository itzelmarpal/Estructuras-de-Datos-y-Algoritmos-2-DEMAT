#include <iostream>
#include <vector>
#include <string>

using namespace std;

/*
    Itzel Berenice Martinez Palacios
    Estructuras de Datos y Algoritmos 2
    Tarea 8
    Problema 3
*/

int main(){
    string A, B;
    // Se leen las cadenas que describen las pilas de hotcakes
    cin >> A >> B;
    vector <vector<int>> dp (A.size() + 1, vector<int>(B.size()+1, 0));

    // Llenar la primera fila (quitar todos los hotcakes de la primera pila 
    // para hacer una pila vacia)
    for (int i = 1; i < A.size() + 1; i++) {
        dp[i][0] = i;
    }
    // Llenar la primera columna (quitar todos los hotcakes de la segunda pila 
    // para hacer una pila vacia)
    for (int i = 1; i < B.size() + 1; i++) {
        dp[0][i] = i;
    }

    // Llenar la matriz de dp utilizando programacion dinamica
    for(int i = 1; i <= A.size(); i++){
        for(int j = 1; j <= B.size(); j++){

            // Checamos la diagonal anterior, si al agregar el siguiente hotcake
            // en cada pila de hotcakes notamos que son del mismo tamanio, 
            // se conserva el costo anterior, si no, aumentamos dos al costo
            int diagonal = (A[i-1] == B[j-1]) ? dp[i-1][j-1] : dp[i-1][j-1] + 2;

            // Tambien tomamos el minimo del costo de arriba y a la izquierda de 
            // nuestra posicion actual, que seria como si en el cambio actual 
            // consideremos el siguiente hotcake de la primera fila o de la segunda 
            // lo cual toma un cambio de 1.
            int side = min(dp[i-1][j] + 1 , dp[i][j-1] + 1);

            // Le asignamos el minimo de los valores anteriores a nuestra dp
            dp[i][j] = min(diagonal, side);
        }
    }

    // Imprimimos la cantidad minima de cambios para los hotcakes
    cout << dp[A.size()][B.size()] << endl;

    return 0;
}