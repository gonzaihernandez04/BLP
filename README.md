Definir una estructura Nodo que contenga:

Un campo int dato para almacenar el valor del nodo.

Un puntero al siguiente nodo.

/

Funciones obligatorias:

Nodo* crearNodo(int dato) – Crea un nodo nuevo con un dato dado. X

void insertarAlInicio(Nodo** cabeza, int dato) – Inserta un nodo al comienzo de la lista. X

void insertarAlFinal(Nodo** cabeza, int dato) – Inserta un nodo al final de la lista. X

void eliminarNodo(Nodo** cabeza, int dato) – Elimina el primer nodo que contenga el dato especificado.

Nodo* buscarNodo(Nodo* cabeza, int dato) – Devuelve un puntero al nodo que contiene el dato (o NULL si no se encuentra).

void imprimirLista(Nodo* cabeza) – Imprime todos los elementos de la lista.

void liberarLista(Nodo** cabeza) – Libera toda la memoria utilizada por la lista.

/
Programa principal:

Implementa un menú interactivo para probar las funciones anteriores (agregar, eliminar, buscar, imprimir, salir).

Permitir al usuario ingresar valores por consola.