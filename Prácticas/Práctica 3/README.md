**`ED`  >  Prácticas  >  Práctica 3**

# :three: Estructuras de datos lineales

## Estructura de la práctica

A continuación se listan los ficheros de esta práctica:

| Fichero | Descripción |
| --- | --- |
| **`Pila_max`** | Clase implementada: se ha decidido hacer **con colas** |
| `Pila_max_cola.h` | Fichero de cabecera de `Pila_max` con colas |
| `Pila_max_cola.cpp` | Implementación de `Pila_max` con colas |
| | |
| `test.cpp` | Fichero de prueba para la clase `Pila_max` |
| | |
| **`Cola`** | Clase para el TDA lineal _cola_ usada en la implementación anterior |
| `Cola.h` | Fichero de cabecera para el TDA `Cola` |
| `Cola.cpp` | Implementación del TDA `Cola` |

## Cómo implementar una pila con una cola

El conflicto entre una pila y una cola reside en la forma de insertar  y extraer elementos:

* Una **pila** es una estructura **LIFO**, en el que el último insertado es el primero en eliminar.
* Una **cola** es una estructura **FIFO**, en el que el primero insertado es el primero en eliminar.

Hablaremos por tanto sobre cómo implementar las operaciones de insertado (`poner()`) y eliminación (`quitar()`). Para ello intentaremos que los elementos de la pila queden almacenados en la cola **siempre en orden inverso**. De este modo, será mucho más sencillo implementar estas dos funciones, que especificaremos a continuación.

### El método `quitar()`

Si en nuestra cola los elementos se insertan en orden inverso, la operación `quitar()` de la pila equivaldrá a la operación `quitar()` de la cola.

### El método `poner()`

Debemos de implementarlo para que, al acabar la implementación, en la cola figure como que sea el último elemento que se ha insertado, pudiendo de este modo hacer uso de `quitar()` de la forma anteriormente mencionada.

Para ello basta seguir los siguientes pasos:

1. Insertamos el elemento que queremos insertar, `elem`, en la cola. Será por tanto el último en eliminar.
2. Uno a uno, repetimos el siguiente proceso con los elementos de la cola que quedaban antes de insertar `elem`:
    1. Copiamos el elemento del frente de la cola (`frente()`) en una variable temporal.
    2. Eliminamos (`quitar()`) el primer elemento de la cola en ser insertado, es decir, el elemento del frente (estructura FIFO).
    3. Insertamos (`poner()`) dicho elemento, almacenado en la variable tempral, en la cola.

Al acabar, tendremos almacenado en la cola los elementos de la pila en orden inverso, como hemos dicho anteriormente.