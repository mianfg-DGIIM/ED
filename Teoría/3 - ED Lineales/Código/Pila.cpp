#include "Pila.h"

Pila::Pila() {
	primera = NULL;
}

Pila::Pila(const Pila &p) {
	if (p.primera == NULL)
		primera = NULL;
	else {
		primera = new CeldaPila;
		primera->elemento = p.primera->elemento;
		CeldaPila *src=p.primera, *dest=primera;
		while(src->sig != NULL) {
			dest->sig = new CeldaPila;
			src = src->sig;
			dest = dest->sig;
			dest->elemento = src->elemento;
		}
		dest->sig = NULL;
	}
}

Pila::~Pila() {
	CeldaPila *aux;
	while (primera != 0) {
		aux = primera;
		primera = primera->sig;
		delete aux;
	}
}

Pila& Pila::operator=(const Pila &p) {
	Pila paux(p);
	CeldaPila *aux;
	aux = (*this).primera;
	(*this).primera = paux.primera;
	paux.primera = aux;
	return *this;
}

void Pila::poner(Tbase c) {
	CeldaPila *aux = new CeldaPila;
	aux->elemento = c;
	aux->sig = primera;
	primera = aux;
}

void Pila::quitar() {
	assert(primera!=0);
	CeldaPila *aux = primera;
	primera = primera->sig;
	delete aux;
}

Tbase Pila::tope() const {
	assert(primera!=0);
	return primera->elemento;
}

bool Pila::vacia() const {
	return primera==0;
}

/*
Pila::reservarMemoria(int n) {
	if (n>0) {
		reservados=n;
		datos = new Tbase[n];
	}
}

Pila::liberarMemoria() {
	if (reservados>0) {
		delete[] datos;
		nelem=0;
		reservados=0;
	}
}

Pila::copiar(const Pila &p) {
	reservarMemoria(p.reservados);
	nelem=p.nelem;
	for (int i=0; i<nelem; i++)
		datos[i] = p.datos[i];
}

Pila::resize(int n) {
	Tbase *datos_aux = new Tbase[n];
	for (int i=0; i<nelem && i<n; i++) {
		datos_aux[i] = datos[i];
	}
	
}

Pila::Pila() {
	reservarMemoria(0);
}

Pila::Pila(const Pila &p) {
	copiar(const Pila &p);
}

Pila& Pila::operator=(const Pila &p) {
	liberarMemoria();
	copiar(p);
}

Pila::~Pila() {
	liberarMemoria();
}

void Pila::poner(Tbase c) {
	if (reservados == nelem) {
		reservarMemoria(reservados*2);
		
	}
}
*/
