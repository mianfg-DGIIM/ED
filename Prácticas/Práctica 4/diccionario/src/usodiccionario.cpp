/**
 * @file usodiccionario.cpp
 * @brief Programa para probar el funcionamiento del TDA Diccionario
 * @author Miguel Ángel Fernández Gutiérrez <mianfg@correo.ugr.es>
 * @author Juan Manuel Mateos Pérez <jumape@correo.ugr.es>
 */

#include <iostream>
#include "Diccionario.h"

using namespace std;

/**
 * @brief Operador de entrada para Diccionario de strings
 * El formato de la entrada es:
 *   - número de claves en primera línea
 *   - clave i-ésima retorno de carro
 *   - numero de informaciones asociadas en la siguiente línea
 *   - en cada línea la información asociada
 * @param is: flujo de entrada
 * @param D: diccionario que se quiere asignar
 * @return Referencia al flujo de entrada
 */
istream &operator>>(istream &is, Diccionario<string, string> &D) {
	int np;
	is >> np;
	is.ignore(); //quitamos \n
	Diccionario<string, string> Daux;
	for (int i = 0; i < np; i++) {
		string clave;

		getline(is, clave);

		int ns;
		is >> ns;
		is.ignore(); //quitamos \n
		list<string> laux;
		for (int j = 0; j < ns; j++) {
			string s;
			getline(is, s);

			// cout<<"Significado leído "<<s<<endl;
			laux.insert(laux.end(), s);
		}
		Daux.insertar(clave, laux);
	}
	D = Daux;
	return is;
}

/**
 * @brief Muestra los significados en pantalla
 * @param D: diccionario del que obtener los significados
 * @param clave: clave de la que se quieren obtener los significados
 */
void mostrarSignificados(Diccionario<string, string> D, const string &clave) {
	list<string> significados(D.getInfo(clave));

	list<string>::iterator it;
	for ( it = significados.begin(); it != significados.end(); ++it )
		cout << '\t' << *it << endl;
}

int main() {
	cout << "\nTDA DICCIONARIO\n";

	Diccionario<string, string> D;

	cout << "\n_____________________________________________\n";
	cout << "\n=> 1. Prueba con operadores de E/S\n";
	cout << "\n(Hemos implementado la sobrecarga de operator<< para Diccionario)\n";
	cout << "\nAlmacenando los datos de data.txt en el diccionario...\n";
	cout << "    NOTA: debe haber usado este programa como: ./usodiccionario < data.txt\n";
	cin >> D;
	cout << "\nEl diccionario almacenado es:\n\n";
	cout << D;

	cout << "\n_____________________________________________\n";
	cout << "\n=> 2. Prueba introduciendo palabras\n\n";
	string entrada1, entrada2;
	list<data<string, string> >::iterator it;

	cout << "Introduce una clave: ";
	getline(cin, entrada1);

	if ( D.estaClave(entrada1, it) ) {
		cout << "Clave correcta. Le añadiremos otro significado.\n";
		cout << "Inserte el nuevo significado: ";
		getline(cin, entrada2);
		D.addSignificado(entrada2, entrada1);
		cout << "\n¡Genial! Ahora la palabra \"" << entrada1 << "\" tiene los significados:\n";
		mostrarSignificados(D, entrada1);
	} else
		cout << "Clave incorrecta.\n";

	cout << "\n_____________________________________________\n";
	cout << "\n=> 3. Funcionalidades adicionales\n";

	cout << "\n----> Unión de diccionarios\n";
	cout << "\nEscriba a continuación un nuevo diccionario:\n";
	Diccionario<string, string> D2;
	cin >> D2;
	cout << "\nEl diccionario almacenado es:\n\n";
	cout << D2;
	cout << "\nEl diccionario resultante de unir éste y el anterior es:\n\n";
	Diccionario<string, string> D3 = D + D2;
	cout << D3;

	cout << "De aquí en adelante, probaremos el resto de funciones con el diccionario unión.\n";

	cout << "\n----> Sinónimos\n";
	cout << "\nInserte dos claves a continuación, veremos si son sinónimas:\n";
	cout << "\tclave 1: ";
	getline(cin, entrada1);
	cout << "\tclave 2: ";
	getline(cin, entrada2);
	cout << '\n';
	if ( !D3.estaClave(entrada1, it) || !D3.estaClave(entrada2, it) )
		cout << "Alguna de las claves es incorrecta.\n";
	else
		if ( D3.sinonimos(entrada1, entrada2) )
			cout << entrada1 << " y " << entrada2 << " son sinónimos :)\n";
		else
			cout << entrada1 << " y " << entrada2 << " no son sinónimos :(\n";

	cout << "\n----> Prefijos\n";
	cout << "\nInserte un prefijo, listaremos todas las palabras que comiencen por él: ";
	getline(cin, entrada1);
	list<string> prefijos = D3.prefijo(entrada1);
	cout << "\nLas palabras que comienzan por \"" << entrada1 << "\" son:\n";
	list<string>::iterator it2;
	for ( it2 = prefijos.begin(); it2 != prefijos.end(); ++it2 )
		cout << '\t' << *it2 << endl;

	cout << "\n----> Ordenar definiciones\n";
	cout << "\nInserte la palabra de la que desea ordenar sus definiciones: ";
	getline(cin, entrada1);
	if ( !D3.ordenar(entrada1) )
		cout << "No se ha podido ordenar. Compruebe que la clave es correcta :(\n";
	else {
		cout << "\n¡A continuación, el nuevo orden de \"" << entrada1 << "\"! ;)\n";
		mostrarSignificados(D3, entrada1);
	}

	return 0;
}
