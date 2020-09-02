/** 
 * @file Fecha_Historica.cpp
 * @author Miguel Ángel Fernández Gutiérrez <mianfg@correo.ugr.es>
 * @author Juan Manuel Mateos Pérez <jumape@correo.ugr.es>
*/

#include <iostream>
#include <string>
#include <cassert>
#include "Fecha_Historica.h"

using namespace std;

void Fecha_Historica::resize(int r){
	if (r>0) {
		string *aux = new string[r];
		for(int i=0; i<numeventos && i<r; ++i)
			aux[i]=str[i];
		delete[] str;
		str = aux;
		reservados = r;
	} else {
		delete[] str;
		str = NULL;
		numeventos = 0;
		reservados = 0;
	}
}

Fecha_Historica::Fecha_Historica():anio(0),reservados(0),numeventos(0),str(0){}

Fecha_Historica::Fecha_Historica(int a, string *s, int n) : reservados(n), numeventos(n){
	assert(a >= 0 && a<= 9999);
	anio = a;
	string *str = new string[n];
	for (int i=0; i<n; i++)
		str[i]=s[i];
}

Fecha_Historica::Fecha_Historica(const Fecha_Historica& e){
	str = new string[e.reservados];
	anio=e.anio;
	numeventos = e.numeventos;
	reservados = e.reservados;
	for(int i=0; i<numeventos; ++i)
		str[i] = e.str[i];
}

Fecha_Historica& Fecha_Historica::operator=(const Fecha_Historica& e){
	resize(e.reservados);
	anio=e.anio;
	numeventos = e.numeventos;
	for(int i=0; i<numeventos; ++i)
		str[i] = e.str[i];
}

void Fecha_Historica::aniadirevento(string& event){
	if (numeventos == reservados)
		if (numeventos==0)
			resize(1);
		else
			resize(2*reservados);
	str[numeventos]=event;
	numeventos++;
}

bool Fecha_Historica::buscarEventos(string s, Fecha_Historica &matches){
	bool encontrado=false;
	for (int i=0; i < numeventos; ++i)
		if(str[i].find(s) != -1 ){
			matches.aniadirevento(str[i]);
			encontrado = true;
		}
	if (encontrado)
		matches.anio=anio;
	return encontrado;
}

ostream& operator<< (ostream& os, const Fecha_Historica& e){
	os << e.anio;
	for ( int i = 0; i < e.numeventos; i++ )
		os << '#' << e.str[i];
	return os;
}

istream& operator>> (istream& is, Fecha_Historica& e){
	// primero borrar
	e.resize(0);
	is >> e.anio;
	is >> noskipws;
	bool continuar = true;
	char comprobador; string temp;
	while ( is >> comprobador && continuar )
		if (comprobador == '#') {
			e.aniadirevento(temp);
			temp = "";
		} else if ( comprobador == '\n' ) {
			e.aniadirevento(temp);
			continuar = false;
			is.putback(comprobador);
		} else
			temp += comprobador;
	return is;
}  
