#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <math.h>

using namespace std;

/*
    Itzel Berenice Martinez Palacios
    Estructuras de Datos y Algoritmos 2
    Tarea 8
    Problema 1
*/


// Funcion que calcula el costo de operaciones para el alineamiento de cadenas
// y nos da las operaciones optimas
void SequenceAlignment(string first, string second) {
    // Crear una matriz dp inicializada en ceros
    vector<vector<int>> dp(first.size() + 1, vector<int>(second.size() + 1, 0));

    // Llenar la primera columna (convertir la cadena first en cadena vacia con
    // solo eliminaciones de caracteres)
    for (int i = 1; i < first.size() + 1; i++) {
        dp[i][0] = i;
    }
    // Llenar la primera fila (convertir la cadena vacia en la second con
    // solo inserciones de caracteres)
    for (int i = 1; i < second.size() + 1; i++) {
        dp[0][i] = i;
    }

    // Llenar la matriz dp utilizando programacion dinamica
    for (int i = 1; i < first.size() + 1; i++) {
        for (int j = 1; j < second.size() + 1; j++) {
            // Calcular la puntuacion por coincidencia (costo 0) o sustitucion (costo 1)
            int match = (first[i-1] == second[j-1]) ? 0 : 1;
            
            // Seleccionar la puntuacion maxima de las posibles operaciones 
            dp[i][j] = min({dp[i-1][j] + 1, dp[i][j-1] + 1, dp[i-1][j-1] + match});
            if((i > 1) && (j > 1) && (first[i-1] == second[j-2]) && 
                (first[i-2] == second[j-1]))
                dp[i][j] = min(dp[i][j], dp[i-2][j-2] + 1); 
        }
    }

    // Imprimir la puntuacion del alineamiento optimo
    cout  << "-----------------------------------------------------------" << endl;
    cout << "El costo de operaciones para llegar a la secuencia optima es " << 
    dp[first.size()][second.size()] << endl;
    cout << "Con las siguientes operaciones: " << endl;
    cout  << "-----------------------------------------------------------" << endl;
    vector<string> optime;
    int i = first.size();
    int j = second.size();
     while (i > 0 || j > 0) {
        // Coincidencia (costo 0)
        if (i > 0 && j > 0 && first[i - 1] == second[j - 1] &&
            dp[i][j] == dp[i - 1][j - 1]) {
            optime.push_back("Manten " + string(1, first[i - 1]));
            i--;
            j--;
        } 
         // Sustitución (costo 1)
        else if (i > 0 && j > 0 && first[i - 1] != second[j - 1] 
            && dp[i][j] == dp[i - 1][j - 1] + 1) {
            optime.push_back("Sustituye " + string(1, first[i - 1]) + 
            " por " + string(1, second[j - 1]));
            i--;
            j--;
        } 
        // Borrado (costo 1)
        else if (i > 0 && dp[i][j] == dp[i - 1][j] + 1) {
            optime.push_back("Borra " + string(1, first[i - 1]));
            i--;
        }
        // Insertar (costo 1)
        else if (j > 0 && dp[i][j] == dp[i][j - 1] + 1) {
            optime.push_back("Inserta " + string(1, second[j - 1]));
            j--;
        } 
        // Transposicion (costo 1)
        else if (i > 1 && j > 1 && first[i - 1] == second[j - 2] && 
            first[i - 2] == second[j - 1] && dp[i][j] == dp[i - 2][j - 2] + 1) {
            optime.push_back("Transposicion de " + string(1, first[i - 2]) 
            + string(1, first[i - 1]));
            i -= 2;
            j -= 2;
        }
    }
    // Imprimir el vector al reves, es decir, en el orden correcto.
    for(int i = optime.size()-1; i >= 0; i--){
        cout << optime[i] << endl;
    }
}

int main(){
    string s, t;
    // Leemos las cadenas
    cout << "Ingresa la primera cadena: " << endl;
    cin >> s;
    cout << "Ingresa la segunda cadena: " << endl;
    cin >> t;

    // Llamamos a la funcion de alineamiento de secuencias
    SequenceAlignment(s, t);

    return 0;
}