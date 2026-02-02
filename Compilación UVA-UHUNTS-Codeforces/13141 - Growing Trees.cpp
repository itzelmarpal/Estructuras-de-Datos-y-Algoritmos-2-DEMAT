#include <iostream>
#include <vector>
using namespace std;
/*
    13141 - Growing Trees
    Itzel Berenice Martinez Palacios

    Por el comportamiento del arbol, nos damos cuenta que
    la cantidad de hojas que tendra el nivel i, van a ser la
    cantidad de hojas del nivel i-1 y las del nivel i-2, es
    decir, de una forma parecida a la serie de Fibonacci, 
    lo que hacemos entonces es precalcular la serie de Fibonacci
    y para cada entrada dada imprimimos el numero correspondiente
    hasta que la entrada sea cero, en ese caso, terminamos el programa.
*/
int main(){
    vector<int> tree(90);
    tree[0] = 0; tree[1] = 1;
    for(int i = 2; i < 90; i++){
        tree[i] = tree[i-1] + tree[i-2];
    }
    int inp_case; cin >> inp_case;
    while (inp_case != 0){   
        cout << tree[inp_case]<< endl;
        cin >> inp_case;
    }
    return 0;
}