#include "ArbolBinario.h"
#include "bintree.h"
#include <set>


void max_subtree_aux(const ArbolBinario<int>::Nodo &n, int cuenta, int &maximo) {
    cout << "Iterando nodo et=" << n->etiqueta << " cuenta=" << cuenta << " maximo=" << maximo << endl;
    if ( n->drcha == NULL && n->izqda == NULL ) {
        cout << "Encontrado fin cuenta=" << cuenta << endl;
        if ( cuenta > maximo )
            maximo = cuenta;
    } else {
        if ( !(n->izqda == NULL) ) {
            cuenta += n->izqda->etiqueta;
            max_subtree_aux(n->izqda, cuenta, maximo);
    	}
        if ( !(n->drcha == NULL) ) {
            cuenta += n->drcha->etiqueta;
            max_subtree_aux(n->drcha, cuenta, maximo);
        }
    }
}

int max_subtree2(const ArbolBinario<int>& T) {
    int maximo = T.raiz()->etiqueta;    
    max_subtree_aux(T.raiz(), T.raiz()->etiqueta, maximo);
    return maximo;
}

/*
devuelve la suma de etiquetas max de todos los posibles subarboles


*/

int puntuacionSubarbol(ArbolBinario<int>::Nodo n, int & suma){
  if(n != 0){
    suma = suma + n->etiqueta;
    puntuacionSubarbol(n->drcha, suma);
    puntuacionSubarbol(n->izqda, suma);
  }
  return suma;
}

void RecorrersubArbol(ArbolBinario<int>::Nodo n, set<int> & set_suma){
  if ( n != 0){
    int suma = 0;
    int num_ins = puntuacionSubarbol(n, suma);
    set_suma.insert(num_ins);
    cout << *(set_suma.begin()) << endl;
    RecorrersubArbol(n->drcha, set_suma);
    RecorrersubArbol(n->izqda, set_suma);
  }
}

int max_subtree(ArbolBinario<int> & T){
  set<int> set_suma;
  ArbolBinario<int>:: Nodo n;
  n = T.raiz();
  RecorrersubArbol(n, set_suma);
  return (*set_suma.rbegin());
}








int main(){
  ArbolBinario<int> arbol;
  cout << "Intriduce arbol" << endl;
  cin >> arbol;
  cout << arbol << endl;
  cout << "La puntuacion max es " << max_subtree(arbol) << endl;
    cout << "tb: " << max_subtree2(arbol) << endl;
}