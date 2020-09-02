/**
 * @file Diccionario.h
 * @brief Fichero cabecera del TDA Diccionario
 * @author Miguel Ángel Fernández Gutiérrez <mianfg@correo.ugr.es>
 * @author Juan Manuel Mateos Pérez <jumape@correo.ugr.es>
 */

#ifndef __DICCIONARIO_H__
#define __DICCIONARIO_H__

#include <iostream>
#include <string>
#include <list>

/**
 * @brief T.D.A. elemento
 * Tipo elemento que define el diccionario. @a T es el tipo de dato asociado a una clave que
 * no se repite (DNI p.ej.) y @a list<U> es una lista de datos (string p.ej) asociados a la clave
 * de tipo @a T. El diccionario está ordenado de menor a mayor clave.
 * 
 * @authors Miguel Ángel Fernández Gutiérrez y Juan Manuel Mateos Pérez
 * @date diciembre 2018
 */
template <class T, class U>
struct data {
	T clave;
	std::list<U> info_asoci;
};

/**
 * @brief Sobrecarga del operador de comparación
 * Ordena dos registros de acuerdo a la clave de tipo T. Puede usarse como funtor.
 * @return La relación de orden
 */
template <class T, class U>
bool operator<(const data<T, U> &d1, const data<T, U> &d2) {
	if (d1.clave < d2.clave)
		return true;
	return false;
}

/**
 * @brief T.D.A. Diccionario
 * 
 * Un diccionario es una lista de datos de los definidos anteriormente. Cuidado porque se
 * manejan listas de listas. Se añaden 2 funciones privadas que hacen más facil la implementación
 * de algunos operadores o funciones de la parte pública. Copiar copia un diccionario en
 * otro y borrar elimina todos los elementos de un diccionario. La implementación de copiar
 * puede hacerse usando iteradores o directamente usando la función @a assign.
 *
 * @authors Miguel Ángel Fernández Gutiérrez y Juan Manuel Mateos Pérez
 * @date diciembre 2018
 */
template <class T, class U>
class Diccionario {
private:
    std::list<data<T, U> > datos;

    // ------------ Funciones auxiliares -----

    /**
     * @brief Copia todos los elementos de @a D en el diccionario
     */
    void copiar(const Diccionario<T, U> &D);

    /**
     * @brief Borra todos los elementos del diccionario
     */
    void borrar();

public:

    // ------------ Constructores ------------

    /**
     * @brief Constructor por defecto
     */
    Diccionario() : datos(std::list<data<T, U> >()) {}

    /**
     * @brief Constructor por copia
     * @param D: diccionario a copiar
     */
    Diccionario(const Diccionario &D) {
        copiar(D);
    }

    // ------------ Destructor ---------------

    /**
     * @brief Destructor
     */
    ~Diccionario() {}

    //  ------------ Sobrecargas --------------

    /**
     * @brief Sobrecarga del operador de asignación
     * @param D: diccionario que se asignará
     * @return Referencia al diccionario
     */
    Diccionario<T, U>& operator=(const Diccionario<T, U> &D);

    /**
     * @brief Sobrecarga del operador suma: unión de diccionarios
     * @param D: diccionario a unir
     * @return El diccionario resultante de unir D con el propio diccionario
     */
    Diccionario<T, U> operator+(const Diccionario<T, U> &D) const;

    /**
     * @brief Sobrecarga del operador de salida
     * @param os: flujo de salida
     * @param D: diccionario a escribir
     * @return Referencia al flujo de salida
     */
    friend std::ostream& operator<<(std::ostream &os, const Diccionario &D) {
        typename std::list<data<T, U> >::const_iterator it;
        typename std::list<U>::const_iterator it2;

        for ( it = D.datos.begin(); it != D.datos.end(); ++it ) {
            os << (*it).clave << ':' << std::endl;
            for ( it2 = (*it).info_asoci.begin(); it2 != (*it).info_asoci.end(); ++it2 ) {
                os << '\t' << (*it2) << std::endl;
            }
            os << std::endl;
        }

        return os;
    }

    // ------------ Iteradores ---------------

    /**
     * @brief Iterador begin
     * @return Iterador begin
     */
    typename std::list<data<T, U> >::iterator& begin() {
		return datos.begin();
	}

    /**
     * @brief Iterador end
     * @return Iterador end
     */
	typename std::list<data<T, U> >::iterator& end() {
		return datos.end();
	}

    /**
     * @brief Iterador begin constante
     * @return Iterador begin constante
     */
	typename std::list<data<T, U> >::const_iterator begin() const {
		return datos.begin();
	}

    /**
     * @brief Iterador end constante
     * @return Iterador end constante
     */
	typename std::list<data<T, U> >::const_iterator end() const {
		return datos.end();
	}

    // ------------ Observadores -------------

    /**
     * @brief Busca la clave @p en el diccionario
     * Si está, devuelve un iterador a donde está la clave. Si no está, devuelve
     * @a end() y deja el iterador de salida apuntando al sitio donde debería estar la clave.
     * @param p: clave a buscar
     * @param it_out: iterador de salida
     * @return Si está la clave
     */
    bool estaClave(const T &p, typename std::list<data<T, U> >::iterator &it_out);

    /**
     * @brief Devuelve la información asociada
     * @param p: clave de la que se quiere devolver la información
     * @return Una lista con la información asociada a la clave
     */
    std::list<U> getInfo(const T &p);

    /**
     * @brief Devuelve el tamaño del diccionario
     * @return El tamaño del diccionario
     */
    int size() const {
        return datos.size();
    }

    // ------------ Modificadores ------------

    /**
     * @brief Inserta un nuevo registro en el diccionario
     * Lo hace a través de la clave @a clave e inserta la lista con toda la información
     * asociada a esa clave. Si el diccionario no estuviera ordenado habría que usar la
     * función @a sort()
     * @param clave: clave en la que insertar lista
     * @param info: lista a insertar
     */
    void insertar(const T &clave, const std::list<U> &info);

    /**
     * @brief Añade una nueva información asociada a una clave que está en el diccionario
     * La nueva información se inserta al final de la lista de información. Si no está
     * la clave, la inserta y añade la información asociada.
     * @param s: información asociada
     * @param p: clave en la que insertar información
     */
    void addSignificado(const U &s, const T &p);

    // ------- ==> MÉTODOS AÑADIDOS ----------

    /*
     * Se han añadido, además de los métodos listados a continuación, los siguientes:
     *   - La sobrecarga de operator<<
     *   - Sobrecarga del operador suma: unión de diccionarios
     * Todos ellos han sido implementados en líneas anteriores.
     */

    /**
     * @brief Comprobar si dos claves son sinónimas
     * Dos claves son sinónimas si alguna de sus informaciones asociadas coincide.
     * @param clave1: primera clave
     * @param clave2: segunda clave
     * @return Si ambas claves son sinónimas
     */
    bool sinonimos(const T &clave1, const T &clave2);

    /**
     * @brief Buscar todas las claves que comiencen por cierto prefijo
     * @param pref: prefijo
     * @return Una lista con todas las claves que comienzan por @a pref
     */
    std::list<T> prefijo(const T &pref) const;

    /**
     * @brief Ordena los registros de una clave específica
     * @param clave: clave de la que se quieren ordenar sus registros
     * @return Si se han podido ordenar (será @a false si no existe la clave)
     */
    bool ordenar(const T &clave);
};

#include "Diccionario.cpp"

#endif