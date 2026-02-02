#include <iostream>
#include <vector>
#include <algorithm>
#define INT_MAX 10000
using namespace std;
/*
    12965 - Angry Bids
    Itzel Berenice Martinez Palacios

    Iniciamos el problema leyendo la cantidad de casos que tenemos que
    realizar, para cada uno de ellos guardamos los precios que quieren los
    productores y los precios que quieren los consumidores en dos vectores
    y a partir de ellos "producers" y "consumers" respectivamente, creamos
    otro vector que contenga a los dos llamado "total" y procedemos a
    ordenar los tres vectores. Tambien insertamos el precio 0 al vector
    "total" ya que tambien tenemos que contemplarlo.

    Recorremos cada elemento del vector total, y para cada elemento
    tenemos que checar cuantos consumidores estan insatisfechos con el
    precio, y cuantos productores estan satisfechos, con esto podemos
    calcular la cantidad de personas enojadas con cada precio en "total".

    Para cada elemento de "total" calculamos la cantidad de personas
    enojadas y si es menor que la menor cantidad de personas enojadas
    hasta ahora, guardamos el valor y el precio. Como comparamos con un
    mayor estricto, es claro que en caso de empate guardaríamos al
    precio menor.

    Al finalizar de checar el vector "total" imprimimos la respuesta
    que guardamos en los enteros "ans_price" y "min_angry_people" y
    pasamos al siguiente caso.
*/
int main(){
    int t; cin >> t;
    for(int cases = 0; cases < t; cases++){
        int p,c; cin >> p >> c;
        vector<int> producers(p);
        vector<int> consumers(c);
        vector<int> total(p+c+1);
        for(int i = 0; i < p; i++){
            cin >> producers[i];
            total[i] = producers[i];
        }
        for(int i = 0; i < c; i++){
            cin >> consumers[i];
            total[p+1] = consumers[i];
        }
        total[p+c] = 0;

        sort(producers.begin(),producers.end());
        sort(consumers.begin(),consumers.end());
        sort(total.begin(),total.end());
        int ans_price = 0, min_angry_people = INT_MAX;
        int ind_prod = 0, ind_cons = 0;
        for(int i = 0; i < p+c+1; i++){
            int price = total[i];
            while(ind_prod < p && price >= producers[ind_prod]) ind_prod++;
            while(ind_cons < c && price > consumers[ind_cons]) ind_cons++;
            int angry = p-ind_prod+ind_cons;
            if(angry < min_angry_people){
                min_angry_people = angry;
                ans_price = price;
            }
        }
        cout << ans_price << " " << min_angry_people << endl;
    }

    return 0;
}