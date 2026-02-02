#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
#define EPS 1e-9

/*
    Itzel Berenice Martinez Palacios
    Estructuras de Datos y Algoritmos 2
    Tarea 10
    Problema 1
*/

// Estructura de punto 
struct Point{
    double x, y;
    Point(){x = y = 0;} // Constructor vacio
    Point(double _x , double _y) : x(_x) , y(_y) {} // Constructor con parametros
    Point operator + (const Point & p) const { // Sobrecarga del operador suma
        return Point{x + p.x, y + p.y};
    }
    Point operator - (const Point & p) const { // Sobrecarga del operador resta
        return Point{x - p.x, y - p.y};
    }
    long long cross(const Point & p) const { // Producto cruz con otro punto
        return x * p.y - y * p.x;
    }
};

// Compara dos puntos, primero por la coordenada y y luego por la x
bool lexComp(const Point &l, const Point &r) {
    if (l.y < r.y - EPS) return true;
    if (l.y > r.y + EPS) return false; 
    if (l.x < r.x - EPS) return true;
    return false; 
}

// Se encuentra el punto lexicograficamente menor y se guarda el menor de todos
void reorder_polygon(vector <Point> & p){
    int pos = 0;
    for (int i = 1; i < p.size(); i++) {
        if (lexComp(p[i], p[pos]))
            pos = i;
    }
    // Se rota el vector de tal manera que el primer punto sea el mas chico,
    // tambien calcula los vectores relativos
    rotate(p.begin(), p.begin() + pos, p.end());
}

// Calcula el angulo polar de p respecto a un origen o
double polarAngle(const Point &p, const Point &o) {
    return atan2(p.y - o.y, p.x - o.x); 
}

// Calcula la suma de Minkowski de dos polígonos convexos P y Q
vector<Point> minkowski(vector<Point> P, vector<Point> Q){
    int n_orig = P.size(); 
    int m_orig = Q.size();

    // Se reordenan los poligonos para que el punto inicial sea el menor
    reorder_polygon(P);
    reorder_polygon(Q);

    // Se asegura un ciclo en el poligono
    P.push_back(P[0]);
    Q.push_back(Q[0]);

    vector<Point> result;
    int i = 0, j = 0;

    // Suma de Minkowski
    while(i < n_orig || j < m_orig) {
        // Agregamos al vector la suma de los puntos actuales
        result.push_back(P[i] + Q[j]); 
        double angle_P = 1e18;
        // Calculamos angulos polares de las aristas actuales
        if (i < n_orig) {
            angle_P = polarAngle(P[i+1], P[i]);
        }
        double angle_Q = 1e18; 
        if (j < m_orig) {
            angle_Q = polarAngle(Q[j+1], Q[j]);
        }

        // Aumentar los indices dependiendo de la situacion
        if (fabs(angle_P - angle_Q) <= EPS && i < n_orig && j < m_orig) {
            i++; j++;
        }
        else if (angle_P < angle_Q - EPS || j >= m_orig ) {
            if (i < n_orig) i++; else break;
        } 
        else if (angle_Q < angle_P - EPS || i >= n_orig ) {
            if (j < m_orig) j++; else break;
        }
    }
    return result;
}


int main(){
    // Leer la entrada
    int n, m;
    cin >> n >> m;
    vector <Point> P(n);
    vector <Point> Q(m);

    for(int i = 0; i < n; i++)
        cin >> P[i].x >> P[i].y;

    for(int i = 0; i < m; i++)
        cin >> Q[i].x >> Q[i].y;
    
    // Realizar la suma de Minkowski entre los poligonos P y Q
    vector <Point> result = minkowski(P, Q);
    // Se imprimen los vertices resultantes
    for(int i = 0; i< result.size(); i++)
        cout << result[i].x << " " << result[i].y << endl;

    return 0;
}