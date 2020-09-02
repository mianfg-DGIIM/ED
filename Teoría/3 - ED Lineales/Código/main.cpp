#include <iostream>
#include <pila.h>
using namespace std;

int main() {
	Pila p, q;
	char dato;
	
	cout << "Escriba una frase: ";
	while ((dato=cin.get())!='\n')
		p.poner(dato);
	
	cout << "Lo escribimos al revés: ";
	while (!p.vacia()) {
		cout << p.tope();
		q.poner(p.tope);
		p.quitar();
	}
	
	cout << endl << "Los originales eran: " << endl;
	while (!q.vacia()) {
		cout << q.tope();
		q.quitar();
	}
	cout << endl;
	
	return 0;
}
