#ifndef __ArbolGeneral_h__
#define __ArbolGeneral_h__

#include <cassert>

using namespace std;

/**
   @brief T.D.A. ArbolGeneral
   
   \b Definición:
   Una instancia \e a del tipo de dato abstracto ArbolGeneral sobre un dominio
   \e T se puede construir como

   - Un objeto vacío (árbol vacío) si no contiene ningún elemento.
   Lo denotamos {}.
   - Un árbol que contiene un elemento destacado, el nodo raíz, con un valor
   \e e en el dominio \e T (denominado \e etiqueta), y \e k subárboles
   \f$(T_1, \ldots, T_k)\f$ del T.D.A. ArbolGeneral sobre \e T.

   Se establece una relación \e padre-hijomasalaizquierda-hermanoaladerecha
   entre cada nodo y los nodos raíz  de los subárboles (si los hubiera) que
   cuelgan de él.
   
   Para poder usar el tipo de dato ArbolGeneral se debe incluir el fichero
   
   <tt>\#include ArbolGeneral.h</tt>

   El espacio requerido para el almacenamiento es O(n), donde n es el número de
   nodos del árbol.

   @author Miguel Ángel Fernández Gutiérrez
   @date diciembre de 2018
*/
template <class T>
class ArbolGeneral {
    /**
     * @page repConjunto Rep del TDA APO
     *
     * @section invConjunto Invariante de la representación
     *
     * Sea \e T un Árbol General sobre un tipo \e T. Entonces el
	 * invariante de la representación es:
	 * 
	 * Si \e T es vacío, entonces T.laraiz vale 0.
	 * Si no:
	 *   - T.laraiz->padre = 0 y
	 *   - \f$ \forall \f$ n nodo de \e T, n->izqda \f$ \neq \f$ n->drch y
	 *   - \f$ \forall \f$ n, m nodos de \e T, si n->izqda = m, entonces
	 *     m->padre = n y
	 *   - número de elementos = número de elementos de la raíz, donde
	 *     N(n) = 1 + N(n->izqda) + N(n->drcha), con N(0) = 0.
     *
     * @section faConjunto Función de abstracción
     *
     * Sea \e T un Árbol General sobre el tipo \e T. Entonces, si lo denotamos
	 * también Árbol(T.laraiz), es decir, como el árbol que cuelga de su raíz,
	 * entonces este árbol del conjunto de valores en la representación se aplica
	 * al árbol.
	 * 
	 * { T.laraiz->etiqueta, {Arbol(T.laraiz->izqda)}, {Arbol(T.laraiz->drcha)} }
	 * 
	 * donde {0} es el árbol vacío.
     */

   private:
    /**
     * @brief nodo
     *
     * En cada  estructura \e nodo se almacena una etiqueta del árbol, que se
     * implementa como un conjunto de nodos enlazados según la relación
     * padre-hijo más a la izquierda-hermano derecha.
     */
    struct nodo {
        /**
         * @brief Elemento almacenado
         *
         * En este campo se almacena la etiqueta que corresponde a este nodo.
         */
        T etiqueta;

        /**
         * @brief Puntero al hijo más a la izquierda
         *
         * En este campo se almacena un puntero al nodo raíz del subárbol más a
         * la izquierda, o el valor 0 si no tiene.
         */
        struct nodo *izqda;

        /**
         * @brief Puntero al hermano derecho
         *
         * En este campo se almacena un puntero al nodo raíz del subárbol
         * hermano derecho, o el valor 0 si no tiene.
         */
        struct nodo *drcha;

        /**
         * @brief Puntero al padre
         *
         * En este campo se almacena un puntero al nodo padre, o el valor 0 si
         * es la raíz.
         */
        struct nodo *padre;

		/**
		 * @brief Constructor
		 * 
		 * Crea un nodo vacío
		 */
		nodo() { padre = drcha = izqda = 0; }

		/**
		 * @brief Constructor con parámetros
		 * @param e Elemento que se va a asignar
		 * 
		 * Crea un nodo con un elemento
		 */
		nodo(const T &elemento) : etiqueta(elemento) { padre = drcha = izqda = 0; }

		/**
		 * @brief Destructor
		 * 
		 * Destruye el nodo
		 */
		~nodo() { padre = 0; izqda = 0; drcha = 0; }
    };

    /**
     * @brief Puntero a la raíz.
     *
     * Este miembro es un puntero al primer nodo, que corresponde a la raíz
     * del árbol. Vale 0 sin el árbol es vacío.
     */
    struct nodo *laraiz;

    /**
     * @brief Destruye el subárbol
     * @param n Nodo a destruir, junto con sus descendientes
     *
     * Libera los recursos que ocupan \e n y sus descendientes.
     */
    void destruir(nodo *&n);

    /**
     * @brief Copia un subárbol
     * @param dest Referencia al puntero del que cuelga la copia
     * @param orig Puntero a la raíz del subárbol a copiar
     *
     * Hace una copia de todo el subárbol que cuelga de \e orig en el puntero
     * \e dest. Es importante ver que en \e dest->padre (si existe) no se
     * asigna ningún valor, pues no se conoce.
     */
    void copiar(nodo *&dest, nodo *orig);

