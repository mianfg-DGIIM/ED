/** 
 * @file Pila_max_cola.h
 * @brief Fichero cabecera de Pila_max (implementado con colas)
 * @author Miguel Ángel Fernández Gutiérrez <mianfg@correo.ugr.es>
 * @author Juan Manuel Mateos Pérez <jumape@correo.ugr.es>
 */

#ifndef __PILA_MAX_COLA_H_
#define __PILA_MAX_COLA_H_

#include "Cola.h"
#include <cassert>
#include <iostream>

/**
 * @brief T.D.A. elemento
 * Creamos este tipo de dato ya que necesitamos que la Pila_max (elemento que posteriormente declararemos)
 * este compuesta por un elem que indique el elemento que contiene y luego un max que indica cual es el elemento maximo de la pila en ese momento.
 * Veamos un ejemplo:
 * Si comenzamos introduciendo elemento 1, tomaria la forma <1,1> ya que 1 es el maximo porque no hay ningun elemento mas.
 * Luego, si introducimos elemento 2, encontrariamos lo siguiente: <1,1> <2,2> ya que ahora el nuevo maximo es 2.
 * Así, introduciendo el elemento 10 obtenemos: <1,1> <2,2> <10,10>
 * Y ahora si introducimos el elemento 5 nos damos cuenta de: <1,1> <2,2> <10,10> <5,10> ya que aunque hayamos introducido
 * el elemento 5 el elemento maximo sigue siendo 10.
 * 
 * @authors Miguel Ángel Fernandez Gutiérrez y Juan Manuel Mateos Pérez
 * @date Noviembre 2018
*/
template<typename T>
struct elemento {
    T elem;
    T max;
};

/**
 * @brief Sobrecarga del operador de salida para elemento
 * @param os Flujo de salida
 * @param el Elemento a escribir en salida
 * @return Referencia a flujo
 */
template<typename T>
std::ostream& operator<<(std::ostream &os, const elemento<T> &el) {
    os << el.elem << " (máx.=" << el.max << ")";
    return os;
}

/**
 * @brief T.D.A. Pila_max
 * 
 * Tipo de dato pila con funcionalidad añadida: mantener el máximo
 * de los elementos insertados en la pila junto con el elemento insertado
 * 
 * La idea de crear este tipo de dato es poder crear una Pila a partir de una Cola.
 * 
 * Una pila es una estructura de tipo LIFO en la que el último elemento que entra es el primero que sale de la siguiente forma:
 * Comienzo:
 * < >
 * Al añadir elemento ocurre lo siguiente:
 * <a1> ; <a1,a2> ; <a1,a2,a3> ; ... ; <a1, ... , an> ;
 * Y al eliminar los elementos ocurre esto:
 * <a1, ... , an-1> ; ... ; <a1, a2, a3> ; <a1, a2> ; <a1> ; <> ;
 * Así finaliza el proceso
 * 
 * En cambio una Cola es una estructura de tipo FIFO, esto es, el primer elemento qeu entra es el primero en salir.
 * Podemos comprobarlo en el siguiente ejemplo:
 * Añadimos elementos:
 * <> ; <a1> ; <a1,a2> ; <a1,a2,a3> ; ... ; <a1, ... , an> ;
 * Si eliminamos elementos llegamos a:
 * <a2, ... , an> ; <a3, ... , an> ; ... ; <an-1,an> ; <an> ; <> ;
 *
 * @authors Miguel Ángel Fernandez Gutiérrez y Juan Manuel Mateos Pérez
 * @date noviembre 2018
*/
template<class T>
class Pila_max {

    Cola<elemento<T> > datos;

        // ------------ Funciones auxiliares -----
        
        /**
         * @brief Poner un struct elemento en el tope de la pila
         * @param elem Elemento a poner en la pila
         */
        void poner(const elemento<T> &elem);

    public:
        // ------------ Constructores ------------

        /**
         * @brief Constructor por defecto
         */
        Pila_max() {}

        /**
         * @brief Constructor por copia
         * @param pila Pila que se copiará
         */
        Pila_max(const Pila_max &pila);

        /**
         * @brief Constructor por copia a partir de cola
         * @param cola Cola que se copiará
         */
        Pila_max(const Cola<elemento<T> > &cola);

        // ------------ Destructor ---------------

        /*
        * ~Pila_max()
        * No es necesario implementar el destructor,
        * ya que se llama al destructor de Cola
        */

        // ------------ Sobrecargas --------------

        /**
         * @brief Sobrecarga del operador de asignación
         * @param pila Pila que se asignará
         * @return Referencia a la pila
         */
        Pila_max& operator=(const Pila_max &pila);

        // ------------ Observadores -------------

        /**
         * @brief Comprueba si la pila está vacía
         * @return Si la pila está vacía
         */
        bool vacia() const {
            return datos.vacia();
        }

        /**
         * @brief Devuelve el tope de la pila
         * @return El tope de la pila
         */
        elemento<T>& tope() {
            assert(datos.num_elementos() > 0);  // si no tiene elementos, no devolvemos el tope
            return(datos.frente());
        }

        /**
         * @brief Devuelve el tope de la pila constante
         * @return El tope de la pila
         */
        const elemento<T>& tope() const {
            assert(datos.num_elementos() > 0);  // si no tiene elementos, no devolvemos el tope
            return(datos.frente());
        }

        /**
         * @brief Devuelve el número de elementos de la pila
         * @return Número de elementos de la pila
         */
        int size() const {
            return datos.num_elementos();
        }

        // ------------ Modificadores ------------

        /**
         * @brief Poner un elemento en el tope de la pila con el cálculo del máximo
         * @param elem Elemento a poner en la pila
         */
        void poner(const T &el);

        /**
         * @brief Quitar el elemento del tope de la pila
         */
        void quitar() {
            datos.quitar();
        }

        //friend std::ostream& operator<<(std::ostream &os, const Pila_max &pila);
};

#include "Pila_max_cola.cpp"

#endif
