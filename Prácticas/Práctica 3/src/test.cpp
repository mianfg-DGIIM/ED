#include "Pila_max_cola.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main() {
    int aleatorio;

    // ------ Pila de enteros -------
    cout << "\nPILA DE ENTEROS" << endl << endl;

    Pila_max<int> pila;

    srand(time(NULL));

    cout << "El tamaño de la pila ahora es de: " << pila.size() << endl;
    // Almacenamos elementos aleatorios en la pila de máximos
    for ( int i = 0; i < 10; i++ ) {
        aleatorio = rand() % 10 + 1;
        pila.poner(aleatorio);
        cout << "Añadido elemento " << aleatorio << endl;
        cout << "El tamaño de la pila ahora es de: " << pila.size() << endl;
    }

    cout << endl;

    // Mostramos por pantalla esos elementos (con su máximo), haciendo:
    //     - mostrar tope
    //     - eliminar elemento
    for ( int i = 0; i < 10; i++ ) {
        cout << pila.tope() << endl;
        pila.quitar();
    }

    cout << endl;
    
    // Comprobamos finalmente si la pila está vacía
    if ( pila.vacia() ) {
        cout << "En efecto, la pila ahora está vacía :)" << endl;
    } else {
        cout << "Ha habido algún fallo porque la pila no está vacía :(" << endl;
    }

    // ------ Pila de floats --------
    cout << endl << "PILA DE FLOATS" << endl << endl;

    // Ahora lo hacemos con otro tipo de dato, para mostrar que nuestras templates funcionan
    Pila_max<float> pila2;

    cout << "Almacenando elementos..." << endl;
    for ( int i = 0; i < 10; i++ )
        pila2.poner(i+0.5);
    
    for ( int i = 0; i < 10; i++ ) {
        cout << pila2.tope() << endl;
        pila2.quitar();
    }

    return 0;
}