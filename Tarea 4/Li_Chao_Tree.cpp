#include <bits/stdc++.h>
#include <complex>
using namespace std;

typedef long long ftype;
typedef complex<ftype> point;
#define x real
#define y imag

ftype dot(point a, point b) {
    return (conj(a) * b).x();
}

ftype f(point a,  ftype x) {
    return dot(a, {x, 1});
}
const int maxn = 2e5;

point line[4 * maxn];

// Funcion que inicializa el árbol para que no tenga
// problemas con las comparaciones en las demas funciones
void ini_tree(){
    for(int i = 0; i < 4*maxn; i++){
        line[i] = {0, INF}; // Le asigna a cada nodo 'infinito'
    }
}

void add_line(point nw, int v = 1, int l = 1, int r = maxn){
    int m = (l + r) / 2;
    bool lef = f(nw, l) < f(line[v], l);
    bool mid = f(nw, m) < f(line[v], m);
    if(mid) {
        swap(line[v], nw); 
    }
    if(r - l == 1) {
        return;
    } else if(lef != mid) {
        add_line(nw, 2 * v, l, m);
    } else {
        add_line(nw, 2 * v + 1, m, r);
    }
}

ftype get(int x, int v = 1, int l = 0, int r = maxn) {
    int m = (l + r) / 2;
    if(r - l == 1) {
        return f(line[v], x);
    } else if(x < m) {
        return min(f(line[v], x), get(x, 2 * v, l, m));
    } else {
        return min(f(line[v], x), get(x, 2 * v + 1, m, r));
    }
}