#ifndef __COLA_H
#define __COLA_H_

typechar char TBase;

struct CeldaCola {
	TBase elemento;
	CeldaCola *sig;
}

class Cola {
	CeldaCola *primera;
	CeldaCola *ultima;
public:
	Cola();
	Cola(const Cola &p);
	~Cola();
	Cola& operator=(const Cola &p);
	
	bool vacia() const { return nelem==0; }
	void poner(TBase c);
	void quitar();
	TBase tope() const;
};

#endif
