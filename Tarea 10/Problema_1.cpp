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
    Problema 1
*/

int rabinKarpMatch(const string& s, const string& badness, int k) {
    const int p = 33; // Numero primo utilizado
    const int m = 1000000007; 

    // Precalcular potencias de p modulo m 
    vector<long long> pi(s.size()+1);
    pi[0] = 1;
    for (int i = 1; i <= s.size(); i++){
        pi[i] = (pi[i-1] * p) % m;
    }
    // Precalcular los valores de hash para todos los prefijos de s
    vector<long long> hashed_prefixes(s.size() + 1, 0);
    for (int i = 0; i < s.size(); i++){
        hashed_prefixes[i+1] = (hashed_prefixes[i] + (s[i] - 'a' + 1) * pi[i]) % m;
    }
    
    // Matriz para guardar la bondad acumulada en los substrings
    // Si tenemos sum[i][j], entonces representa la bondad del substring desde
    // i hasta j.
    vector<vector<long long>> sum (s.size()+1, vector <long long>(s.size(), 0));
    // Determinar la bondad para los substrings s
    for (int i = 0; i < s.size(); i++) {
        sum[i][i] = (1 + badness[s[i]-'a'] - '0') % 2; // Dice si el caracter i es bueno o malo
        // Calcula la bondad para substrings de distinto tamanio
        for (int l = i+1; l < s.size(); l++) {
            sum[i][l]=sum[i][l-1]+((1 + badness[s[l]-'a'] - '0') % 2);
        }
    }

    int distinct = 0;

    for (int l = 1; l <= s.size(); l++) {
        set<long long> allHashed;
        
        for (int i = 0; i+l <= s.size(); i++)
            if (sum[i][l+i-1]<= k){ // Solo consideramos substring con bondad requerida
                long long hashed = (hashed_prefixes[i + l] + m - hashed_prefixes[i]) % m;
                hashed = (hashed * pi[s.size()-i]) % m;
                allHashed.insert(hashed); // Insertamos el hash en nuestro set de hashes
            }
        distinct += allHashed.size(); // Sumamos la cantidad de hashes únicos con longitud l.
    }
    return distinct;
}    


int main(){
    // Leemos el input
    string s, badness;
    cin >> s >> badness;
    int k; cin >> k;

    //Llamamos a la funcion que resuelve el problema
    cout << rabinKarpMatch(s, badness, k) << endl;
    return 0;
}