    /**
     * @brief Cuenta el número de nodos
     * @param n Nodo del que cuelga el subárbol de nodos a contabilizar.
     *
     * Cuenta cuántos nodos cuelgan de \e n, incluido éste.
     */
    int contar(nodo *n) const;

	/**
	 * @brief Cuenta el número de hijos
	 * @param n Nodo padre del que cuelgan los hijos.
	 * 
	 * Cuenta cuántos hijos cuelgan de \e nodo.
	 */
	int contarHijos(nodo *n) const;

    /**
     * @brief Comprueba igualdad de dos subárboles
     * @param n1 Primer subárbol a comparar
     * @param n2 Segundo subárbol a comparar
     *
     * Comprueba si son iguales los subárboles que cuelgan de \e n1 y \e n2.
     * Para ello deberán tener los mismos nodos en las mismas posiciones y
     * con las mismas etiquetas.
     */
    bool sonIguales(nodo *n1, nodo *n2) const;

    /**
     * @brief Escribe un subárbol
     * @param out Stream de salida donde escribir
     * @param nod Nodo del que cuelga el subárbol a escribir
     *
     * Escribe en el flujo de salida todos los nodos del subárbol que cuelga
     * del nodo \e nod siguiendo un recorrido en preorden. La forma de
     * impresión de cada nodo es:
     *
     * - Si el nodo es nulo, imprime el carácter 'x'.
     * - Si el nodo no es nulo, imprime el carácter 'n' seguido de un
     * espacio, al que sigue la impresión de la etiqueta
     */
    void escribeArbol(std::ostream &out, nodo *nod) const;

    /**
     * @brief Lee un subárbol
     * @param in Stream de entrada desde el que leer
     * @param nod Referencia al nodo que contendrá el subárbol leído
     *
     * Lee del flujo de entrada \e in los elementos de un árbol según el
     * formato que se presenta en la función de escritura.
     *
     * @see escribeArbol
     */
    void leeArbol(std::istream &in, nodo *&nod);

   public:
    /**
     * @brief Tipo Nodo
     *
     * Este tipo nos permite manejar cada uno de los nodos del árbol. Los
     * valores que tomará serán tantos como nodos en el árbol (para poder
     * referirse a cada uno de ellos) y además un valor destacado
     * \e nulo (0), que indica que no se refiere a ninguno de ellos.
     *
     * Una variable \e n de este tipo se declara
     *
     * <tt>ArbolGeneral::Nodo n;</tt>
     *
     * Las operaciones válidas sobre el tipo nodo son:
     *
     * - Operador de Asignación (=).
     * - Operador de comprobación de igualdad (==).
     * - Operador de comprobación de desigualdad (!=).
     */
    typedef struct nodo *Nodo;

    /**
     * @brief Constructor por defecto
     *
     * Reserva los recursos e inicializa el árbol a vacío {}. La operación se
     * realiza en tiempo O(1).
     */
    ArbolGeneral();

    /**
     * @brief Constructor de raíz
     * @param e Etiqueta de la raíz
     *
     * Reserva los recursos e inicializa el árbol con un único nodo raíz que
     * tiene la etiqueta \e e, es decir, el árbol {e, {}, {}}. La operación
     * se realiza en tiempo O(1).
     */
    ArbolGeneral(const T &e);

    /**
     * @brief Constructor de copias
     * @param v ArbolGeneral a copiar
     *
     * Construye el árbol duplicando el contenido de \e v en el árbol
     * receptor.
     * La operación se realiza en tiempo O(n), donde \e n es el número
     * de elementos de \e v.
     */
    ArbolGeneral(const ArbolGeneral<T> &v);

    /**
     * @brief Destructor
     *
     * Libera los recursos ocupados por el árbol receptor. La operación se
     * realiza en tiempo O(n), donde n es el número de elementos del árbol
     * receptor.
     */
    ~ArbolGeneral();

    /**
     * @brief Operador de asignación
     * @param v ArbolGeneral a copiar
     * @return Referencia al árbol receptor.
     *
     * Asigna el valor del árbol duplicando el contenido de \e v en el árbol
     * receptor.
     * La operación se realiza en tiempo O(n), donde \e n es el número de
     * elementos de \e v.
     */
    ArbolGeneral<T> &operator=(const ArbolGeneral<T> &v);

    /**
     * @brief Asignar nodo raíz
     * @param e Etiqueta a asignar al nodo raíz
     *
     * Vacía el árbol receptor y le asigna como valor el árbol de un único
     * nodo cuya etiqueta es \e e.
     */
    void asignaRaiz(const T &e);

    /**
     * @brief Raíz del árbol
     * @return Nodo raíz del árbol receptor
     *
     * Devuelve el nodo raíz, que es 0 (nulo) si el árbol está vacío.
     * La operación se realiza en tiempo O(1).
     */
    Nodo raiz() const;

    /**
     * @brief Hijo más a la izquierda
     * @param n Nodo del que se quiere obtener el hijo más a la izquierda.
     * @pre \e n no es nulo
     * @return Nodo hijo más a la izquierda
     *
     * Devuelve el nodo hijo más a la izquierda de \e n, que valdrá 0 (nulo)
     * si no tiene hijo más a la izquierda.
     * La operación se realiza en tiempo O(1).
     */
    Nodo hijoMasIzquierda(const Nodo n) const;

