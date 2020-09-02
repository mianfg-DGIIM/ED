/**
 * @file Guia_Tlf.h
 * @brief Fichero cabecera del TDA Guía de Teléfonos
 * @author Miguel Ángel Fernández Gutiérrez <mianfg@correo.ugr.es>
 * @author Juan Manuel Mateos Pérez <jumape@correo.ugr.es>
 */

#ifndef __GUIA_TLF_H__
#define __GUIA_TLF_H__

#include <iostream>
#include <string>
#include <map>
#include <list>

using namespace std;

/*
 * @brief Sobrecarga del operador de entrada
 * @param os: flujo de entrada
 * @param d: pair a leer
 * @return Referencia al flujo de entrada
 */
istream& operator>>(istream &is,pair<string,string> &d);

/**
 * @brief T.D.A. Guía de Teléfonos
 * 
 * Tipo elemento que define una guia de tlf. Cosnta de un objeto de tipo map de la stl, que es 
 * un contenedor que almacena elementos formados por:
 *      *) Un valor clave: que se usa para ordenar e idnetificar de forma unica cada elemento.
 *      *) Un valor asignado : que alamcenan el contenido asociado a esta clave.
 * 
 * @authors Miguel Ángel Fernández Gutiérrez y Juan Manuel Mateos Pérez
 * @date diciembre 2018
 */
class Guia_Tlf {
private:
    map<string, string> datos;  // si admites que haya nombres repetidos, se usa multimap

    // ------------ Funciones auxiliares -----

    /**
     * @brief Copia todos los elementos de @a gt en el *this
     */
    void copiar(const Guia_Tlf &gt);

public:

    // ------------ Constructores ------------

    /**
     * @brief Constructor por defecto
     */
    Guia_Tlf() : datos(map<string, string>()) {}

    /**
     * @brief Constructor por copia
     * @param gt: guía a copiar
     */
    Guia_Tlf(const Guia_Tlf &gt);

    // ------------ Destructor ---------------

    /**
     * @brief Destructor
     */
    ~Guia_Tlf() {}

    //  ------------ Sobrecargas --------------

    /**
     * @brief Sobrecarga del operador de asignación
     * @param D: guía que se asignará
     * @return Referencia a la guía
     */
    Guia_Tlf& operator=(const Guia_Tlf &gt);

    /**
     * @brief Sobrecarga del operador de acceso
     * @param nombre: nombre del elemento a acceder
     * @return Devuelve el valor asociado a un nombre, es decir, el teléfono
     */
    string& operator[](const string &nombre);

    /**
     * @brief Sobrecarga del operador suma: unión de guías
     * @param gt: guía que se une
     * @return Una nueva guía resultado de unirle al objeto la guía gt
     */
    Guia_Tlf operator+(const Guia_Tlf &gt) const;

    /**
     * @brief Sobrecarga del operador resta: diferencia de guías
     * @param gt: guía que se sustráe
     * @return Una nueva guía resultado sustraerle al objeto la guía gt
     */
    Guia_Tlf operator-(const Guia_Tlf &gt) const;

    /**
     * @brief Sobrecarga del operador de salida
     * @param os: flujo de salida
     * @param gt: guía a escribir
     * @return Referencia al flujo de salida
     */
    friend std::ostream& operator<<(std::ostream &os, const Guia_Tlf &gt);

    /**
     * @brief Sobrecarga del operador de salida
     * @param os: flujo de entrada
     * @param gt: guía a leer
     * @return Referencia al flujo de salida
     */
    friend std::istream& operator>>(std::istream &is, Guia_Tlf &gt);

    // ------------ Observadores -------------

    /**
     * @brief Retorna el teléfono asociado a @a nombre
     * @note Esto es válido únicamente para @a map
     * @param nombre: nombre del que buscar su teléfono
     * @return El teléfono asociado a @a nombre
     */
    string getTelefono(const string &nombre) const;

    /**
     * @brief Contabiliza cuántos teléfonos tenemos asociados a un @a nombre
     * @note En @a map debe ser 0 o 1, en @a multimap puede retornar más de 1.
     * @param nombre: nombre sobre el que queremos consultar
     * @return Número de teléfonos asociados a un nombre
     */
    unsigned int contabiliza(const string &nombre) const;

    /**
     * @brief Devuelve el tamaño de la guía
     * @return El tamaño de la guía
     */
    int size() const;

    // ------------ Modificadores ------------

    /**
     * @brief Inserta un nuevo teléfono
     * @param nombre: clave del nuevo teléfono
     * @param tlf: número de teléfono
     * @return Un @a pair donde @a first apunta al nuevo elemento insertado y @a bool
     * es @a true si se ha insertado el nuevo teléfono, @a false en caso contrario
     */
    pair<map<string, string>::iterator, bool> insertar(string nombre, const string &tlf);

    /**
     * @brief Inserta un nuevo teléfono
     * @param p: @a pair con el nombre y el teléfono asociado
     * @return Un @a pair donde @a first apunta al nuevo elemento insertado y @a bool
     * es @a true si se ha insertado el nuevo teléfono, @a false en caso contrario
     */
    pair<map<string, string>::iterator, bool> insertar(const pair<string, string> &p);

    /**
     * @brief Borrar un teléfono
     * @note En caso de que fuese @a multimap borraría todos con ese nombre
     * @param nombre: nombre que se quiere borrar
     */
    void borrar(const string &nombre);

    /**
     * @brief Borrar un teléfono
     * @note Esta función nos permite borrar únicamente aquel que coincida en nombre y teléfono
     * @param nombre: nombre que se quiere borrar
     * @param tlf: teléfono asociado
     */
    void borrar(const string &nombre, const string &tlf);

    /**
     * @brief Limpia la guía
     */
    void clear();

    // ------- ==> MÉTODOS AÑADIDOS ----------

    /*
     * Se han añadido, además de los métodos listados a continuación, los siguientes:
     *   - La sobrecarga de operator<<
     * Todos ellos han sido implementados en líneas anteriores.
     */

    /**
     * @brief Busca todos los teléfonos que comiencen por un cierto prefijo
     * Dos claves son sinónimas si alguna de sus informaciones asociadas coincide.
     * @param pre: prefijo que se desea buscar
     * @return Una nueva guía únicamente con los nombres con teléfonos que comiencen
     * por el prefijo especificado
     */
    Guia_Tlf prefijo(const string &pre) const;

    /**
     * @brief Devuelve todos los @a nombres con teléfono asociado @a tlf
     * @param tlf: teléfono del que se quieren averiguar sus nombres
     * @return Lista con todos los nombres
     */
    list<string> getNombres(const string &tlf) const;

    /**
     * @brief Modificar teléfono asociado a un nombre
     * @param nombre: nombre del que se desea modificar su teléfono
     * @param tlf: nuevo teléfono
     * @return Si se ha podido modificar el teléfono
     */
    bool modificarTelefono(const string &nombre, const string &tlf);
};

#endif