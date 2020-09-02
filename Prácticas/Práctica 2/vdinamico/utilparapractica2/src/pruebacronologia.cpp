/** 
 * @file pruebacronologia.cpp
 * @author Miguel Ángel Fernández Gutiérrez <mianfg@correo.ugr.es>
 * @author Juan Manuel Mateos Pérez <jumape@correo.ugr.es>
*/

#include "Cronologia.h"
#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char * argv[]) {

	if (argc!=2){
		cout<<"Dime el nombre del fichero con la cronologia"<<endl;
		return 0;
	}

	ifstream f (argv[1]);
	if (!f){
		cout<<"No puedo abrir el fichero "<<argv[1]<<endl;
		return 0;
	}

	Cronologia mi_cronologia;

	f >> mi_cronologia; //Cargamos en memoria
   
	cout << "Cronología leida del archivo: " << endl << mi_cronologia << endl;
   
	Cronologia buscadora(mi_cronologia.buscarEventos("Sherlock"));  // uso de constructor de copias + búsqueda
   
	/* To-do: Ej: buscar un evento y restringir copia a los acontecimientos con ese evento, después imprimir para comprobar */
	cout << "Evento encontrado con \"Sherlock\":\n" << buscadora;

}