    /**
     * @brief Hermano derecha
     * @param n Nodo del que se quiere obtener el hermano a la derecha.
     * @pre \e n no es nulo
     * @return Nodo hermano a la derecha
     *
     * Devuelve el nodo hermano a la derecha de \e n, que valdrá 0 (nulo)
     * si no tiene hermano a la derecha.
     * La operación se realiza en tiempo O(1).
     */
    Nodo hermanoDerecha(const Nodo n) const;

    /**
     * @brief Nodo padre
     * @param n Nodo del que se quiere obtener el padre.
     * @pre \e n no es nulo
     * @return Nodo padre
     *
     * Devuelve el nodo padre de \e n, que valdrá 0 (nulo) si es la raíz.
     * La operación se realiza en tiempo O(1).
     */
    Nodo padre(const Nodo n) const;

    /**
     * @brief Etiqueta de un nodo
     * @param n Nodo en el que se encuentra el elemento.
     * @pre \e n no es nulo
     * @return Referencia al elemento del nodo \e n
     *
     * Devuelve una referencia al elemento del nodo \e n y por tanto se puede
     * modificiar o usar el valor.
     * La operación se realiza en tiempo O(1).
     */
    T& etiqueta(const Nodo n);

    /**
     * @brief Etiqueta de un nodo
     * @param n Nodo en el que se encuentra el elemento.
     * @pre \e n no es nulo
     * @return Referencia constante al elemento del nodo \e n.
     *
     * Devuelve una referencia al elemento del nodo \e n. Es constante y por
     * tanto no se puede modificiar el valor.
     * La operación se realiza en tiempo O(1).
     */
    const T& etiqueta(const Nodo n) const;

    /**
     * @brief Copia subárbol
     * @param orig Árbol desde el que se va a copiar una rama
     * @param nod Nodo raíz del subárbol que se copia.
     * @pre \e nod es un nodo del árbol \e orig y no es nulo
     *
     * El árbol receptor acaba con un valor copia del subárbol que cuelga del
     * nodo \e nod en el árbol \e orig. La operación se realiza en tiempo
     * O(n), donde \e n es el número de nodos del subárbol copiado.
     */
    void asignarSubarbol(const ArbolGeneral<T> &orig, const Nodo nod);

    /**
     * @brief Podar subárbol hijo más a la izquierda
     * @param n Nodo al que se le podará la rama hijo más a la izquierda.
     * @param dest Árbol que recibe la rama cortada
     * @pre \e n no es nulo y es un nodo válido del árbol receptor.
     *
     * Asigna un nuevo valor al árbol \e dest, con todos los elementos del
     * subárbol izquierdo del nodo \e n en el árbol receptor. Éste se queda
     * sin dichos nodos.
     *  La operación se realiza en tiempo O(1).
     */
    void podarHijoMasIzquierda(Nodo n, ArbolGeneral<T> &dest);

    /**
     * @brief Podar subárbol hermano derecha
     * @param n Nodo al que se le podará la rama hermano derecha.
     * @param dest Árbol que recibe la rama cortada
     * @pre \e n no es nulo y es un nodo válido del árbol receptor.
     *
     * Asigna un nuevo valor al árbol \e dest, con todos los elementos del
     * subárbol hermano derecho del nodo \e n en el árbol receptor. Éste se
     * queda sin dichos nodos.
     * La operación se realiza en tiempo O(1).
     */
    void podarHermanoDerecha(Nodo n, ArbolGeneral<T> &dest);

    /**
     * @brief Insertar subárbol hijo más a la izquierda
     * @param n: Nodo al que se insertará el árbol \e rama como hijo más a la
     * izquierda.
     * @param rama Árbol que se insertará como hijo más a la izquierda.
     * @pre \e n no es nulo y es un nodo válido del árbol receptor
     *
     * El árbol \e rama se inserta como hijo más a la izquierda del nodo \e n
     * del árbol receptor. El árbol \e rama queda vacío y los nodos que
     * estaban en el subárbol hijo más a la izquierda de \e n se desplazan a
     * la derecha, de forma que el anterior hijo más a la izquierda pasa a ser
     * el hermano a la derecha del nuevo hijo más a la izquierda.
     */
    void insertarHijoMasIzquierda(Nodo n, ArbolGeneral<T> &rama);

    /**
     * @brief Insertar subárbol hermano derecha
     * @param n Nodo al que se insertará el árbol \e rama como hermano a la
     * derecha.
     * @param rama Árbol que se insertará como hermano derecho.
     * @pre \e n no es nulo y es un nodo válido del árbol receptor
     *
     * El árbol \e rama se inserta como hermano derecho del nodo \e n del
     * árbol receptor. El árbol \e rama queda vacío y los nodos que estaban a
     * la derecha del nodo \e n pasan a la derecha del nuevo nodo.
     */
    void insertarHermanoDerecha(Nodo n, ArbolGeneral<T> &rama);

