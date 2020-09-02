#include "ArbolBinario.h"
#include <set>
#include <list>
#include<stack>
#include<queue>

void hijo_mayor_profundidad_aux(const ArbolBinario<int> &a, const ArbolBinario<int>::Nodo &nod, int profundidad, int &max_prof, ArbolBinario<int>::Nodo &nodo_max_prof) {
    cout << "Iterando aux: " << nod->etiqueta << " "<<profundidad<<" "<<max_prof<<" "<<nodo_max_prof->etiqueta<<endl;
    if ( nod != NULL )
        if ( nod->izqda == NULL && nod->drcha == NULL ) {
            // estamos ante un nodo hoja, comprobamos
            if ( profundidad > max_prof ) {
                max_prof = profundidad;
            	nodo_max_prof = nod;
            }
        } else {
			if ( nod->izqda != NULL )
            hijo_mayor_profundidad_aux(a, nod->izqda, profundidad+1, max_prof, nodo_max_prof);
            if ( nod->drcha != NULL )
            hijo_mayor_profundidad_aux(a, nod->drcha, profundidad+1, max_prof, nodo_max_prof);
        }
}

ArbolBinario<int>::Nodo hijo_mayor_profundidad(const ArbolBinario<int> &a) {
    ArbolBinario<int>::Nodo nod = a.raiz();
    int max_prof = 0;
    hijo_mayor_profundidad_aux(a, a.raiz(), 0, max_prof, nod);
    return nod;
}

bool depth_if(const ArbolBinario<int> &a) {
    ArbolBinario<int>::Nodo hijo_mas_prof = hijo_mayor_profundidad(a);
    cout << hijo_mas_prof->etiqueta<<endl;
    if ( hijo_mas_prof->etiqueta % 2 == 0 )
        return true;
    else
        return false;
}

void longest_path_aux(const ArbolBinario<int> &A, list<int> &L,
	const ArbolBinario<int>::Nodo &n, list<int> camino) {
    if ( n != NULL ) {
        if ( n->izqda == NULL && n->drcha == NULL ) {
            // estamos en una hoja: vemos si el camino es mayor
            if ( camino.size() > L.size() )
                L = camino;
        } else {
            if ( n->izqda != NULL ) {
                list<int> new_camino = camino;
                new_camino.push_back(n->izqda->etiqueta);
                longest_path_aux(A, L, n->izqda, new_camino);
            }
            if ( n->drcha != NULL ) {
                list<int> new_camino = camino;
                new_camino.push_back(n->drcha->etiqueta);
                longest_path_aux(A, L, n->drcha, new_camino);
            }
        }
    }
}

void longest_path(const ArbolBinario<int> &A, list<int> &L) {
    list<int> camino;
    ArbolBinario<int>::Nodo n = A.raiz();
    camino.push_back(n->etiqueta);
    longest_path_aux(A, L, n, camino);
}

int main(){
	ArbolBinario<int> arbol;
	cin>>arbol;
	cout<<arbol;
	list<int> longest;
	longest_path(arbol, longest);
	if (depth_if(arbol))
		cout << "truu";
	else
		cout << "fake";
	for ( auto it = longest.begin(); it != longest.end(); ++it )
		cout << *it << " ";
	cout << endl;
}
