#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

/*
    11356 - Dates
    Itzel Berenice Martinez Palacios

    Declaramos primero un arreglo y un vector para los dias y los meses en el calendario
    respectivamente.
    Tambien hacemos una funcion que dado un string llamado "month" recorre todo el vector
    de los meses hasta encontrar "month" en el, y regresa el indice.

    Por cada caso leemos la primera linea como un solo string y con la 
    funcion stoi pasamos el anio a entero, con la funcion "find_the_month" encontramos
    el indice en el vector de meses para el mes dado, y el dia lo leemos de nuevo con la funcion
    stoi.

    Checamos despues si el anio actual es bisiesto o no, en caso de serlo se actualiza el numero
    de dias correspondiente a febrero a 29, y en caso de serlo a 28.

    Hacemos un ciclo que se realiza k veces, en el vamos checando cautelosamente si 
    al aumentar un dia terminamos el mes actual, terminamos el anio actual, y vamos 
    actualizando valores de acuerdo a las anteriores condiciones.

    Para finalizar, imprimimos la respuesta para cada caso, y si el dia es de un solo digito,
    nos aseguramos de imprimir el dia con dos digitos.
*/

int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
vector<string> months = {"January", "February", "March", "April", "May", "June","July", "August", "September", "October", "November", "December"};

int find_the_month(string month){
    for(int i = 0; i < months.size(); i++)
        if(months[i] == month)
            return i;
}

int main(){
    int t; cin >> t;
    for(int cases = 0; cases < t; cases++){
        string date; cin >> date;
        int k; cin >> k;
        int year = stoi(date.substr(0,4));
        int month = find_the_month(date.substr(5,date.size()-8));
        int day = stoi(date.substr(date.size()-2,2));
        if((year%400 == 0) || ((year%4==0)&&(year%100!=0)))
            days[1] = 29;
        else days[1] = 28;

        while(k--){
            if(day+1>days[month]){
                day = 1;
                if(month+1 > 11){
                    month = 0;
                    year++;
                    if((year%400 == 0) || ((year%4==0)&&(year%100!=0)))
                        days[1] = 29;
                    else days[1] = 28;
                }
                else month++;
            }
            else day++;
        }
        cout << "Case " << cases+1 <<": " << year << "-" << months[month] << "-";
        if(day < 10)
            cout << "0"<< day << endl;
        else cout << day << endl;
    }
    return 0;
}