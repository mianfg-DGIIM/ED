/** 
 * @file Cronologia.cpp
 * @author Miguel Ángel Fernández Gutiérrez <mianfg@correo.ugr.es>
 * @author Juan Manuel Mateos Pérez <jumape@correo.ugr.es>
*/

#include <iostream>
#include "Cronologia.h"
#include "Fecha_Historica.h"

using namespace std;

void Cronologia::resize(int r){	
	Fecha_Historica *aux = new Fecha_Historica[r];
	for(int i=0; i<neventos && i<r; ++i)
		aux[i]=event[i];
	delete[] event;
	event = aux;
	reservados = r;
}

void Cronologia::ordenar(){
	for (int i=neventos-1; i>0; --i) 
		for (int j=0; j<i; ++j)
			if (event[j].getAnio() > event[j+1].getAnio()) {
				Fecha_Historica aux;
				aux = event[j];
				event[j] = event[j+1];
				event[j+1]= aux;
			}
}

Cronologia::Cronologia():reservados(0),neventos(0),event(0){}
     
Cronologia::Cronologia(Fecha_Historica *eh, int n):reservados(n),neventos(n){
	Fecha_Historica *event = new Fecha_Historica[n];   
	for (int i=0; i<n; i++)
		event[i]=eh[i];
}

Cronologia::Cronologia(const Cronologia& c){
	event = new Fecha_Historica[c.reservados];
	neventos = c.neventos;
	reservados = c.neventos;
	for(int i=0; i<neventos; ++i)
		event[i] = c.event[i];
}

void Cronologia::aniadirEvento(Fecha_Historica& eh){
	if (neventos == reservados){
		if (neventos==0)
			resize(1);
		else
			resize(2*reservados);
	}
	event[neventos]=eh;
	neventos++;
	ordenar();
}

int Cronologia::buscarAnio(int f){
	int i=0;
	bool valido=false;
	while(i<neventos && !valido)
		if(event[i].getAnio()==f)
			valido = true;
		else
			++i;
	if(!valido)
		i=-1;
	return i;
}


Cronologia Cronologia::buscarEventos(string s){
	Cronologia nuevo;
	for (int i=0; i < neventos; ++i){
		Fecha_Historica aux;
		if(event[i].buscarEventos(s,aux))
			nuevo.aniadirEvento(aux);
	}
	nuevo.ordenar();
	return nuevo;
}

ostream& operator<< (ostream& os, const Cronologia& c){
	for(int i=0; i<c.neventos; i++) {
		os << c.event[i];
		os << endl;
	}
	return os;     
}

istream& operator>> (istream& is, Cronologia& c){
	Fecha_Historica b;
	while(is >> b)
        c.aniadirEvento(b);
	return is;
}
