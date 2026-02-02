#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
int resets[1000001];

/*
    Itzel Berenice Martinez Palacios
    Estructuras de Datos y Algoritmos 2
    Tarea 7
    Problema 2
*/

// Funcion que me construye el arreglo resets
void kmpPreprocess(const string &p) {
    int i=0,j=-1;
    resets[0]=-1;
    while (i<p.size()) { // For all caracters in the pattern
        while (j>=0 && p[i]!=p[j]) j=resets[j];
        i++;j++;
        resets[i]=j;
    }
}
// Count the number of occurences of pattern within s
int kmpMatch(const string &s, const string &pattern) {
    int i=0,j=0,nc=0;
    // Scan the string s
    while (i<s.size()) {
    // If there is a mismatch at i, we use the resets array *recursively* to try smaller par// In case there is no matching at all, this loop will stop with j=-1
    while (j>=0 && s[i]!=pattern[j]) j = resets[j];
    // If there is a match or no matched structure at all (j=-1), we advance
i++; j++;
// This happens when we find the pattern
if (j==pattern.size()) {
nc++;
// We can leverage (again) the already matched characters
j = resets[j];
}
}
return nc;
}

    

int main(){
    string word;
    cin >> word;
    // Preprocesamos la cadena dada para construir el arreglo resets-
    kmpPreprocess(word);
    vector <string> sufix_prefix;
    sufix_prefix.push_back(word); // la cadena dada es una de las respuestas

    // Prefijo propio mas largo que también es sufijo
    int lsp = resets[word.size()];

    // Construye el vector de todos los prefijos que son sufijos
    while(lsp > 0){
        sufix_prefix.push_back(word.substr(0,lsp));
        lsp = resets[lsp];
    }
    // Imprime los prefijos-sufijos y cuantas veces aparecen en la cadena
    // original de menor a mayor.
    for(int i = sufix_prefix.size()-1 ; i >= 0; i--){
        int reps = kmpMatch(word, sufix_prefix[i]);
        cout << sufix_prefix[i] << " " << reps << endl;
    }

    return 0;
}