    /**
     * @brief Borra todos los elementos
     *
     * Borra todos los elementos del árbol receptor. Cuando termina, el árbol
     * está vacía. La operación se realiza en tiempo O(n), donde \e n es el
     * número de elementos del árbol receptor.
     */
    void clear();

    /**
     * @brief Número de elementos
     * @return El número de elementos del árbol receptor.
     *
     * La operación se realiza en tiempo O(n).
     * @see contar
     */
    int size() const;

    /**
     * @brief Vacío
     * @return Devuelve \e true si el número de elementos del árbol receptor
     * es cero, \e false en caso contrario.
     *
     * La operación se realiza en tiempo O(1).
     */
    bool empty() const;

	/**
	 * @brief Calcula la altura de un nodo
	 * @param n Nodo del que se desea calcular su altura
	 * @return Devuelve la altura de un nodo
	 */
	int altura(Nodo n) const;

	/**
	 * @brief Árbol reflejado
	 * @param n Nodo a partir del cual se hará el reflejado
	 */
	void reflejado(Nodo n);

    /**
     * @brief Operador de comparación (igualdad)
     * @param v ArbolGeneral con el que se desea comparar.
     * @return Devuelve \e true si el árbol receptor tiene los mismos
     * elementos y en el mismo orden, \e false en caso contrario.
     *
     * La operación se realiza en tiempo O(n).
     * @see sonIguales
     */
    bool operator==(const ArbolGeneral<T> &v) const;

    /**
     * @brief Operador de comparación (diferencia)
     * @param v ArbolGeneral con el que se desea comparar.
     * @return Devuelve \e true si el árbol receptor no tiene los mismos
     * elementos y en el mismo orden, \e false en caso contrario.
     *
     * La operación se realiza en tiempo O(n).
     */
    bool operator!=(const ArbolGeneral<T> &v) const;

	/**
	 * @brief Recuperar árbol a partir de sus tres recorridos
	 * @param preorden Recorrido en preorden
	 * @param inorden Recorrido en inorden
	 * @param postorden Recorrido en postorden
	 * @return Devuelve un árbol cuyos recorridos son estos tres
	 */
	friend ArbolGeneral<T> recuperarArbol(string preorden, string inorden, string postorden);

    /**
     * @brief Operador de extracción de flujo
     * @param in Stream de entrada
     * @param v Árbol que leer
     * @return Referencia al stream de entrada
     *
     * Lee de \e in un árbol y lo almacena en \e v. El formato aceptado para
     * la lectura se puede consultar en la función de salida.
     * @see leeArbol
     */
    template <class T>
    friend std::istream &operator>>(std::istream &in, ArbolGeneral<T> &v);
    /**
     * @brief Operador de inserción en flujo
     * @param out Stream de salida
     * @param v Árbol que escribir
     * @return Referencia al stream de salida
     *
     * Escribe en la salida todos los nodos del árbol \e v siguiendo un
     * recorrido en preorden. La forma de impresión de cada nodo es:
     *
     * - Si el nodo es nulo, imprime el carácter 'x'.
     * - Si el nodo no es nulo, imprime el carácter 'n' seguido de un
     * espacio, al que sigue la impresión de la etiqueta.
     *
     * @see escribeArbol
     */
    template <class T>
    friend std::ostream &operator<<(std::ostream &out, const ArbolGeneral<T> &v);

	/* ___________________________________________________________ */
	/*|                                                           |*/
	/*|                     CLASES ITERADORAS                     |*/
	/*|___________________________________________________________|*/

	class preorden_iterador {
	private:
		Nodo p;
	public:
		/**
		 * @brief Constructor por defecto
		 */
		preorden_iterador() : p(0) {}

		/**
		 * @brief Constructor con nodo
		 * @param n Nodo que se va a copiar
		 */
		preorden_iterador(const Nodo &n) : p(n) {}

		/**
		 * @brief Constructor de copia
		 * @param i Iterador que se va a copiar
		 */
		preorden_iterador (const preorden_iterador &i) : p(i.p) {}

		/**
		 * @brief Acceso constante a la información del nodo
		 */
		const T& operator*() const {
			assert (p!=0);
			return p->etiqueta;
		}

		/**
		 * @brief Acceso a la información del nodo
		 */
		T& operator*() {
			assert (p!=0);
			return p->etiqueta;
		}

		/**
		 * @brief Operación de igualdad entre dos posiciones
		 * @param n Nodo con el que se compara
		 * @return \e true si son iguales, \e false en caso contrario
		 */
		bool operator==(const preorden_iterador &i) {
			return p == i.p;
		}

		/**
		 * @brief Operación de desigualdad entre dos posiciones
		 * @param n Nodo con el que se compara
		 * @return \e false si son iguales, \e true en caso contrario
		 */
		bool operator!=(const preorden_iterador &i) {
			return p != i.p;
		}

		/**
		 * @brief Nodo del padre
		 * @return Devuelve el nodo apuntando al padre
		 */
		preorden_iterador padre() const {
			if (p->padre != 0)
				return preorden_iterador(p->padre);
			else
				return preorden_iterador();
		}

