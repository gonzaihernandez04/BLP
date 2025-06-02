
#include <stdio.h>
#include <stdlib.h>
#include "Utilities/utilidades.h"


typedef struct Materia{
    char nombreMateria[55];
    int inscripto;
    int aprobada; //Indica si aprobo la materia
    int firstTest;
    int secondTest;

} Materia;

typedef struct Estudiante{
    char nombre[45];
    char nacimiento[10];
    int dni;
    int legajo;
    Materia materias [48]; //Hasta 48 materias. POR DEFAULT

} Estudiante;



Materia *newMateria(char nombreMateria[55]){
    Materia *materia = (Materia *)malloc(sizeof(Materia));
    strcpy(materia->nombreMateria, nombreMateria); //  Copia segura de string
      materia->inscripto = 0;
    materia->aprobada = 0;
    materia->firstTest = 0;
    materia->secondTest = 0;
    return materia;
}

typedef struct nodeDL
{
    Estudiante *estudiante;
    struct nodeDL *next;
    struct nodeDL *prev;
} nodeDL;

typedef struct
{
    nodeDL *head;
    nodeDL *tail;
    int size;
} doubleLinkedList;

// Crear nuevo nodo
nodeDL *newNode(Estudiante *estudiante)
{
    nodeDL *nd = (nodeDL *)malloc(sizeof(nodeDL));
    if (nd == NULL)
        return NULL;
    nd->estudiante = estudiante;
    nd->next = NULL;
    nd->prev = NULL;
    return nd;
}

// Insertar nodo al inicio de la lista
void prepend(doubleLinkedList *lista, Estudiante *estudiante)
{
    nodeDL *nodeNew = newNode(estudiante);
    if (lista->size == 0)
    {
        lista->head = nodeNew;
        lista->tail = nodeNew;
    }
    else
    {
        nodeNew->next = lista->head;
        lista->head->prev = nodeNew;
        lista->head = nodeNew;
    }
    lista->size++;
}

// Insertar nodo al final de la lista
void append(doubleLinkedList *lista, Estudiante *estudiante)
{
    nodeDL *nodeNew = newNode(estudiante);
    if (lista->size == 0)
    {
        lista->head = nodeNew;
        lista->tail = nodeNew;
    }
    else
    {
        nodeNew->prev = lista->tail;
        lista->tail->next = nodeNew;
        lista->tail = nodeNew;
    }
    lista->size++;
}

// Imprimir la lista
void printList(doubleLinkedList *lista)
{
    nodeDL *node = lista->head;
    if (node != NULL)
    {
        printf("Lista: ");
        while (node != NULL)
        {
            if (node->next != NULL)
            {
                printf("%s->", node->estudiante->nombre);
            }
            else
            {
                printf("%s\n", node->estudiante->nombre);
            }

            node = node->next;
            
        }
    }
    else
    {
        printf("Lista vacia. \n");
    }
}

// Limpiar la lista
void clear(doubleLinkedList *lista)
{
    nodeDL *current = lista->head;
    while (current != NULL)
    {
        nodeDL *next = current->next;
        free(current);
        current = NULL;
        current = next;
    }
    lista->head = NULL;
    lista->tail = NULL;
    lista->size = 0;
    printf("La lista se vacio");
}

// Borrar nodo de la lista
void deleteNode(Estudiante *estudiante, doubleLinkedList *lista)
{

    nodeDL *node = lista->head;
    if (lista->size > 0) // Verificamos que la lista o el dato no esten vacios
    {
        while (node != NULL) // Mientras  llegue a la cola y el siguiente a el sea nulo
        {

            if (node->estudiante == estudiante)
            {
                if (node->prev != NULL)
                {
                    node->prev->next = node->next;
                }
                else
                {
                    lista->head = node->next; // Es el primer nodo
                }
                if (node->next != NULL)
                {

                    node->next->prev = node->prev;
                }
                else
                {
                    lista->tail = node->prev; // Es el último nodo
                }

                free(node); // libero memoria en nodo ya que encontro el valor y lo elimino
                node = NULL;
                lista->size--;
                printf("Valor eliminado con exito");
                return;
            }

            node = node->next;
        }
    }
    printf("Nodo con valor %d no encontrado.\n", estudiante);
}

nodeDL *findNode(Estudiante *estudiante, doubleLinkedList *lista)
{
    nodeDL *node = lista->head;
    if (lista->size > 0)
    {

        while (node != NULL)
        {
            if (node->estudiante == estudiante)
            {
                printf("El valor del nodo encontrado: %d ", node->estudiante);
                return node;
            }

            node = node->next;
        }
    }
    printf("Valor del nodo no encontrado");
    return NULL;
}


int size(doubleLinkedList *lista)
{
    return lista->size;
}



// Funcion para conv



/// Find node by name

   nodeDL *findNodeByName(doubleLinkedList *lista,char nombre[45])
{
    nodeDL *node = lista->head;
    char nombreUpper[45];
    strcpy(nombreUpper, nombre); // Copia el nombre a una variable temporal para no modificar el original

    upperCase(nombreUpper); // Convierte el nombre a mayúsculas

    if (lista->size > 0)
    {

        while (node != NULL)
        {
            char nombreEstudianteMayus[45];
            strcpy(nombreEstudianteMayus, node->estudiante->nombre);
            upperCase(nombreEstudianteMayus);

            if (strcmp(nombreEstudianteMayus, nombreUpper) == 0)
            {
                return node;
            }

            node = node->next;
        }
    }
    return NULL;
}


