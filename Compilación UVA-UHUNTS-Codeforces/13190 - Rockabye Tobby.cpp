#include <iostream>
#include <set>
#include <utility>
#include <vector>
#include <string>
using namespace std;

/*
    13190 - Rockabye Tobby
    Itzel Berenice Martinez Palacios
    
    Utilizando que el set ordena a sus elementos de menor a mayor, inicializamos
    uno que guarde pairs:
        * La primera entrada del pair corresponde al proximo tiempo en que tobby
            se tomara dicha medicina.
        * La segunda entrada del pair es la posición inicial en la que se leyo la
            medicina.
    Asi, el orden del set se ira por los menores tiempos y en caso de empate toma
    en cuenta la prioridad de dicha medicina.

    Tambien utilizamos dos vectores extras:
        * initial_time: Guarda en la posicion (i) el tiempo inicial de la medicina i
        * medication_names: Guarda en la posicion (i) el nombre de la medicina i.
    Cada medicina que nos den la vamos a ingresar a nuestro set.

    Asi, cada linea del output sera el elemento en la primera posicion del set,
    despues se borra dicho elemento, y se aniade basicamente el mismo, pero con
    el nuevo tiempo en el que Tobby debera tomarse dicha pastilla.

    Hacemos esto hasta que Tobby se tome la cantidad de pastillas que le recomienda
    el doctor.
*/

int main(){
    int t; cin >> t;
    for(int cases = 0; cases < t; cases++){
        int n, k; cin >> n >> k;
        set <pair<int, int>> time_position;
        vector<int> initial_time(n);
        vector<string> medication_names(n);

        for(int i = 0; i < n; i++){
            cin >> medication_names[i] >> initial_time[i];
            time_position.insert(make_pair(initial_time[i], i));
        }

        for(int i = 0; i < k; i++){
            pair <int, int> aux = *time_position.begin();
            cout << aux.first << " " << medication_names[aux.second] << endl;
            time_position.erase(aux);
            time_position.insert(make_pair(initial_time[aux.second]+aux.first,
                aux.second));
        }
    }

    return 0;
}