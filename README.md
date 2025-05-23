# 💻 Trabajo Práctico N°1 - Programación Bajo Nivel

Bienvenido al repositorio del **Trabajo Práctico N°1** de Programación Bajo Nivel.  
Aquí encontrarás la implementación de una **lista doblemente enlazada** en C, junto con todas las funciones necesarias para manipularla.

---
## 👨‍💻 Integrantes

- 🦸‍♂️ **Agustin Menechino**
- 🦸‍♂️ **Gonzalo Hernandez**
- 🦸‍♂️ **Laureano Brocos**
- 🦸‍♂️ **Ivan Dominguez**

---
## 📋 Consignas

### 1. Definir una estructura Nodo que contenga:
- Un campo `int dato` para almacenar el valor del nodo.
- Un puntero al siguiente nodo.

---

### 2. Funciones obligatorias

```c
// Crea un nodo nuevo con un dato dado.
Nodo* crearNodo(int dato);

// Inserta un nodo al comienzo de la lista.
void insertarAlInicio(Nodo** cabeza, int dato);

// Inserta un nodo al final de la lista.
void insertarAlFinal(Nodo** cabeza, int dato);

// Elimina el primer nodo que contenga el dato especificado.
void eliminarNodo(Nodo** cabeza, int dato);

// Devuelve un puntero al nodo que contiene el dato (o NULL si no se encuentra).
Nodo* buscarNodo(Nodo* cabeza, int dato);

// Imprime todos los elementos de la lista.
void imprimirLista(Nodo* cabeza);

// Libera toda la memoria utilizada por la lista.
void liberarLista(Nodo** cabeza);
```

---

### 3. Programa principal

- Implementa un **menú interactivo** para probar las funciones anteriores:  
  ➤ Agregar  
  ➤ Eliminar  
  ➤ Buscar  
  ➤ Imprimir  
  ➤ Salir


