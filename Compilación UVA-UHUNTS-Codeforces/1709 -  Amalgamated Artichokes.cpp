#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

/*
    1709 -  Amalgamated Artichokes
    Itzel Berenice Martinez Palacios

    Iniciamos con ciclo while que se mantiene activo mientras pueda
    leer los 6 enteros de interes, nuestro mayor valor al iniciar, 
    es cuando en la funcion dada sustituimos k por 1, por lo tanto
    lo calculamos y lo guardamos en "max". Tambien inicializamos una
    variable "ans" = 0 que será nuestra respuesta.

    Despues por cada tiempo que pase comenzando por k = 2 (ya que ya
    habíamos calculado el valor cuando k = 1) volvemos a calcular el
    resultado de la funcion, comparamos si la diferencia entre el
    "max" y el resultado de la funcion es mayor que la respuesta
    guardada en "ans", si si lo es sustituimos "ans" por esta diferencia
    tambien si el resultado de la funcion actual es mayor que "max", 
    sustituimos "max" por este valor.

    Despues de cada caso de prueba, ajustamos una precision de 9 digitos
    despues del punto decimal e imprimos la respuesta en "ans".
*/

int main(){
    int p, a, b, c, d, n;
    while (cin >> p >> a >> b >> c >> d >> n) {
        double max = p*(sin(a+b)+ cos(c+d)+2);
        double ans = 0;
        for(int i = 2; i <= n; i++){
            double actual = p*(sin(a*i + b) + cos(c*i + d)+2);
            if(max - actual > ans)
                ans = max - actual;
            if(actual > max) max = actual;
        }

        cout << " " << fixed << setprecision(9) << ans << endl;
    }

    return 0;
}