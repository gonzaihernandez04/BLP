#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Materia
{
    char nombreMateria[55];
    int inscripto;
    int aprobada; // Indica si aprobo la materia
    int firstTest;
    int secondTest;

} Materia;

typedef struct Estudiante
{
    char nombre[45];
    char nacimiento[10];
    int dni;
    int legajo;
    Materia materias[48]; // Hasta 48 materias.
    int cantMaterias ;

} Estudiante;

Materia *newMateria(char nombreMateria[55])
{
    Materia *materia = (Materia *)malloc(sizeof(Materia));
    strcpy(materia->nombreMateria, nombreMateria); // Copia segura de string
    materia->inscripto = 0;                        // Booleano
    materia->aprobada = 0;                         // Booleano
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
                    lista->tail = node->prev; // Es el Ãºltimo nodo
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

nodeDL *findEstudiante(char estudiante[55], doubleLinkedList *lista)
{
    nodeDL *node = lista->head;
    if (lista->size > 0)
    {
        while (node != NULL)
        {
            if (strcmp(node->estudiante->nombre, estudiante) == 0)
            {
                return node;
            }

            node = node->next;
        }
    }
    printf("\n-Estudiante no encontrado\n");
    return NULL;
}

// Funcion para buscar si la materia ingresada existe en el plan
int findMateria(char nombreMateria[55], int cantMaterias, Materia *materias[])
{
    for (int i = 0; i < cantMaterias; i++)
    {
        if (strcmp(materias[i]->nombreMateria, nombreMateria) == 0)
        {
            return i; // Devuelve el índice si la encuentra
        }
    }
    return -1; // No se encontró la materia
}

void agregarMateria(Estudiante *estudiante, Materia *materia)
{
    if (estudiante->cantMaterias < 48)
    {
        estudiante->materias[estudiante->cantMaterias] = *materia;
        estudiante->cantMaterias++;
    }
    else
    {
        printf("No se pueden agregar más materias.\n");
    }
}

void eliminarMateria(Estudiante *estudiante, char materia[55])
{
    if (estudiante == NULL) {
        printf("Error: puntero estudiante es NULL.\n");
        return;
    }

    int indice = -1;
    for (int i = 0; i < estudiante->cantMaterias; i++) {
    printf("Materia %d: %s\n", i, estudiante->materias[i].nombreMateria);
}
    for (int i = 0; i < estudiante->cantMaterias-1; i++) // Busco la posicion de la materia a borrar
    {
        printf("cantMaterias: %d\n", estudiante->cantMaterias);
        if (strcmp(estudiante->materias[i].nombreMateria, materia) == 0)
        {
            indice = i;
            break;
        }
    }
    if (indice != -1)
    {
        for (int i = indice; i < estudiante->cantMaterias - 1; i++)
        {
            estudiante->materias[i] = estudiante->materias[i + 1]; // Sobreescribe con la siguiente
        }
        estudiante->cantMaterias--;
        printf("\n-Materia eliminada con éxito.\n");
        return;
    }
    else
    {
        printf("\n-Materia no encontrada.\n");
        return;
    }
}

void mostrarMaterias(nodeDL *nodoEstudiante)
{
    for (int i = 0; i < nodoEstudiante->estudiante->cantMaterias; i++)
    {
        if (i != nodoEstudiante->estudiante->cantMaterias - 1)
        {
            printf("\n[%s]->", nodoEstudiante->estudiante->materias[i].nombreMateria);
        }
        else
        {
            printf("[%s]\n", nodoEstudiante->estudiante->materias[i].nombreMateria);
        }
    }
}

void anortarseMateria(nodeDL *nodoEstudiante, char nombreMateria[55], int cantMaterias, Materia *materias[])
{
    int encontrado = findMateria(nombreMateria, cantMaterias, materias);
    if (encontrado != -1)
    {  
        // Verificar si ya está anotado
        for (int i = 0; i < nodoEstudiante->estudiante->cantMaterias; i++)
        {
            if (strcmp(nodoEstudiante->estudiante->materias[i].nombreMateria, nombreMateria) == 0)
            {
                if (nodoEstudiante->estudiante->materias[i].inscripto == 0)
                {
                    agregarMateria(nodoEstudiante->estudiante, materias[encontrado]);
                    
                }
                else
                {
                    printf("Ya estás anotado en esa materia.\n");
                }
                return; // Salir después de encontrar la materia
            }
        }
        // Si no está anotado, agregar la materia
        agregarMateria(nodoEstudiante->estudiante, materias[encontrado]);
        printf("\n-Materia agregada con éxito.\n");
    }
    else
    {
        printf("Materia no encontrada en el plan.\n");
    }
}
