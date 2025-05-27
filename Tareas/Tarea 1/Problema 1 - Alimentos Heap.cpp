#include <iostream>
#include <vector>
#include <unordered_map>

/*
    Tarea 1 - Updatable Heap.
    Itzel Berenice Martinez Palacios.
    Estructuras de Datos y Algoritmos.
*/


using namespace std;
// Inicio de la clase UpdatableHeap
template <class TPriority , class TKey> 
class UpdatableHeap{
    private:
        vector <pair<TPriority,TKey>> heap;
        unordered_map <TKey, long long> id2pos;
    public: 
        void up_heapify(long long int i){
            long long actual = i;
            long long par = parent(i);

            if(actual > 0 && heap[actual] > heap[par]){
                id2pos[heap[actual].second] = par;
                id2pos[heap[par].second] = actual;
                swap(heap[actual], heap[par]);
                up_heapify(par);
            }
        }
        void down_heapify(long long int n, long long int i){
            long long nodo = i;
            long long int l = left(i);
            long long int r = right(i);
            long long int maxi = i;

            if (r < n && heap[r] > heap[maxi])
                maxi = r;
            if (l < n && heap[l] > heap[maxi])
                maxi = l;

            if(maxi != nodo){
                id2pos[heap[maxi].second] = nodo;
                id2pos[heap[nodo].second] = maxi;
                swap(heap[maxi], heap[nodo]);
                down_heapify(n, maxi);
            }
        }
            // Calcula el indice del padre.
                long long int parent(long long int i){
                    if(i == 0){
                        return -1;
                    }
                    return (i - 1) / 2;
                }
            // Calcula el indice del hijo izquierdo.
                long long int left(long long int i){
                    return 2 * i + 1;
                }
            // Calcula el indice del hijo derecho.
                long long int right(long long int i){
                    return 2 * i + 2;
                }

    // LISTA
        // Devuelve el elemento de mayor prioridad.
        pair<TPriority, TKey> top(void) const{
            return heap.front();
        }
    // LISTA
        //  Elimina el elemento de mayor prioridad.
        void pop(){
            if(heap.empty()) return;
            id2pos.erase(heap[0].second);
            heap[0] = heap.back();
            heap.pop_back();
            if (!heap.empty()) {
                id2pos[heap[0].second] = 0;
                down_heapify(heap.size(), 0);
            }
        }
    // LISTA
        // Inserta un nodo con prioridad p y clave k, si ya existia 
        // un nodo con clave k, se actualiza para tener la nueva prioridad.
         void insertOrUpdate(const TPriority &p, const TKey &k){
            if(!isInserted(k)){
                heap.push_back({p, k});
                long long int i = heap.size()-1;
                id2pos[k] = i;
                up_heapify(i);
            }
            else{
                long long position = id2pos[k];
                heap[position].first = p;
                down_heapify(heap.size(), position);
                up_heapify(position);
            }
        }
    // LISTA
        // Devuelve true si la clave k esta en el heap o false en caso contrario.
        bool isInserted(const TKey &k) const{
            if(id2pos.find(k) != id2pos.end())
                return true;
            else
                return false;
        }
    // LISTA
        // devuelve el numero de elementos que contiene el heap actualmente
        int getSize() const{
            return heap.size();
        }
    // SIN EMPEZAR
        // borra el nodo con clave k. En caso de que no exista dicho nodo,}
        // no hace nada.
        void erase(const TKey &K){
            if(id2pos.find(K) == id2pos.end()) return;
            if(heap.empty()) return;
            long long position = id2pos[K];
            id2pos[heap[getSize()-1].second] = position;
            swap(heap[position], heap[getSize()-1]);
            id2pos.erase(K);
            heap.pop_back();
            down_heapify(heap.size(), position);
            up_heapify(position);
        }
};

int main(){

    int OP;
    string tipo;
    cin >> OP;
    UpdatableHeap <long long, string> heap;
    for(int i=0; i<OP; i++){
        cin >> tipo;
        // Imprime el nombre de alimento de mayor valor, junto a su valor
        if(tipo == "P"){ 
            if(heap.getSize() == 0)
                cout << "-1" << endl;
            else{
                pair <long long, string> mayor = heap.top();
                cout << mayor.second << " " << mayor.first << endl;
            }
        }
        // Inserta el alimento con el valor dado. Si ya existe, se actualiza el valor.
        else if(tipo == "IU"){
            string nombre;
            long long valor;
            cin >> nombre >> valor;
            heap.insertOrUpdate(valor, nombre);
        } 
        // Elimina el alimento de mayor valor, en caso de empate 
        // se elimina por orden lexicografico.
        else if(tipo == "DL"){
            heap.pop();
        }
        // Se elimina el alimento de la base de datos.
        else if(tipo == "D"){
            string nombre;
            cin >> nombre;
            heap.erase(nombre);
        }
    }

    return 0;
}
