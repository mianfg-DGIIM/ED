#ifndef __PILA_H_
#define __PILA_H_

/*
 * Primera posible implementación
 * 
 * Desventajas: desperdicio de memoria, se puede llenar
 * Solución: usar memoria dinámica
 * 

typedef char Tbase;

class Pila {
	Tbase datos[500];
	int nelem;
public:
	Pila();
	Pila (const Pila &p);
	~Pila();
	Pila& operator=(const Pila &p);

	bool vacia() const { return nelem==0; }
	void poner(Tbase c) {
		assert(nelem<500);
		datos[nelem]=c;
		nelem++;
	}
	void quitar() {
		assert(nelem>0);
		nelem--;
	}
	Tbase tope() const {
		assert(nelem>0);
		return datos[nelem-1];
	}
}; */

/*
 * Otra implementación

class Pila {
	Tbase *datos;
	int reservados;
	int nelem;
	void resize(int n);
public:
	Pila();
	Pila(const Pila &p);
	~Pila();
	Pila& operator=(const Pila &p);
	
	bool vacia() const { return nelem==0; }
	void poner(Tbase c);
	void quitar();
	Tbase tope() const;
}; */


typechar char Tbase;

struct CeldaPila {
	Tbase elemento;
	CeldaPila *sig;
}

class Pila {
	CeldaPrimera *primera;
public:
	Pila();
	Pila(const Pila &p);
	~Pila();
	Pila& operator=(const Pila &p);
	
	bool vacia() const { return nelem==0; }
	void poner(Tbase c);
	void quitar();
	Tbase tope() const;
};

#endif