		/**
		 * @brief Nodo del hijo izquierda
		 * @return Devuelve el nodo apuntando al hijo izquierda
		 */
		preorden_iterador izquierda() const {
			if (p->izquierda != 0)
				return preorden_iterador(p->izquierda);
			else
				return preorden_iterador();
		}

		/**
		 * @brief Nodo del hijo derecha
		 * @return Devuelve el nodo apuntando al hijo derecha
		 */
		preorden_iterador derecha() const {
			if (p->derecha != 0)
				return preorden_iterador(p->derecha);
			else
				return preorden_iterador();
		}

		/**
		 * @brief Comprobación de nulidad
		 * @return Devuelve \e true si nulo, \e false en caso contrario
		 */
		bool nulo() const {
			return preorden_iterador == 0;
		}

		/**
		 * @brief Siguiente elemento en preorden
		 * @return Iterador al siguiente elemento en preorden
		 */
		preorden_iterador& operator++();

		/**
		 * @brief Elemento anterior en preorden
		 * @return Iterador al elemento anterior en preorden
		 */
		preorden_iterador& operator--();

		friend class ArbolGeneral;
		friend class reverse_preorden_iterador;
	};

	/**
	 * @brief Comienzo de un iterador \e preorden_iterador
	 * @return Iterador en preorden apuntando a la raíz
	 */
	preorden_iterador begin_pre() const;

	/**
	 * @brief Fin de un iterador \e preorden_iterador
	 * @return Iterador en preorden apuntando al final
	 */
	preorden_iterador end_pre() const;

	/**
	 * @brief Recorrido en preorden
	 * 
	 * Muestra el recorrido del árbol en preorden usando iteradores
	 */
	void recorrerPreorden() const;

	class reverse_preorden_iterador {
	  private:
	  	Nodo p;
	  public:
		/**
		 * @brief Constructor por defecto
		 */
		reverse_preorden_iterador() : p(0) {}

		/**
		 * @brief Constructor con nodo
		 * @param n Nodo que se va a copiar
		 */
		reverse_preorden_iterador(const Nodo &n) : p(n) {}

		/**
		 * @brief Constructor de copia
		 * @param i Iterador que se va a copiar
		 */
		reverse_preorden_iterador (const reverse_preorden_iterador &i) : p(i.p) {}

		/**
		 * @brief Acceso constante a la información del nodo
		 */
		const T& operator*() const {
			assert (p!=0);
			return p->etiqueta;
		}

		/**
		 * @brief Acceso a la información del nodo
		 */
		T& operator*() {
			assert (p!=0);
			return p->etiqueta;
		}

		/**
		 * @brief Operación de igualdad entre dos posiciones
		 * @param n Nodo con el que se compara
		 * @return \e true si son iguales, \e false en caso contrario
		 */
		bool operator==(const reverse_preorden_iterador &i) {
			return p == i.p;
		}

		/**
		 * @brief Operación de desigualdad entre dos posiciones
		 * @param n Nodo con el que se compara
		 * @return \e false si son iguales, \e true en caso contrario
		 */
		bool operator!=(const reverse_preorden_iterador &i) {
			return p != i.p;
		}

		/**
		 * @brief Nodo del padre
		 * @return Devuelve el nodo apuntando al padre
		 */
		reverse_preorden_iterador padre() const {
			if (p->padre != 0)
				return reverse_preorden_iterador(p->padre);
			else
				return reverse_preorden_iterador();
		}

		/**
		 * @brief Nodo del hijo izquierda
		 * @return Devuelve el nodo apuntando al hijo izquierda
		 */
		reverse_preorden_iterador izquierda() const {
			if (p->izquierda != 0)
				return reverse_preorden_iterador(p->izquierda);
			else
				return reverse_preorden_iterador();
		}

		/**
		 * @brief Nodo del hijo derecha
		 * @return Devuelve el nodo apuntando al hijo derecha
		 */
		reverse_preorden_iterador derecha() const {
			if (p->derecha != 0)
				return reverse_preorden_iterador(p->derecha);
			else
				return reverse_preorden_iterador();
		}

		/**
		 * @brief Comprobación de nulidad
		 * @return Devuelve \e true si nulo, \e false en caso contrario
		 */
		bool nulo() const {
			return reverse_preorden_iterador == 0;
		}

		/**
		 * @brief Siguiente elemento en preorden
		 * @return Iterador al siguiente elemento en preorden inverso
		 */
		reverse_preorden_iterador&& operator++();

		/**
		 * @brief Elemento anterior en preorden
		 * @return Iterador al elemento anterior en preorden inverso
		 */
		reverse_preorden_iterador&& operator--();

		friend class ArbolGeneral;
		friend class preorden_iterador;
	};

	/**
	 * @brief Comienzo de un iterador \e reverse_preorden_iterador
	 * @return Iterador en preorden inverso apuntando a la raíz
	 */
	reverse_preorden_iterador begin_reverse_pre() const;

	/**
	 * @brief Fin de un iterador \e reverse_preorden_iterador
	 * @return Iterador en preorden inverso apuntando al final
	 */
	reverse_preorden_iterador end_reverse_pre() const;

	/**
	 * @brief Recorrido en preorden inverso
	 * 
	 * Muestra el recorrido del árbol en preorden inverso usando iteradores
	 */
	void recorrerPreordenInverso() const;

