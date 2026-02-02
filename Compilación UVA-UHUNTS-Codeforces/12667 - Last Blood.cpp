#include <iostream>
#include <vector>

/*
    12667 - Last Blood
    Itzel Berenice Martinez Palacios

    Cuando en competencias de programacion un equipo resuelve por primera vez un
    problema, a esto se le llama "Last Blood".
    Lo que nos piden es encontrar el ultimo last blood de cada problema en el 
    concurso, es decir, el ultimo envio para cada problema que fue el primer
    envio aceptado de algun equipo.

    Para esto creamos dos vectores del tamanio de la cantidad de problemas a realizar
        * team_that_solved: Guarda en su posicion i, al ultimo equipo que resolvio por
                primera vez el problema i.
        * time_for_problem: Guarda en su posicion i, el tiempo del ultimo equipo que
                resolvio por primera vez el problema i (inicializado en -1).
    Tambien tenemos al vector booleano "scores" que guarda en su posiicon (i,j) si el 
    equipo i ya resolvio el problema j o no.

    Para cada una de los m envios que nos dan, si notamos que el envio fue
    aceptado, entonces checamos en el vector "scores" si el equipo actual ya habia resuelto
    ese problema antes o no, si no lo habia resuelto, registramos en "scores" que ya lo hizo
    y guardamos en los vectores "team_that_solved" y "time_for_problem" el nombre del equipo
    actual y el tiempo en que lo resolvio.

    Terminando de leer los envios, recorremos el vector time_for_problem para cada problema:
        * Si el valor que guarda "time_for_problem" es -1, significa que nadie resolvio dicho
            problema.
        * En caso contrario, imprimimos el valor de "time_for_problem" y el nombre del equipo
            que se guarda en "team_that_solved"
*/

using namespace std;
int main(){
    int n, t, m; cin >> n >> t >> m;
    vector<int> team_that_solved(n+1);
    vector<int> time_for_problem(n+1, -1);
    bool scores[101][15] = {};
    for(int i = 0; i < m; i++){
        int time, id; string result; char problem;
        cin >> time >> id >> problem >> result;
        if(result[0] == 'Y'){
            if(scores[id][problem - 'A'] == 0){
                scores[id][problem - 'A'] = true;
                team_that_solved[problem - 'A'] = id;
                time_for_problem[problem - 'A'] = time;
            }
        }
    }
    for(int i = 0; i < n; i++){
        if(time_for_problem[i] == -1)
            cout << char(i+'A') << " - -" << endl;
        else
            cout << char(i+'A') << " " << time_for_problem[i] << " " << team_that_solved[i] << endl;
    }

    return 0;
}