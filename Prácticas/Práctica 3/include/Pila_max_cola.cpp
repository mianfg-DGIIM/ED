/** 
 * @file Pila_max_cola.cpp
 * @brief Implementación de Pila_max (implementado con colas)
 * @author Miguel Ángel Fernández Gutiérrez <mianfg@correo.ugr.es>
 * @author Juan Manuel Mateos Pérez <jumape@correo.ugr.es>
 */

template<class T>
Pila_max<T>::Pila_max(const Pila_max<T> &pila) {
    datos = pila.datos;
}

template<class T>
Pila_max<T>::Pila_max(const Cola<elemento<T> > &cola) {
    datos = cola;
}

template<class T>
Pila_max<T>& Pila_max<T>::operator=(const Pila_max<T> &pila) {
    datos = pila.datos;
    return *this;
}

template<class T>
void Pila_max<T>::poner(const elemento<T> &elem) {
    elemento<T> aux;
    int n = datos.num_elementos();
    datos.poner(elem);
    for ( int i = 0; i < n; i++ ) {
        aux = datos.frente();
        datos.quitar();
        datos.poner(aux);
    }
}

template<class T>
void Pila_max<T>::poner(const T &el) {
    elemento<T> aux;
    aux.elem=el;
    if ( vacia() )
        aux.max = el;
    else
        if (el > tope().max)
            aux.max = el;
        else
            aux.max = tope().max;
    poner(aux);
}