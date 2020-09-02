/** 
 * @file Diccionario.cpp
 * @brief Implementación del TDA Diccionario
 * @author Miguel Ángel Fernández Gutiérrez <mianfg@correo.ugr.es>
 * @author Juan Manuel Mateos Pérez <jumape@correo.ugr.es>
 */

template <class T, class U>
void Diccionario<T, U>::copiar(const Diccionario<T, U> &D) {
    datos.assign(D.datos.begin(), D.datos.end());
}

template <class T, class U>
void Diccionario<T, U>::borrar() {
    this->datos.erase(datos.begin(), datos.end());
}

template <class T, class U>
Diccionario<T, U>& Diccionario<T, U>::operator=(const Diccionario<T, U> &D) {
    if ( this != &D ) {
        borrar();
        copiar(D);
    }
    return *this;
}

template <class T, class U>
Diccionario<T, U> Diccionario<T, U>::operator+(const Diccionario<T, U> &D) const {
    Diccionario<T, U> aux(*this);
    typename std::list<data<T, U> >::const_iterator it;

    for (it = D.datos.begin(); it != D.datos.end(); ++it) {
        aux.insertar((*it).clave, (*it).info_asoci);
    }

    return aux;
}

template <class T, class U>
bool Diccionario<T, U>::estaClave(const T &p, typename std::list<data<T, U> >::iterator &it_out) {
    if (datos.size() > 0) {
        typename std::list<data<T, U> >::iterator it;

        for (it = datos.begin(); it != datos.end(); ++it)
            if ((*it).clave == p) {
                it_out = it;
                return true;
            } else if ((*it).clave > p) {
                it_out = it;
                return false;
            }

        it_out = it;
        return false;
    } else {
        it_out = datos.end();
        return false;
    }
}

template <class T, class U>
std::list<U> Diccionario<T, U>::getInfo(const T &p) {
    typename std::list<data<T, U> >::iterator it;

    if ( !estaClave(p, it) )
        return std::list<U>();
    else
        return (*it).info_asoci;
}

template <class T, class U>
void Diccionario<T, U>::insertar(const T &clave, const std::list<U> &info) {
    typename std::list<data<T, U> >::iterator it;

    if ( !estaClave(clave, it) ) {
        data<T, U> p;
        p.clave = clave;
        p.info_asoci = info;

        datos.insert(it, p);
    } else {
        typename std::list<U>::const_iterator it2;
        for ( it2 = info.begin(); it2 != info.end(); ++it2 )
            (*it).info_asoci.push_back(*it2);
    }
}

template <class T, class U>
void Diccionario<T, U>::addSignificado(const U &s, const T &p) {
    typename std::list<data<T, U> >::iterator it;

    if ( !estaClave(p, it) ) {
        data<T, U> dat;
        dat.clave = p;
        dat.info_asoci.clear();
        dat.info_asoci.push_back(s);
        datos.insert(it, dat);
    } else
        // insertamos el significado al final
        (*it).info_asoci.push_back(s);
}

template <class T, class U>
bool Diccionario<T, U>::sinonimos(const T &clave1, const T &clave2) {
    typename std::list<data<T, U> >::iterator it1;	// iterador a la clave 1
    typename std::list<data<T, U> >::iterator it2;	// iterador a la clave 2
    if ( !estaClave(clave1, it1) || !estaClave(clave2, it2) )
        return false;
        
    typename std::list<U>::const_iterator it_i1;	// iterador a info_asociada de clave 1
    typename std::list<U>::const_iterator it_i2;	// iterador a info_asociada de clave 2

    for ( it_i1 = (*it1).info_asoci.begin(); it_i1 != (*it1).info_asoci.end(); ++it_i1 )
        for ( it_i2 = (*it2).info_asoci.begin(); it_i2 != (*it2).info_asoci.end(); ++it_i2 )
            if ( (*it_i1) == (*it_i2) )
                return true;

    return false;
}

template <class T, class U>
std::list<T> Diccionario<T, U>::prefijo(const T &pref) const {
    typename std::list<T> claves;
    typename std::list<data<T, U> >::const_iterator it;
    
    bool insertar = true;
    for ( it = datos.begin(); it != datos.end(); ++it ) {
        insertar = true;
        if ( it->clave.size() < pref.size() )
            insertar = false;
        else
            for ( unsigned int i = 0; i < pref.size() && insertar; i++ )
                if ( pref[i] != it->clave[i] )
                    insertar = false;
        
        if (insertar) {
            claves.push_back(it->clave);
        }
    }
    
    return claves;
}

template <class T, class U>
bool Diccionario<T, U>::ordenar(const T &clave) {
    typename std::list<data<T, U> >::iterator it;
    if ( !estaClave(clave, it) )
        return false;
    else
        (*it).info_asoci.sort();
    
    return true;
}