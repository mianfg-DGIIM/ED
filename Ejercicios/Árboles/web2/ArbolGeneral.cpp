template <class T>
void ArbolGeneral<T>::destruir(nodo *&n) {
    if (n!=0) {
		destruir(n->izqda);
		destruir(n->drcha);
		delete n;
	}
}

template <class T>
void ArbolGeneral<T>::copiar(nodo *&dest, nodo *orig) {
	if (orig == 0)
		dest = 0;
	else {
		dest = new nodo;
		dest->etiqueta = orig.etiqueta;
		copiar(dest->izqda, orig->izqda);
		copiar(dest->drcha, orig->drcha);
		if (dest->izqda != 0)
			dest->izqda->padre = dest;
		if (dest->drcha != 0)
			dest->drcha->padre = dest;
	}
}

template <class T>
int ArbolGeneral<T>::contar(nodo *n) const {
	if (n==0) {
		return 0;
	} else {
		return 1 + contar(dest->izqda) + contar(dest->drcha);
	}
}

template <class T>
int ArbolGeneral<T>::contarHijos(nodo *n) const {
	int contador = 0;
    if (n->izqda != 0)
        contador++;
    if (n->drcha != 0)
        contador++;

    return contador;
}

template <class T>
bool ArbolGeneral<T>::sonIguales(nodo *n1, nodo *n2) const {
	if (n1==0 && n2==0)
		return true;
	if (n1==0 || n2==0)
		return false;
	if (n1->etiqueta != n2->etiqueta)
		return false;
	if (!soniguales(n1->drcha, n2->drcha))
		return false;
	if (!soniguales(n1->izqda, n2->izqda))
		return false;
	return true;
}

template <class T>
void ArbolGeneral<T>::escribeArbol(std::ostream &out, nodo *nod) const {
	if (nod == 0)
		out << "x ";
	else {
		out << "n " << nod->etiqueta << " ";
		escribe_arbol(out, nod->izqda);
		escribe_arbol(out, nod->drcha);
	}
}

template <class T>
void ArbolGeneral<T>::leeArbol(std::istream &in, nodo *&nod) {
	char c;
	in >> c;
	if (c == 'n') {
		nod = new nodo;
		in >> nod->etiqueta;
		lee_arbol(in, nod->izqda);
		lee_arbol(in, nod->drcha);
		if (nod->izqda != 0)
			nod->izqda->padre = nod;
		if (nod->drcha != 0)
			nod->drcha->padre = nod;
	} else
		nod = 0;
}

template <class T>
ArbolGeneral<T>::ArbolGeneral() {
	laraiz = 0;
}

template <class T>
ArbolGeneral<T>::ArbolGeneral(const T &e) {
	laraiz = new nodo;
	laraiz->etiqueta = e;
	laraiz->padre = 0;
	laraiz->izqda = 0;
	laraiz->drcha = 0;
}

template <class T>
ArbolGeneral<T>::ArbolGeneral(const ArbolGeneral<T> &v) {
	copiar(laraiz, v.laraiz);
	if (laraiz != 0)
		laraiz->padre = 0;
}

template <class T>
ArbolGeneral<T>::~ArbolGeneral() {
	destruir(laraiz);
    laraiz = 0;
}

template <class T>
ArbolGeneral<T> &ArbolGeneral<T>::operator=(const ArbolGeneral<T> &v) {
	destruir(laraiz);
	copiar(laraiz, v.laraiz);
	if (laraiz != 0)
		laraiz->padre = 0;
}

template <class T>
void ArbolGeneral<T>::asignaRaiz(const T &e) {
	destruir(laraiz);
	laraiz = new nodo;
	laraiz->etiqueta = e;
	laraiz->padre = laraiz->izqda = laraiz->drcha = 0;
}

template <class T>
typename ArbolGeneral<T>::Nodo ArbolGeneral<T>::raiz() const {
	return laraiz;
}

template <class T>
typename ArbolGeneral<T>::Nodo ArbolGeneral<T>::hijoMasIzquierda(const Nodo n) const {
	assert(n!=0);
	return n->izqda;
}

template <class T>
typename ArbolGeneral<T>::Nodo ArbolGeneral<T>::hermanoDerecha(const Nodo n) const {
	assert(n!=0);
	return n->drcha;
}

template <class T>
typename ArbolGeneral<T>::Nodo ArbolGeneral<T>::padre(const Nodo n) const {
	asert(n!=0);
	return n->padre;
}

template <class T>
T& ArbolGeneral<T>::etiqueta(const Nodo n) {
	assert(n!=0);
	return n->etiqueta;
}

template <class T>
const T& ArbolGeneral<T>::etiqueta(const Nodo n) const {
	assert(n!=0);
	return n->etiqueta;
}

template <class T>
void ArbolGeneral<T>::asignarSubarbol(const ArbolGeneral<T> &orig, const Nodo nod) {
	destruir(laraiz);
	copiar(laraiz, nod);
	if (laraiz != 0)
		laraiz->padre = 0;
}

template <class T>
void ArbolGeneral<T>::podarHijoMasIzquierda(Nodo n, ArbolGeneral<T> &dest) {
	assert(n!=0);
	destruir(dest.laraiz);
	dest.laraiz = n->izqda;
	if (dest.laraiz != 0) {
		dest.laraiz->padre = 0;
		n->izqda = 0;
	}
}

