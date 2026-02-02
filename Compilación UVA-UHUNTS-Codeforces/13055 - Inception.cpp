#include <iostream>
#include <stack>
#include <vector>
#include <string>
using namespace std;

/*
    13055 - Inception
    Itzel Berenice Martinez Palacios

    Iniciamos un stack para resolver al problema, ya que como Dom Cobb
    viaja de suenio en suenio y necesita recordar el camino que ha viajado
    entre los suenios de las personas, nos damos cuenta que un stack es lo
    adecuado para resolver este problema.
    
    Para cada query tenemos tres opciones:
        * "Sleep", "nombre": Al tener esta query, sabemos que Dom Cobb viajo al
            suenio de "nombre", como lo queremos guardar en el camino, lo insertamos
            en el stack.
        * "Kick": Esta query nos indica que la persona en la que esta Dom Cobb actualmente
            se desperto, por lo que Dom Cobb tiene que salir de ese suenio, y quitamos 
            el ultimo elemento del stack con un pop() si el stack no esta vacio.
        * "Test": Aqui Dom Cobb quiere saber el nombre de la persona en la que se encuentra.
                => Si el stack no esta vacio, imprime el nombre de la ultima posicion del stack.
                => Si esta vacio, se imprime que no esta en un suenio.
        
*/

int main(){
    int n; cin >> n;
    string query;
    stack<string> people;
    for(int i = 0; i < n; i++){
        cin >> query;
        if(query == "Sleep"){
            string name; cin >> name;
            people.push(name);
        }
        else if(query == "Kick"){
            if(people.empty() != true){
                people.pop();
            }
        }
        else if(query == "Test"){
            if(people.empty() != true){
                cout << people.top() << endl;
            }
            else{
                cout << "Not in a dream" << endl;
            }
        }
    }

    return 0;
}