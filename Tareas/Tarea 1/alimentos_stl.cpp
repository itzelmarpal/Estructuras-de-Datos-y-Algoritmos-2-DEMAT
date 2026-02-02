#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
using namespace std;

/*
    Tarea 1 - STL.
    Itzel Berenice Martinez Palacios.
    Estructuras de Datos y Algoritmos.
*/

int main (){

    // Se crea el set "valores" para ordenar los alimentos dando prioridad al valor
    // y despues al orden lexicografico. 
    // Tambien se crea el map alimentos para hacer eficiente la busqueda por nombre.
      set <pair<int, string>> valores;
      map <string, int> alimentos;
      
      int n;
      cin >> n;
      string op;
      for(int i = 0; i<n; i++){
            cin >> op;
            if(op == "P"){ // Se imprime el alimento de mayor valor.
                  if(alimentos.empty()){
                        cout << "-1" << endl;
                  }
                  else{
                       auto it = --valores.end(); 
                       cout << it->second << " " << it->first << endl;
                  }
            }
            else if(op == "IU"){ // Se inserta un alimento con un valor dado.
                  string alimento;
                  int valor;
                  cin >> alimento >> valor;
                  if(alimentos.count(alimento))
                        valores.erase({alimentos[alimento], alimento});
                  alimentos[alimento] = valor;
                  valores.insert({valor, alimento});
            }
            else if(op == "DL"){ // Se elimina el alimento con mayor valor.
                       if(!alimentos.empty()){
                             auto it = -- valores.end();
                             alimentos.erase(it->second);
                             valores.erase(it); 
                       }
            }
            else if(op == "D"){ // Se elimina una alimento dado de la Base de Datos.
                  string alimento;
                  cin >> alimento;
                  if(alimentos.count(alimento)){
                        valores.erase({alimentos[alimento], alimento});
                        alimentos.erase(alimento);
                  }
            }
      }  
      return 0;      
}