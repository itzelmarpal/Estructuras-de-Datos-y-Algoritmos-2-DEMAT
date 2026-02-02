#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <math.h>

/*
    Itzel Berenice Martinez Palacios
    Estructuras de Datos y Algoritmos 2
    Tarea 8
    Problema 2
*/

using namespace std;

// Funcion que nos dice si C es una cadena que es mezcla ordenada de A y B 
bool isMixed(string A, string B, string C){

    // Si las longitudes no coinciden, C no esta formada por A y B
    if(A.size() + B.size() != C.size())
        return false;

    // Inicializamos nuestra matriz de programacion dinamica
    vector<vector<bool>> dp(A.size() + 1, vector<bool>(B.size() + 1, 0)); 
    dp[0][0] = true;
    
    // Llenamos la primera columna utilizando A
    for(int i = 1; i <= A.size(); i++){
        if(dp[i-1][0] && A[i-1] == C[i-1])
            dp[i][0] = true;
    }

    // Llenamos la primera fila utilizando B
    for(int i = 1; i <= B.size(); i++){
        if(dp[0][i-1] && B[i-1] == C[i-1])
            dp[0][i] = true;
    }

    // Llenar la matriz dp utilizando programacion dinamica
    for (int i = 1; i <= A.size(); i++) {
        for (int j = 1; j <= B.size(); j++) {
            // El caracter i+j-1 de C esta dado por la cadena A
            if(A[i-1] == C[i+j-1] && dp[i-1][j])
                dp[i][j] = true;
            // El caracter i+j-1 de C esta dado por la cadena B
            if(B[j-1] == C[i+j-1] && dp[i][j-1])
                dp[i][j] = true;
        }
    }
    // Se regresa el resultado final
    return dp[A.size()][B.size()];
}
int main(){
    string A, B, C;

    // Leemos las cadenas A, B y C
    cout << "Ingrese la cadena A: " << endl;
    cin >> A;
    cout << "Ingrese la cadena B: " << endl;
    cin >> B;
    cout << "Ingrese la cadena C: " << endl;
    cin >> C;

    // Analizamos las cadenas para obtener nuestra respuesta
    bool answer = isMixed(A, B, C);
    
    // Imprimimos la respuesta adecuada
    if(answer){
        cout << "La cadena C SI es mezcla de las cadenas A y B." << endl;
    }
    else cout << "La cadena C NO es mezcla de las cadenas A y B." << endl;

    return 0;
}