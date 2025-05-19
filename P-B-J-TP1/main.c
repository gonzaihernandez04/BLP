#include <stdio.h>
#include <stdlib.h>

typedef struct nodeDL {
    int date;
    struct nodeDL *next;
    struct nodeDL *prev;
} nodeDL;

typedef struct {
    nodeDL *head;
    nodeDL *tail;
    int size;
} doubleLinkedList;

// Crear nuevo nodo
nodeDL *newNode(int date)
{
    nodeDL *nd = (nodeDL *)malloc(sizeof(nodeDL));
    if (nd == NULL) return NULL;
    nd->date = date;
    nd->next = NULL;
    nd->prev = NULL;
    return nd;
}

// Insertar nodo al inicio de la lista
void prepend(doubleLinkedList *lista, int date)
{
    nodeDL *nodeNew = newNode(date);
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
void append(doubleLinkedList *lista, int date)
{
    nodeDL *nodeNew = newNode(date);
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
void printList(doubleLinkedList *lista){
    nodeDL *node = lista->head;
    printf("Lista: ");
    while (node != NULL) {
        printf("%d ", node->date);
        node = node->next;
    }
    printf("\n");
}

// Limpiar la lista
void clear(doubleLinkedList *lista){
    nodeDL *current = lista->head;
    while (current != NULL) {
        nodeDL *next = current->next;
        free(current);
        current = next;
    }
    lista->head = NULL;
    lista->tail = NULL;
    lista->size = 0;
}

int main(){
    doubleLinkedList lista = {NULL, NULL, 0};

    prepend(&lista, 10);
    prepend(&lista, 20);
    prepend(&lista, 30);

    printList(&lista); // Debería mostrar: Lista: 30 20 10

    clear(&lista);
    return 0;
}