template <class T>
void ArbolGeneral<T>::podarHermanoDerecha(Nodo n, ArbolGeneral<T> &dest) {
	assert(n!=0);
	destruir(dest.laraiz);
	dest.laraiz = n->drcha;
	if (dest.laraiz != 0) {
		dest.laraiz->padre = 0;
		n->drcha = 0;
	}
}

template <class T>
void ArbolGeneral<T>::insertarHijoMasIzquierda(Nodo n, ArbolGeneral<T> &rama) {
	assert(n!=0);
	destruir(n->drcha);
	n->drcha = n->izqda;
	n->izqda = rama.laraiz;
	if (n->izqda != 0)
		n->izqda->padre = n;
		rama.laraiz = 0;
}

template <class T>
void ArbolGeneral<T>::insertarHermanoDerecha(Nodo n, ArbolGeneral<T> &rama) {
	assert(n!=0);

    // REVISAR
	destruir(n->drcha);
	n->drcha = rama.laraiz;
	if (n->drcha != 0)
		n->drcha->padre = n;
		rama.laraiz = 0;
}

template <class T>
void ArbolGeneral<T>::clear() {
	destruir(laraiz);
	laraiz = 0;
}

template <class T>
int ArbolGeneral<T>::size() const {
	return contar(laraiz);
}

template <class T>
bool ArbolGeneral<T>::empty() const {
	return laraiz == 0;
}

// ALTURA Y REFLEJADO

template <class T>
bool ArbolGeneral<T>::operator==(const ArbolGeneral<T> &v) const {
	return soniguales(laraiz, v.laraiz);
}

template <class T>
bool ArbolGeneral<T>::operator!=(const ArbolGeneral<T> &v) const {
	return !(*this == v);
}

// RECUPERAR

template <class T>
istream &operator>>(istream &in, ArbolGeneral<T> &v) {
	v.lee_arbol(in, v.laraiz);
	return in;
}

template <class T>
ostream &operator<<(ostream &out, const ArbolGeneral<T> &v) {
	v.escribe_arbol(out, v.laraiz);
	return out;
}

template<class T>
typename ArbolGeneral<T>::preorden_iterador& ArbolGeneral<T>::preorden_iterador::operator++() {
    if (p==0)
        return *this;
    if (p->izqda != 0)          // retorna el hijo más a la izquierda
        p = p->izqda;
    else if (p->drcha != 0)     // le toca a su hermano
        p = p->drcha;
    else {
        // subimos mientras no haya hermanos a la derecha
        while ((p->padre != 0) && (p->padre->drcha == 0))
            p = p->padre;
        if (p->padre == 0)      // si es la raíz hemos acabado
            p = 0;
        else
            p = p->padre->drcha;
    }

    return *this;
}

template<class T>
typename ArbolGeneral<T>::preorden_iterador& ArbolGeneral<T>::preorden_iterador::operator--() {
    if (p==0)
        return *this;
    else {
        if (p->padre != 0) {    // si tengo padre
            typename ArbolGeneral<T>::preorden_iterador sig(p->padre);
            typename ArbolGeneral<T>::preorden_iterador it(p->padre);
            while (++sig != p)  // me busco
                ++it;           // le tocará al penúltimo
            p = it.p;
            return *this;
        } else {
            p = 0;
            return *this;
        }
    }
}

template<class T>
typename ArbolGeneral<T>::preorden_iterador ArbolGeneral<T>::begin_pre() const {
    typename ArbolGeneral<T>::preorden_iterador it(laraiz);
    return it;
}

template<class T>
typename ArbolGeneral<T>::preorden_iterador ArbolGeneral<T>::end_pre() const {
    typename ArbolGeneral<T>::preorden_iterador it(0);
    return it;
}

void ArbolGeneral<T>::recorrerPreorden() const {
    ArbolGeneral<T>::preorden_iterator it;
    for ( it = begin_pre(); it != end_pre(); it++ )
        cout << *it << " ";
}

template<class T>
typename ArbolGeneral<T>::reverse_preorden_iterador& ArbolGeneral<T>::reverse_preorden_iterador::operator++() {
    typename ArbolGeneral<T>::preorden_iterador it(p);
    it--;
    p = it.p;
    return *this;
}

template<class T>
typename ArbolGeneral<T>::reverse_preorden_iterador& ArbolGeneral<T>::reverse_preorden_iterador::operator--() {
    typename ArbolGeneral<T>::preorden_iterador it(p);
    it++;
    p = it.p;
    return *this;
}

template<class T>
typename ArbolGeneral<T>::reverse_preorden_iterador ArbolGeneral<T>::begin_reverse_pre() const {
    typename ArbolGeneral<T>::everse_preorden_iterador it(end_pre().p);
    return it;
}

template<class T>
typename ArbolGeneral<T>::reverse_preorden_iterador ArbolGeneral<T>::end_reverse_pre() const {
    typename ArbolGeneral<T>::reverse_preorden_iterador it(begin_pre().p);
    return it;
}

void ArbolGeneral<T>::recorrerPreordenInverso() const {
    ArbolGeneral<T>::reverse_preorden_iterator it;
    for ( it = begin_reverse_pre(); it != end_reverse_pre(); it++ )
        cout << *it << " ";
}

// INORDEN, POSTORDEN

