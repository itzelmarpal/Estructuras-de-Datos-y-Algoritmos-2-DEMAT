#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

/*
    Itzel Berenice Martinez Palacios
    Estructuras de Datos y Algoritmos 2
    Tarea 7
    Problema 1
*/

// Almacena la longitud de la sub-cadena mas larga empezando por s[i]
// que coinciden con los primeros carácteres de s.
std::vector<int> zFunction(std::string s) {
    std::vector<int> zf(s.size());
    // We will maintain this interval all along the scan of s
    int l=0,r=0;
    // Scanning s
    for(int i=1;i<s.size();i++) {
        if (i<r) {
            zf[i] = min(r-i,zf[i-l]);
        }
        // Expand zf[i] when possible
        while (i+zf[i]<s.size() && s[zf[i]]==s[i+zf[i]]) zf[i]++;
        // We may have to update the rightmost interval matched with a prefix of s
        if (i+zf[i]>r) {
            l = i;
            r = i+zf[i];
        }
    }
    return zf;
}

// Funcion que resuelve el problema.
string short_Palindrome(string s){
    string original = s; // guardamos la cadena original
    reverse(s.begin(), s.end()); // reverso de s
    string rev_s = s;
    string aux= rev_s + original; // Concatenamos la cadena al reves con la original

    vector <int> z = zFunction(aux); 
    int count = 0;

    // Identificamos el indice en donde dejan de coincidir las cadenas.
    for(int i = 1; i <= s.size(); i++){
        if(z[aux.size()-i] == i)
            count = i;
    }
    // Regresamos la cadena original concatenada con la
    // parte que no sobra en el reverso de s
    return original + rev_s.substr(count);
}

int main(){
    string s;
    cin >> s;
    // Imprimimos la respuesta
    cout << short_Palindrome(s) << endl;
    return 0;
}