#include <iostream>
#include <vector>
#include <algorithm>
#define INT_MAX  2147483647
using namespace std;
vector <int> dp(100001, INT_MAX);

/*
    12955 - Factorial
    Itzel Berenice Martinez Palacios
    
    Este programa precalcula las respuestas en un vector "dp", donde
    dp[i] guarda el minimo de factoriales que suman "i".

    Primero, llenamos el vector "dp" con  dos fors. El de afuera
    genera los factoriales al multiplicarse con "num_multiplied" y el
    de adentro los usa para encontrar la solucion optima para cada numero.

    Al final, cuando leemos un "n", la respuesta ya esta precalculada y
    solo la imprimimos desde dp[n].
*/

int main(){
    dp[0] = 0;
    int num_multiplied = 1;
    for(int factorial = 1; factorial < 100001; factorial *= num_multiplied){
        for(int i = factorial; i < 100001; i++)
            dp[i] = min(dp[i], dp[i-factorial]+1);
        num_multiplied++;
    }
    int n;
    while(cin >> n )
        cout << dp[n] << endl;
    
    return 0;
}