#include <iostream>
#include <ctime>    // Recursos para medir tiempos
#include <cstdlib>  // Para generación de números pseudoaleatorios
#include <vector>   // Lo haremos con vectores

using namespace std;

vector<vector<int> > producto(const vector<vector<int> > & a,
                              const vector<vector<int> > & b) {
    if ( a.size() > 0 && b.size() > 0 )
        if ( a[0].size() == b.size() ) {
            vector<vector<int> > resultado(a.size(), vector<int>(b[0].size(), 0));
            
            int elemento;
            for ( int i = 0; i < a.size(); i++ ) {
                for ( int j = 0; j < b.size(); j++ ) {
                    elemento = 0;
                    for ( int k = 0; k < b.size(); k++ )
                    	elemento += a[i][k]*b[k][j];
                    resultado[i][j] = elemento;
                }
            }
            
            return resultado;
        }
    
    vector<vector<int> > empty;
    return empty;
}

void show(const vector<vector<int> > & v) {
	for ( int i = 0; i < v.size(); i++ ) {
		for ( int j = 0; j < v[0].size(); j++ )
			cout << v[i][j] << ' ';
		cout << endl;
	}
	cout << endl;
}

void sintaxis() {
  cerr << "Sintaxis:" << endl;
  cerr << "  TAM: Tamaño del vector (>0)" << endl;
  cerr << "  VMAX: Valor máximo (>0)" << endl;
  cerr << "Se generan matrices cuadradas de tamaño TAM con elementos aleatorios en [0,VMAX["
       << endl;
  exit(EXIT_FAILURE);
}

int main(int argc, char * argv[])
{
  // Lectura de parámetros
  if (argc!=3)
    sintaxis();
  int tam=atoi(argv[1]);     // Tamaño del vector
  int vmax=atoi(argv[2]);    // Valor máximo
  if (tam<=0 || vmax<=0)
    sintaxis();
  
  // Generación del vector aleatorio v1
  vector<vector<int> > v1(tam, vector<int>(tam,0));   // Reserva de memoria
  srand(time(0));                  // Inicialización del generador de números pseudoaleatorios
  for (int i=0; i<tam; i++)        // Recorrer vector
	for (int j=0; j<tam; j++)
		v1[i][j] = rand() % vmax;  // Generar aleatorio [0,vmax[

  // Generación del vector aleatorio v2
  vector<vector<int> > v2(tam, vector<int>(tam,0));   // Reserva de memoria
  for (int i=0; i<tam; i++)        // Recorrer vector
	for (int j=0; j<tam; j++)
		v2[i][j] = rand() % vmax;  // Generar aleatorio [0,vmax[
  
  clock_t tini;    // Anotamos el tiempo de inicio
  tini=clock();
  
  vector<vector<int> > resultado;
  resultado = producto(v1, v2);   // Multiplicamos las matrices
  
  clock_t tfin;    // Anotamos el tiempo de finalización
  tfin=clock();

  // Mostramos resultados
  cout << tam << "\t" << (tfin-tini)/(double)CLOCKS_PER_SEC << endl;
  
}
