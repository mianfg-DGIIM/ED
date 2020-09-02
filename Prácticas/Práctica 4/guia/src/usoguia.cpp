#include "Guia_Tlf.h"

#include <fstream>

using namespace std;

/**
 * @brief Sobrecarga del operador de salida para @a list de @a string
 * @param os: flujo de salida
 * @param l: lista que se desea mostrar
 * @return Referencia al flujo de salida
 */
ostream& operator<<(ostream &os, const list<string> &l) {
	list<string>::const_iterator it;
	for ( it = l.cbegin(); it != l.cend(); ++it )
		os << '\t' << *it << endl;
	return os;
}

int main(int narg, char* argv[]){
	ifstream g1, g2;
	string entrada, entrada2;

	cout << "\nTDA GUIA_TLF\n";

	Guia_Tlf guia1, guia2;

	cout << "\n_____________________________________________\n";
	cout << "\n=> 1. Prueba con operadores de E/S\n";
	cout << "\nIntroduce el nombre del fichero que contiene la primera guía: " << endl;
	cin >> entrada;
	g1.open(entrada);
	if ( !g1 ) {
		cout << "\nError abriendo el archivo " << entrada << endl;
		return -1;
	}
	g1 >> guia1;
	cout << "\nLa guía 1, introducida mediante " << entrada << ", es: " << endl << endl;
	cout << guia1;
	cout << "\nIntroduce el nombre del fichero que contiene la segunda guía: " << endl;
	cin >> entrada;
	g2.open(entrada);
	if ( !g2 ) {
		cout << "\nError abriendo el archivo " << entrada << endl;
		return -1;
	}
	g2 >> guia2;
	cout << "\nLa guía 2, introducida mediante " << entrada << ", es: " << endl << endl;
	cout << guia2;

	cout << "\n_____________________________________________\n";
	cout << "\n=> 2. Prueba introduciendo y borrando de la guía\n\n";

	cout << "De aquí en adelante, probaremos estas funciones con la guía 1\n";

	cout << "\nDime un nombre sobre el que quieres obtener el teléfono: ";
	
	cin.ignore();
	getline(cin, entrada);
	string tlf = guia1.getTelefono(entrada);
	if ( tlf == "" )
		cout << "\nEl nombre \"" << entrada << "\" no existe en la guía"<<endl;
	else
		cout << "\nEl teléfono de \"" << entrada << "\" es: "<< tlf <<endl;
	
	cin.clear();
	cout << "\nDime el nombre que quieres borrar: ";

	getline(cin, entrada);
	guia1.borrar(entrada);
	cout << "\nAhora la guía, tras borrar a \"" << entrada << "\" es:"<<endl;
	cout << guia1 << endl;

	Guia_Tlf guia_union = guia1 + guia2;
	Guia_Tlf guia_diferencia = guia1 - guia2;

	cout << "\n----> Unión de guías\n";
	cout << "\nLa unión de las dos guías: " << endl
		 << guia_union << endl;
	cout << "\n----> Diferencia de guías\n";
	cout << "\nLa diferencia de las dos guías:" << endl
		 << guia_diferencia << endl;
	
	cout << "\n_____________________________________________\n";
	cout << "\n=> 3. Funcionalidades adicionales\n";

	cout << "\nDe aquí en adelante, probaremos estas funciones con la guía unión.\n";

	cout << "\n----> Prefijo\n";
	cout << "\nEscriba a continuación un prefijo telefónico: ";
	cin >> entrada;
	cout << "\nA continuación, se listan los elementos de la guía con prefijo \"" << entrada << "\":\n";
	Guia_Tlf prefijos = guia_union.prefijo(entrada);
	cout << prefijos << endl;

	cout << "\n----> Nombres de personas con un mismo teléfono\n";
	cout << "\nEscriba un número de teléfono: ";
	cin >> entrada;
	cout << "\nLos nombres de las personas con teléfono " << entrada << " en la guía unión son:\n";
	list<string> nombres = guia_union.getNombres(entrada);
	cout << nombres;

	cout << "\n----> Modificar teléfono\n";
	cout << "\nInserte el nombre: ";
	cin.ignore();
	getline(cin, entrada);
	cout << "\nInserte el nuevo teléfono: ";
	cin >> entrada2;

	if ( !guia_union.modificarTelefono(entrada, entrada2) )
		cout << "\nEl nombre \"" << entrada << "\" no está en la guía :(\n";
	else {
		cout << "\n¡Genial! ;) Ahora la guía es:\n\n";
		cout << guia_union << endl;
	}

	return 0;
}