	class inorden_iterador {
	private:
		Nodo p;
	public:
		/**
		 * @brief Constructor por defecto
		 */
		inorden_iterador() : p(0) {}

		/**
		 * @brief Constructor con nodo
		 * @param n Nodo que se va a copiar
		 */
		inorden_iterador(const Nodo &n) : p(n) {}

		/**
		 * @brief Constructor de copia
		 * @param i Iterador que se va a copiar
		 */
		inorden_iterador (const inorden_iterador &i) : p(i.p) {}

		/**
		 * @brief Acceso constante a la información del nodo
		 */
		const T& operator*() const {
			assert (p!=0);
			return p->etiqueta;
		}

		/**
		 * @brief Acceso a la información del nodo
		 */
		T& operator*() {
			assert (p!=0);
			return p->etiqueta;
		}

		/**
		 * @brief Operación de igualdad entre dos posiciones
		 * @param n Nodo con el que se compara
		 * @return \e true si son iguales, \e false en caso contrario
		 */
		bool operator==(const inorden_iterador &i) {
			return p == i.p;
		}

		/**
		 * @brief Operación de desigualdad entre dos posiciones
		 * @param n Nodo con el que se compara
		 * @return \e false si son iguales, \e true en caso contrario
		 */
		bool operator!=(const inorden_iterador &i) {
			return p != i.p;
		}

		/**
		 * @brief Nodo del padre
		 * @return Devuelve el nodo apuntando al padre
		 */
		inorden_iterador padre() const {
			if (p->padre != 0)
				return inorden_iterador(p->padre);
			else
				return inorden_iterador();
		}

		/**
		 * @brief Nodo del hijo izquierda
		 * @return Devuelve el nodo apuntando al hijo izquierda
		 */
		inorden_iterador izquierda() const {
			if (p->izquierda != 0)
				return inorden_iterador(p->izquierda);
			else
				return inorden_iterador();
		}

		/**
		 * @brief Nodo del hijo derecha
		 * @return Devuelve el nodo apuntando al hijo derecha
		 */
		inorden_iterador derecha() const {
			if (p->derecha != 0)
				return inorden_iterador(p->derecha);
			else
				return inorden_iterador();
		}

		/**
		 * @brief Comprobación de nulidad
		 * @return Devuelve \e true si nulo, \e false en caso contrario
		 */
		bool nulo() const {
			return inorden_iterador == 0;
		}

		/**
		 * @brief Siguiente elemento en inorden
		 * @return Iterador al siguiente elemento en inorden
		 */
		inorden_iterador&& operator++();

		/**
		 * @brief Elemento anterior en inorden
		 * @return Iterador al elemento anterior en inorden
		 */
		inorden_iterador&& operator--();

		friend class ArbolGeneral;
		friend class reverse_inorden_iterador;
	};

	/**
	 * @brief Comienzo de un iterador \e inorden_iterador
	 * @return Iterador en inorden apuntando a la raíz
	 */
	inorden_iterador begin_in() const;

	/**
	 * @brief Fin de un iterador \e inorden_iterador
	 * @return Iterador en inorden apuntando al final
	 */
	inorden_iterador end_in() const;

	/**
	 * @brief Recorrido en inorden
	 * 
	 * Muestra el recorrido del árbol en inorden usando iteradores
	 */
	void recorrerInorden() const;

	class reverse_inorden_iterador {
	  private:
	  	Nodo p;
	  public:
		/**
		 * @brief Constructor por defecto
		 */
		reverse_inorden_iterador() : p(0) {}

		/**
		 * @brief Constructor con nodo
		 * @param n Nodo que se va a copiar
		 */
		reverse_inorden_iterador(const Nodo &n) : p(n) {}

		/**
		 * @brief Constructor de copia
		 * @param i Iterador que se va a copiar
		 */
		reverse_inorden_iterador (const reverse_inorden_iterador &i) : p(i.p) {}

		/**
		 * @brief Acceso constante a la información del nodo
		 */
		const T& operator*() const {
			assert (p!=0);
			return p->etiqueta;
		}

		/**
		 * @brief Acceso a la información del nodo
		 */
		T& operator*() {
			assert (p!=0);
			return p->etiqueta;
		}

		/**
		 * @brief Operación de igualdad entre dos posiciones
		 * @param n Nodo con el que se compara
		 * @return \e true si son iguales, \e false en caso contrario
		 */
		bool operator==(const reverse_inorden_iterador &i) {
			return p == i.p;
		}

		/**
		 * @brief Operación de desigualdad entre dos posiciones
		 * @param n Nodo con el que se compara
		 * @return \e false si son iguales, \e true en caso contrario
		 */
		bool operator!=(const reverse_inorden_iterador &i) {
			return p != i.p;
		}

		/**
		 * @brief Nodo del padre
		 * @return Devuelve el nodo apuntando al padre
		 */
		reverse_inorden_iterador padre() const {
			if (p->padre != 0)
				return reverse_inorden_iterador(p->padre);
			else
				return reverse_inorden_iterador();
		}

