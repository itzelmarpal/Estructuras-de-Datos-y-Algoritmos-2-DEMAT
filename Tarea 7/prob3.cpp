#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;
int resets[1000];

/*
    Itzel Berenice Martinez Palacios
    Estructuras de Datos y Algoritmos 2
    Tarea 7
    Problema 3
*/

// Preprocesa el patron dado para aplicar despues kmpMatch
void kmpPreprocess(const string &p) {
    int i=0,j=-1;
    resets[0]=-1;
    while (i<p.size()) { // For all caracters in the pattern
        while (j>=0 && p[i]!=p[j]) j=resets[j];
        i++;j++;
        resets[i]=j;
    }
}
// Encuentra las ocurrencias del patron en la cadena s y guardamos sus posiciones iniciales
void kmpMatch(const string &s, const string &pattern, set<int>& indexes) {
    kmpPreprocess(pattern);
    int i=0,j=0;
    // Scan the string s
        while (i<s.size()) {
            // If there is a mismatch at i, we use the resets array *recursively* to try smaller par// In case there is no matching at all, this loop will stop with j=-1
            while (j>=0 && s[i]!=pattern[j]) j = resets[j];
            // If there is a match or no matched structure at all (j=-1), we advance
            i++; j++;
            // This happens when we find the pattern
            if (j==pattern.size()) {
                indexes.insert(i-j); // Se guarda la posicion en donde coincide
                // We can leverage (again) the already matched characters
                j = resets[j];
            }
        }
    return;
}

int main(){
    int W, H, w, h;
    // Leemos la matriz grande
    cout << "Introduce W y H: " << endl;
    cin >> W >> H;
    vector<string> M(W);
    cout << "Introduce la matriz grande palabra por palabra: " << endl;
    for(int i = 0; i < W; i++){
        cin >> M[i];
    }
    // Leemos la matriz chica
    cout << "Introduce w y h:" << endl;
    cin >> w >> h;
    cout << "Introduce la matriz chica palabra por palabra: " << endl;
    vector<string> m(w);
    for(int i = 0; i < w; i++){
        cin >> m[i];
    }

    int answer = 0; // Contador de ocurrencias de la matriz chiquita

    // Se busca la matriz m en la M.
    for(int n = 0; n <= (W-w) ; n++){
        // matches[i] guarda las posiciones donde aparece la fila i de m en M[n+i]
        vector<set<int>> matches(w); 
        // Buscamos cada fila de m en la fila correspondiente de M
        for(int i = 0; i < w; i++)
            kmpMatch(M[n+i], m[i], matches[i]);
        
        // Verifica si la matriz coincide verticalmente
        for (int pos : matches[0]){ 
            bool aux = true;
            for (int j = 1; j < w; j++){
                // Verifica si la posicion actual existe en todas las filas
                if(matches[j].find(pos) == matches[j].end()){
                    aux = false;
                    break;
                }
            }
            if(aux) answer++; // Incrementa si todas las filas coinciden en la posicion actual
        }
    }
    cout << answer << endl;  // Imprime la respuesta final
    return 0;
}