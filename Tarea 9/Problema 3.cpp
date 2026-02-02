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
    Problema 3
*/

// Estructura de vector 
struct vec{
    double x, y;
    vec() : x(0.0), y(0.0) {} // Constructor vacío
    vec(const double &_x, const double &_y) : x(_x), y(_y) {} // Constructor con valores dados
    vec operator+(const vec & v) const { return vec(x+v.x , y+v.y); } // Suma de vectores
    vec operator-(const vec & v) const { return vec(x-v.x , y-v.y); } // Resta de vectores
    double dot(const vec& v) const { return x * v.x + y * v.y; } // Producto punto
    double norm () const { return sqrt(x*x + y*y);} // Norma de un vector
    // Normalizar un vector
    vec normal() const { 
      double vec_norm = norm();
      if (vec_norm < EPS) return vec(0.0, 0.0);
      return vec(x/vec_norm, y/vec_norm);
  }
};

// Estructura para una linea ax^2 + bx + c con doubles
struct line{
  double a, b, c;
  line(const double _a, const double _b, const double _c) : a(_a), b(_b), c(_c) {}
};

// Calcula el vector normal perpendicular a un segmento y lo normaliza.
vec norm_ort(vec a, vec b){
  vec v = vec(-(b-a).y , (b-a).x).normal();
  return v;
}

// Calcula el punto de interseccion entre dos lineas usando la Regla de Cramer.
vec points_int(const line& l1, const line& l2){
    double cross_x = l1.b * l2.c - l1.c * l2.b;
    double cross_y = l1.c * l2.a - l1.a * l2.c;
    double cross_z = l1.a * l2.b - l1.b * l2.a;

    return vec(cross_x / cross_z, cross_y / cross_z);
}

// Solucion del problema, calcula el area del poligono recortado con una 
// distancia d como el problema lo pide
double cut_area(double d, int n, vector <vec> polygon){
  // Inicializamos un nuevo poligono que sera el poligono final
  vector<vec> new_poly;
  for(int i = 0; i < n; i++){
    // Para cada vertice del poligono original calculamos los vectores normales
    // perpendiculares del segmento actual y del siguiente
    vec v_1 = norm_ort(polygon[i], polygon[(i + 1) % n]);
    vec v_2 = norm_ort(polygon[(i + 1) % n], polygon[(i + 2) % n]);
    // Desplazamos el segmento actual y el siguiente con el d dado y lo guardamos en lineas
    line l1(v_1.x, v_1.y, -(polygon[i].dot(v_1) + d));
    line l2(v_2.x, v_2.y, -(polygon[(i + 1) % n].dot(v_2) + d));
    // Calculamos la interseccion de las lineas anteriormente desplazadas y calculamos su interseccion,
    // la guardamos despues como una estructura de vector, aunque lo trataremos como un punto
    vec push = points_int(l1, l2);
    // Agregamos este punto a la lista de vertices del nuevo poligono
    new_poly.push_back(push);
  }
  double ans = 0;
  // Utilizamos la formula vista en clase para calcular el area de poligonos convexos.
    for (int i = 0; i < new_poly.size(); i++) {
      ans += new_poly[i].x * new_poly[(i + 1) % n].y;
      ans -= new_poly[i].y * new_poly[(i + 1) % n].x;
    }
    return fabs(ans) * 0.5;
}

int main(){
  bool pass = true;
  double d;
  int n;
  while(pass){ // El while para hasta que ingresen dos ceros como entrada.
    cin >> d >> n; // Leemos los datos de entrada
    if(d == 0 && n == 0) pass = false;
    if(pass){
      vector<vec> points;
      points.resize(n);
      // Leemos los puntos del poligono
      for(int i = 0; i < n; i++){
        cin >> points[i].x >> points[i].y;
      }
      // Lo guardamos en sentido antihorario
      reverse(points.begin(), points.end());
      double answer = cut_area(d,n, points);
      // Imprimimos el resultado
      printf("%.3lf\n", answer) << '\n';
    }
  }
  return 0;
}