		/**
		 * @brief Nodo del hijo izquierda
		 * @return Devuelve el nodo apuntando al hijo izquierda
		 */
		reverse_inorden_iterador izquierda() const {
			if (p->izquierda != 0)
				return reverse_inorden_iterador(p->izquierda);
			else
				return reverse_inorden_iterador();
		}

		/**
		 * @brief Nodo del hijo derecha
		 * @return Devuelve el nodo apuntando al hijo derecha
		 */
		reverse_inorden_iterador derecha() const {
			if (p->derecha != 0)
				return reverse_inorden_iterador(p->derecha);
			else
				return reverse_inorden_iterador();
		}

		/**
		 * @brief Comprobación de nulidad
		 * @return Devuelve \e true si nulo, \e false en caso contrario
		 */
		bool nulo() const {
			return reverse_inorden_iterador == 0;
		}

		/**
		 * @brief Siguiente elemento en inorden
		 * @return Iterador al siguiente elemento en inorden inverso
		 */
		reverse_inorden_iterador&& operator++();

		/**
		 * @brief Elemento anterior en inorden
		 * @return Iterador al elemento anterior en inorden inverso
		 */
		reverse_inorden_iterador&& operator--();

		friend class ArbolGeneral;
		friend class inorden_iterador;
	};

	/**
	 * @brief Comienzo de un iterador \e reverse_inorden_iterador
	 * @return Iterador en inorden inverso apuntando a la raíz
	 */
	reverse_inorden_iterador begin_reverse_in() const;

	/**
	 * @brief Fin de un iterador \e reverse_inorden_iterador
	 * @return Iterador en inorden inverso apuntando al final
	 */
	reverse_inorden_iterador end_reverse_in() const;

	/**
	 * @brief Recorrido en inorden inverso
	 * 
	 * Muestra el recorrido del árbol en inorden inverso usando iteradores
	 */
	void recorrerInordenInverso() const;

	class postorden_iterador {
	private:
		Nodo p;
	public:
		/**
		 * @brief Constructor por defecto
		 */
		postorden_iterador() : p(0) {}

		/**
		 * @brief Constructor con nodo
		 * @param n Nodo que se va a copiar
		 */
		postorden_iterador(const Nodo &n) : p(n) {}

		/**
		 * @brief Constructor de copia
		 * @param i Iterador que se va a copiar
		 */
		postorden_iterador (const postorden_iterador &i) : p(i.p) {}

		/**
		 * @brief Acceso constante a la postformación del nodo
		 */
		const T& operator*() const {
			assert (p!=0);
			return p->etiqueta;
		}

		/**
		 * @brief Acceso a la postformación del nodo
		 */
		T& operator*() {
			assert (p!=0);
			return p->etiqueta;
		}

		/**
		 * @brief Operación de igualdad entre dos posiciones
		 * @param n Nodo con el que se compara
		 * @return \e true si son iguales, \e false en caso contrario
		 */
		bool operator==(const postorden_iterador &i) {
			return p == i.p;
		}

		/**
		 * @brief Operación de desigualdad entre dos posiciones
		 * @param n Nodo con el que se compara
		 * @return \e false si son iguales, \e true en caso contrario
		 */
		bool operator!=(const postorden_iterador &i) {
			return p != i.p;
		}

		/**
		 * @brief Nodo del padre
		 * @return Devuelve el nodo apuntando al padre
		 */
		postorden_iterador padre() const {
			if (p->padre != 0)
				return postorden_iterador(p->padre);
			else
				return postorden_iterador();
		}

		/**
		 * @brief Nodo del hijo izquierda
		 * @return Devuelve el nodo apuntando al hijo izquierda
		 */
		postorden_iterador izquierda() const {
			if (p->izquierda != 0)
				return postorden_iterador(p->izquierda);
			else
				return postorden_iterador();
		}

		/**
		 * @brief Nodo del hijo derecha
		 * @return Devuelve el nodo apuntando al hijo derecha
		 */
		postorden_iterador derecha() const {
			if (p->derecha != 0)
				return postorden_iterador(p->derecha);
			else
				return postorden_iterador();
		}

		/**
		 * @brief Comprobación de nulidad
		 * @return Devuelve \e true si nulo, \e false en caso contrario
		 */
		bool nulo() const {
			return postorden_iterador == 0;
		}

		/**
		 * @brief Siguiente elemento en postorden
		 * @return Iterador al siguiente elemento en postorden
		 */
		postorden_iterador&& operator++();

		/**
		 * @brief Elemento anterior en postorden
		 * @return Iterador al elemento anterior en postorden
		 */
		postorden_iterador&& operator--();

		friend class ArbolGeneral;
		friend class reverse_postorden_iterador;
	};

	/**
	 * @brief Comienzo de un iterador \e postorden_iterador
	 * @return Iterador en postorden apuntando a la raíz
	 */
	postorden_iterador begpost_post() const;

	/**
	 * @brief Fpost de un iterador \e postorden_iterador
	 * @return Iterador en postorden apuntando al fpostal
	 */
	postorden_iterador end_post() const;

	/**
	 * @brief Recorrido en postorden
	 * 
	 * Muestra el recorrido del árbol en postorden usando iteradores
	 */
	void recorrerPostorden() const;

