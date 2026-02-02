#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <algorithm>
#define ll long long
#define MAX 2000002
using namespace std;

const int p = 31;
const int m = 1000000007;
vector<ll> hashed_prefixes;
vector<ll> pi;
int n;

/*
    Itzel Berenice Martinez Palacios
    Estructuras de Datos y Algoritmos 2
    Tarea 9
    Problema 3
*/

// Regresa el valor hash del substring de s, empezando con i de longitud l
long long hash_value(int i, int l){
    long long hashed = (hashed_prefixes[i + l] + m - hashed_prefixes[i]) % m; // hp[0] = 0 y hp[1] corresponde a s[0]
    hashed = (hashed * pi[n-i-1]) % m;
    return hashed;
}

// Encuentra el minimo index tal que se cumple lo indicado en la tarea
int inciso_a(string s, int k, int l){
    int low = 0, high = (n-max(k,l)+1); // Valores para la busqueda binaria
    while(low < high){
        int mid = low + (high-low)/2;
        if(hash_value(k, mid) == hash_value(l, mid))
            low = mid+1; // Si coinciden, se busca mas largo
        else{
            high = mid; // Si no coinciden, se busca mas cortos
        }
    }
    return low; // Se regresa la longitud encontrada
}

// Compara dos substrings como el problema nos lo indica
bool inciso_b(string s, int k, int l){
    int idx = inciso_a(s, k, l); // Encontramos el indice donde ya no coinciden
    // Comparamos los caracteres cuando son distintos
    if(idx == n || s[k+idx] >= s[l+idx]) return 0;
    return 1;
}

int main(){
    // Leemos el input del problema
    int cases; cin >> cases;
    for(int count = 0; count < cases; count++){
        string s; cin >> s;
        string t = s + s; // Se duplica el string para resolver el problema
        int n = t.size();

        // Calcular los potencias modulares para el hashing
        pi.resize( t.size() +1, 0);
        pi[0] = 1;
        for (int i = 1; i <= t.size(); i++){
            pi[i] = (pi[i-1] * p) % m;
        }

        // Calcular los valores de hash para cada prefijo del string t
        hashed_prefixes.resize(t.size()+1, 0);
        for(int i = 0; i < t.size(); i++){
            hashed_prefixes[i+1] = (hashed_prefixes[i] + (t[i]- 'a' + 1) * pi[i]) % m;
        }

        // Buscamos la mejor rotacion del collar
        int low = 0, l = n/2;
        for(int i = 1; i < l; i++) // Comparamos los substrings
            if(t.substr(i, l) < t.substr(low, l)) low = i;
        // Imprimimos el indice de la mejor rotacion
        cout << low + 1 << endl;
    }
    return 0;
}