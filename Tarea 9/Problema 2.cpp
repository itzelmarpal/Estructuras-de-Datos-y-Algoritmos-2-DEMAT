#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>
using namespace std;

/*
    Itzel Berenice Martinez Palacios
    Estructuras de Datos y Algoritmos 2
    Tarea 10
    Problema 2
*/

// Estructura de punto 
struct Point{
    int x, y;
    Point(){x = y = 0;} // Constructor vacio
    Point(int _x , int _y) : x(_x) , y(_y) {} // Constructor con parametros
    // Igualdad entre puntos
    bool operator == (const Point &other) const {return (x == other.x && y == other.y);} 
    // Suma de puntos
    Point operator+(const Point &p) const { return Point(x + p.x, y + p.y); } 
    // Resta de puntos
    Point operator-(const Point &p) const { return Point(x - p.x, y - p.y); } 
    // Producto cruz
    long long cross(const Point &p) const { return (long long)x * p.y - (long long)y * p.x; } 
    // Producto punto
    long long dot(const Point &p) const { return (long long)x * p.x + (long long)y * p.y; }
    // Producto cruz con 2 parametros
    long long cross(const Point &a, const Point &b) const { return (a - *this).cross(b - *this); } 
    long long sqrLen() const { return this->dot(*this); } // Norma del vector
};

// Variables globales
int NUM;
vector <Point> poly;
Point translation;

// Devuelve el signo de un numero (1 si es postivo, 0 si es cero, -1 si es negativo)
int sgn(long long val) { return val > 0 ? 1 : (val == 0 ? 0 : -1); }

// Compara dos puntos, primero por la coordenada x y luego por la y
bool lexComp(const Point &l, const Point &r) {
    if (l.x != r.x) return l.x < r.x;
    return l.y < r.y;
}

// La funcion se asegura de que el vector de puntos este ordenado lexicograficamente del menor
// al mayor, y calcula los vectores p_i - p_0
void prepare(vector<Point> &points) {
    int n = points.size()-1;
    // Si son solo 3 vertices, el proceso siguiente no puede hacerse y se regresa
    if(n < 3){
        NUM = 0;
        poly.clear();
        return;
    }
    
    // Se crea un nuevo vector de puntos y se copian los puntos anteriormente dados
    vector<Point> distinct(n);
    for (int i = 0; i < n; ++i) {
        distinct[i] = points[i];
    }

    // Se encuentra el punto lexicograficamente menor y se guarda el menor de todos
    int pos = 0;
    for (int i = 1; i < n; i++) {
        if (lexComp(distinct[i], distinct[pos]))
            pos = i;
    }

    // Se rota el vector de tal manera que el primer punto sea el lexicograficamente mas chico,
    // tambien calcula los vectores relativos
    rotate(distinct.begin(), distinct.begin() + pos, distinct.end());
    translation = distinct[0];
    NUM = n-1;
    poly.resize(NUM);
    for (int i = 0; i < NUM; i++) // Se calcula el vector p_i - p_0, para todo i
        poly[i] = distinct[i + 1] - translation;   
}

// Verifica si un punto esta dentro de un triángulo
bool pointInTriangle(Point a, Point b, Point c, Point point) {
    long long s1 = abs(a.cross(b, c));
    long long s2 = abs(point.cross(a, b)) + abs(point.cross(b, c)) + abs(point.cross(c, a));
    return s1 == s2;
}

// Nos dice si un punto esta dentro de un poligono convexo usando busqueda binaria
bool pointInConvexPolygon(Point point) {
    // Si no esta entre la primer arista y la ultima del poligono, se rechaza al punto
    point = point - translation;
    if (poly[0].cross(point) != 0 &&
            sgn(poly[0].cross(point)) != sgn(poly[0].cross(poly[NUM - 1])))
        return false;
    if (poly[NUM - 1].cross(point) != 0 &&
            sgn(poly[NUM - 1].cross(point)) != sgn(poly[NUM - 1].cross(poly[0])))
        return false;
    // Si el punto es colineal con la primer arista
    if (poly[0].cross(point) == 0)
        return poly[0].sqrLen() >= point.sqrLen();

    // Busqueda binaria para encontrar el sector correcto
    int l = 0, r = NUM - 1;
    while (r - l > 1) {
        int mid = l +(r - l) / 2;
        if (poly[mid].cross(point) >= 0)
            l = mid;
        else
            r = mid;
    }
    int pos = l;
    // Checa si esta en el triangulo que se forma con los puntos encontrados
    return pointInTriangle(poly[pos], poly[pos + 1], Point(0, 0), point);
}
 
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Se leen los numeros de la primera linea de entrada 
    int n,m,k;
    cin >> n >> m >> k;

    // Si no es poligono, responde de acuerdo a ello y se termina el programa
    if (n < 3) {
        if (k == 0) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
        return 0;
    }

    // Se leen los puntos del poligono dado
    vector<Point> polygon(n);
    for(int i = 0 ; i < n; i++){
        cin >> polygon[i].x >> polygon[i].y;
    }
    vector<Point> preparePoints = polygon;
    if (n > 0) {
        preparePoints.push_back(polygon[0]);
    }

    prepare(preparePoints);
    int counter = 0; // Contador de cohetes dentro del poligono

    // Se leen los puntos en donde caen los cohetes
    for(int i = 0; i < m; i++){
        Point rocket;
        cin >> rocket.x >> rocket.y;
        if(pointInConvexPolygon(rocket))
            counter++;
    }

    // Responder "YES" en caso de que mas de k o k cohetes hayan caido
    // dentro del poligono, e imprimir "NO" en caso contrario
    if(counter >= k) cout << "YES" << endl;
    else cout << "NO" << endl;

    return 0;
}