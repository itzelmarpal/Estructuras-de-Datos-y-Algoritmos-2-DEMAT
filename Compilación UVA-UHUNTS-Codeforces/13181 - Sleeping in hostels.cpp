#include <iostream>
#include <string>
#include <algorithm>
/*
    13181 - Sleeping in hostels.cpp
    Itzel Berenice Martinez Palacios
    Nos dan cadenas de caracteres, el programa debe terminar cuando 
    dejemos de recibir estas cadenas.
    Para cada cadena debemos encontrar la mejor posicion en la que 
    podra dormir un huesped, y debemos imprimir la distancia al huesped 
    mas cercano.
    Para ello declaramos una variable llamada ans que guardara esta distancia
    maxima, recorremos cada posicion de la cadena dada y tambien tenemos un entero
    llamado 'prev' que guarda la posicion del huesped mas cercano a la posicion actual.
    Tenemos tres casos:
        * Cuando acabamos de encontrar un huesped por primera vez
        * Cuando ya hemos encontrado un huesped previamente
        * Cuando el ultimo huesped encontrado no esta en la ultima casilla
    Cada uno de estos casos los tratamos de la manera adecuada, como lo hacemos en las
    siguientes lineas.
*/
using namespace std;
int main(){
    string s;
    while(1){
        // Leer la linea de caracteres
        getline(cin, s);
        if(s.empty()) break; // Parar si no hay cadena
        int prev = -1, ans = 0;
        for(int i = 0; i < s.size(); i++){
            if(s[i] == 'X'){
                if(prev == -1){
                    ans = max(i-1, prev);
                    prev = i;
                }
                else{
                    ans = max(ans, (i-prev-2)/2);
                    prev = i;
                }
            }
            
        }
        if(prev != s.size()-1)
            ans = max(ans, int(s.size())-prev-2);
        cout << ans << endl;
    }

    return 0;
}