	class reverse_postorden_iterador {
	  private:
	  	Nodo p;
	  public:
		/**
		 * @brief Constructor por defecto
		 */
		reverse_postorden_iterador() : p(0) {}

		/**
		 * @brief Constructor con nodo
		 * @param n Nodo que se va a copiar
		 */
		reverse_postorden_iterador(const Nodo &n) : p(n) {}

		/**
		 * @brief Constructor de copia
		 * @param i Iterador que se va a copiar
		 */
		reverse_postorden_iterador (const reverse_postorden_iterador &i) : p(i.p) {}

		/**
		 * @brief Acceso constante a la postformación del nodo
		 */
		const T& operator*() const {
			assert (p!=0);
			return p->etiqueta;
		}

		/**
		 * @brief Acceso a la postformación del nodo
		 */
		T& operator*() {
			assert (p!=0);
			return p->etiqueta;
		}

		/**
		 * @brief Operación de igualdad entre dos posiciones
		 * @param n Nodo con el que se compara
		 * @return \e true si son iguales, \e false en caso contrario
		 */
		bool operator==(const reverse_postorden_iterador &i) {
			return p == i.p;
		}

		/**
		 * @brief Operación de desigualdad entre dos posiciones
		 * @param n Nodo con el que se compara
		 * @return \e false si son iguales, \e true en caso contrario
		 */
		bool operator!=(const reverse_postorden_iterador &i) {
			return p != i.p;
		}

		/**
		 * @brief Nodo del padre
		 * @return Devuelve el nodo apuntando al padre
		 */
		reverse_postorden_iterador padre() const {
			if (p->padre != 0)
				return reverse_postorden_iterador(p->padre);
			else
				return reverse_postorden_iterador();
		}

		/**
		 * @brief Nodo del hijo izquierda
		 * @return Devuelve el nodo apuntando al hijo izquierda
		 */
		reverse_postorden_iterador izquierda() const {
			if (p->izquierda != 0)
				return reverse_postorden_iterador(p->izquierda);
			else
				return reverse_postorden_iterador();
		}

		/**
		 * @brief Nodo del hijo derecha
		 * @return Devuelve el nodo apuntando al hijo derecha
		 */
		reverse_postorden_iterador derecha() const {
			if (p->derecha != 0)
				return reverse_postorden_iterador(p->derecha);
			else
				return reverse_postorden_iterador();
		}

		/**
		 * @brief Comprobación de nulidad
		 * @return Devuelve \e true si nulo, \e false en caso contrario
		 */
		bool nulo() const {
			return reverse_postorden_iterador == 0;
		}

		/**
		 * @brief Siguiente elemento en postorden
		 * @return Iterador al siguiente elemento en postorden postverso
		 */
		reverse_postorden_iterador&& operator++();

		/**
		 * @brief Elemento anterior en postorden
		 * @return Iterador al elemento anterior en postorden postverso
		 */
		reverse_postorden_iterador&& operator--();

		friend class ArbolGeneral;
		friend class postorden_iterador;
	};

	/**
	 * @brief Comienzo de un iterador \e reverse_postorden_iterador
	 * @return Iterador en postorden postverso apuntando a la raíz
	 */
	reverse_postorden_iterador begpost_reverse_post() const;

	/**
	 * @brief Fpost de un iterador \e reverse_postorden_iterador
	 * @return Iterador en postorden postverso apuntando al fpostal
	 */
	reverse_postorden_iterador end_reverse_post() const;

	/**
	 * @brief Recorrido en postorden postverso
	 * 
	 * Muestra el recorrido del árbol en postorden postverso usando iteradores
	 */
	void recorrerPostordenPostverso() const;
};



/*________________________________________________ */


/*____________________________________________________________ */



/*____________________________________________________________ */



/*____________________________________________________________ */
/*____________________________________________________________ */
//               FUNCIONES PUBLICAS
/*____________________________________________________________ */
/*____________________________________________________________ */











































template<class T>
void preorden(std::ostream &out, nodo *nod) const {
	if (nod == 0)
		out << "x ";
	else {
		out << "n " << nod->etiqueta << " ";
		preorden(out, nod->izqda);
		preorden(out, nod->drcha);
	}
}

template<class T>
void ArbolGeneral<T>::inorden(std::ostream &out, nodo *nod) const {
	if (nod == 0)
		out << "x ";
	else {
		inorden(out, nod->izqda);
		out << "n " << nod->etiqueta << " ";
		inorden(out, nod->drcha);
	}
}

template<class T>
void ArbolGeneral<T>::postorden(std::ostream &out, nodo *nod) const {
	if (nod == 0)
		out << "x ";
	else {
		postorden(out, nod->izqda);
		postorden(out, nod->drcha);
		out << "n " << nod->etiqueta << " ";
	}
}

template<class T>
int ArbolGeneral<T>::altura(nodo *nod) const {
	int contador
}

template<class T>
void ArbolGeneral<T>::construir(std::istream &in, nodo *&nod) {

}

template<class T>
typename ArbolGeneral<T>::Nodo ArbolGeneral<T>::reflejar(nodo *&nod) const {

}

#include "ArbolGeneral.cpp"

#endif