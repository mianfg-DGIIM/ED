/** 
 * @file Guia_Tlf.cpp
 * @brief Implementación del TDA Guía de Teléfonos
 * @author Miguel Ángel Fernández Gutiérrez <mianfg@correo.ugr.es>
 * @author Juan Manuel Mateos Pérez <jumape@correo.ugr.es>
 */

#include "Guia_Tlf.h"

istream & operator>>(istream &is,pair<string,string> &d){
    getline(is,d.first,'\t');
    getline(is,d.second);
    return is;
}

void Guia_Tlf::copiar(const Guia_Tlf &gt) {
    datos.insert(gt.datos.begin(), gt.datos.end());
}

Guia_Tlf::Guia_Tlf(const Guia_Tlf &gt){
    copiar(gt);
}

Guia_Tlf& Guia_Tlf::operator=(const Guia_Tlf &gt) {
    if ( this != &gt ) {
        clear();
        copiar(gt);
    }
    return *this;
}

string& Guia_Tlf::operator[](const string &nombre){
    return datos[nombre];
}

Guia_Tlf Guia_Tlf::operator+(const Guia_Tlf &gt) const {
    Guia_Tlf aux(*this);
    map<string, string>::const_iterator it;
    for (it = gt.datos.begin(); it != gt.datos.end(); ++it)
        aux.datos.insert(*it);
    return aux;
}

Guia_Tlf Guia_Tlf::operator-(const Guia_Tlf &gt) const {
    Guia_Tlf aux(*this);
    map<string, string>::const_iterator it;
    for (it = gt.datos.begin(); it != gt.datos.end(); ++it)
        aux.borrar(it->first, it->second);
    return aux;
}

std::ostream& operator<<(std::ostream &os, const Guia_Tlf &gt) {
    map<string, string>::const_iterator it;
    for (it = gt.datos.begin(); it != gt.datos.end(); ++it)
        os << it->first << "\t" << it->second << endl;
    return os;
}

std::istream& operator>>(std::istream &is, Guia_Tlf &gt) {
    pair<string,string> p;
    Guia_Tlf aux;

    while (is >> p)
        aux.insertar(p);
    gt = aux;
    return is;
}

string Guia_Tlf::getTelefono(const string &nombre) const {
    map<string, string>::const_iterator it = datos.find(nombre);
    if (it == datos.end())
        return string("");
    else
        return it->second;
}

unsigned int Guia_Tlf::contabiliza(const string &nombre) const{
    return datos.count(nombre);
}

int Guia_Tlf::size() const{
    return datos.size();
}

pair<map<string, string>::iterator, bool> Guia_Tlf::insertar(string nombre, const string &tlf) {
    pair<string, string> p(nombre, tlf);
    pair<map<string, string>::iterator, bool> ret;

    ret = datos.insert(p);
    return ret;
}

pair<map<string, string>::iterator, bool> Guia_Tlf::insertar(const pair<string, string> &p) {
    pair<map<string, string>::iterator, bool> ret;

    ret = datos.insert(p);
    return ret;
}

void Guia_Tlf::borrar(const string &nombre) {
    map<string, string>::iterator itlow = datos.lower_bound(nombre);   //el primero que tiene dicho nombre
    map<string, string>::iterator itupper = datos.upper_bound(nombre); //el primero que ya no tiene dicho nombre
    datos.erase(itlow, itupper);
}

void Guia_Tlf::borrar(const string &nombre, const string &tlf) {
    map<string, string>::iterator itlow = datos.lower_bound(nombre);   //el primero que tiene dicho nombre
    map<string, string>::iterator itupper = datos.upper_bound(nombre); //el primero que ya no tiene dicho nombre
    map<string, string>::iterator it;
    bool salir = false;
    for (it = itlow; it != itupper && !salir; ++it)
        if (it->second == tlf) {
            datos.erase(it);
            salir = true;
        }
}

void Guia_Tlf::clear(){
    datos.clear();
}

Guia_Tlf Guia_Tlf::prefijo(const string &pre) const {
    Guia_Tlf aux;
    map<string, string>::const_iterator it;

    bool insertar = true;
    for (it = datos.begin(); it != datos.end(); it++){
        insertar = true;
        if ( it->second.size() < pre.size() )
            insertar = false;
        else
            for(unsigned int i = 0; i<pre.size() && insertar; i++)
                if( pre[i] != it->second[i] )
                    insertar = false;
        
        if (insertar)
            aux.insertar(*it);
    }

    return aux;
}

list<string> Guia_Tlf::getNombres(const string &tlf) const {
    list<string> nombres;
    map<string, string>::const_iterator it;

    for ( it = datos.begin(); it != datos.end(); ++it )
        if ( (*it).second == tlf )
            nombres.push_back((*it).first);

    return nombres;
}

bool Guia_Tlf::modificarTelefono(const string &nombre, const string &tlf) {
    map<string, string>::iterator it;

    for ( it = datos.begin(); it != datos.end(); ++it )
        if ( (*it).first > nombre )
            return false;
        else
            if ( (*it).first == nombre ) {
                (*it).second = tlf;
                return true;
            }
    
    return false;
}