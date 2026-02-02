#include <iostream>
#include <map>
#include <vector>
#include <iomanip>
#include <set>
using namespace std;

/*
    11348 - Exhibition 
    Itzel Berenice Martinez Palacios

    Para este problema utilizaremos un map llamado "colection", el cual guarda:
        * Primera entrada (entero): Guarda el tipo de estampilla actual.
        * Segunda entrada (set de enteros): Guarda a las personas que tienen a la
            estampilla actual en su coleccion.
    En el problema, por cada persona en el grupo de amigos, nos daran los tipos de 
    estampillas que esta persona tiene, por lo cual en nuestro map "colection"
    registraremos entonces en el set de su segunda entrada, que esta persona tiene
    en su coleccion personal dicha estampilla.

    Inicializamos ahora un entero llamado "originals" que contara cuantas estampillas
    las tiene solamente una persona en el grupo de amigos. Tambien un vector llamado 
    "total_stamps", en su i-esima posicion almacena la cantidad de estampillas
    originales que tiene la persona i.
    
    Despues, para cada elemento (i) en nuestro map "colection", checamos si el set 
    del elemento (i) tiene un solo elemento. Si es asi, le sumamos 1 a nuestro entero
    "originals", y tambien a la posicion correspondiente en nuestro vector "total stamps",
    la posicion en "total_stamps" corresponde al unico elemento en el set del elemento (i).

    Finalizamos imprimiendo los porcentajes adecuados para cada caso, con 6 digitos despues
    del punto.
*/

int main(){
    int k; cin >> k;
    for(int cases = 0; cases < k; cases++){
        map<int,set<int>> colection;
        int n; cin >> n;
        for(int i = 0; i < n; i++){
            int m; cin >> m;
            for(int j = 0; j < m; j++){
                int a; cin >> a;
                colection[a].insert(i);
            }
        }
        vector<int> total_stamps(n,0);
        int originals = 0;
        for(auto &stamp : colection){
            if(stamp.second.size() == 1){
                originals++;
                total_stamps[*stamp.second.begin()]++;
            }
        }
        cout << "Case " << cases+1 << ":";
        for(int i = 0; i < n; i ++)
            cout << " " << fixed << setprecision(6) << double(total_stamps[i])*100/originals << "%";
        cout << endl;
    }

    return 0;
}