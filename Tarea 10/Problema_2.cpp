#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/*
    Itzel Berenice Martinez Palacios
    Estructuras de Datos y Algoritmos 2
    Tarea 9
    Problema 2
*/

const int p = 31;
const int m = 1000000007;
int n;

vector<long long> hashed_prefixes, pi;

// Regresa el valor hash del substring s[l, r-1]
long long hash_value(int l, int r){
    long long value = (hashed_prefixes[r] - hashed_prefixes[l] + m) % m;
    value = (value * pi[n - l - 1]) % m;
    return value;
}

// Checa si existe un substring de tamanio l que cumple las condiciones del problema
bool is_a_password(int l){
    
    long long pfx = hash_value(0, l); // Hash del prefijo con longitud l
    long long sfx = hash_value(n-l, n); // Hash del sufijo con longitud l
    // Checamos si coinciden
    if(pfx == sfx){
        // Si coinciden buscamos el mismo substring dentro de la cadena s
        for(int i = 1; i+l < n; i++){ 
            long long actual = hash_value(i, i+l);
            if(actual == pfx)  return true; // Se regresa 1 al encontrar dicho substring
        }
    }
    return false;
}

int main(){
    // Leemos el input del problema
    string s; cin >> s;
    n = s.size();
    // Precalcular potencias de p modulo m 
    pi.resize(n,0);
    pi[0] = 1;
    for (int i = 1; i < n; i++){
        pi[i] = (pi[i-1] * p) % m;
    }
    // Precalcular los valores de hash para todos los prefijos de s
    hashed_prefixes.resize(s.size()+1, 0);
    for (int i = 0; i < s.size(); i++){
        hashed_prefixes[i+1] = (hashed_prefixes[i] + s[i] * pi[i]) % m;
    }
    // Se busca el substring mas largo que cumpla las condiciones del problema
    // Empezamos desde el mas grande, hasta el mas chico
    for(int i = n-2; i > 0; i--){
        if (is_a_password(i)){
            // Si lo encontramos, imprimimos dicho substring
            cout << s.substr(0, i) << endl; 
            return 0;
        }
    }
    // Si no encontramos ningun substring que cumpla las condiciones, imprimimos 
    // Just a legend
    cout << "Just a legend" << endl;

    return 0;
}