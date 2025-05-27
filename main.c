#include <stdio.h>
#include <stdlib.h>

//Estructura del Node Double Linked
typedef struct nodeDL
{
    int date; //Dato del nodo
    struct nodeDL *next; //Siguiente al Nodo
    struct nodeDL *prev; //Previo al Nodo
} nodeDL;

//Estructura de Double Linked List
typedef struct
{
    nodeDL *head; //Cabeza de la lista
    nodeDL *tail; //Cola de la lista
    int size;
} doubleLinkedList;

// Crear nuevo nodo
nodeDL *newNode(int date)
{
    nodeDL *nd = (nodeDL *)malloc(sizeof(nodeDL));
    if (nd == NULL)
        return NULL;
    nd->date = date; 
    nd->next = NULL;
    nd->prev = NULL;
    return nd;
}

// Insertar nodo al inicio de la lista
void prepend(doubleLinkedList *lista, int date)
{
    nodeDL *nodeNew = newNode(date);
    if (lista->size == 0) //Lista vacia
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
    if (lista->size == 0) //Si esta vacia, el nodo ingresado va ser la cabeza y cola.
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
                printf("[%d]->", node->date);
            }
            else
            {
                printf("[%d]", node->date);
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
    while (current != NULL) //Mientras que el actual no sea null 
    {
        nodeDL *next = current->next; //Guardamos el nodo siguiente
        free(current); //Liberamos el nodo 
        current = NULL;
        current = next; //Guardamos el siguiente como el actual
    }
    lista->head = NULL;
    lista->tail = NULL;
    lista->size = 0;
    printf("La lista se vacio");
}

// Borrar nodo de la lista
void deleteNode(int date, doubleLinkedList *lista)
{

    nodeDL *node = lista->head;
    if (lista->size > 0) // Verificamos que la lista o el dato no esten vacios
    {
        while (node != NULL) // Mientras  llegue a la cola y el siguiente a el sea nulo
        {

            if (node->date == date)
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
    printf("Nodo con valor %d no encontrado.\n", date);
}

nodeDL *findNode(int date, doubleLinkedList *lista)
{
    nodeDL *node = lista->head;
    if (lista->size > 0) //Verificamos que existe una lista
    {

        while (node != NULL)
        {
            if (node->date == date)
            {
                printf("El valor del nodo encontrado: %d ", node->date);
                return node;
            }

            node = node->next;
        }
    }
    printf("Valor del nodo no encontrado");
    return NULL;
}
void main()
{
    doubleLinkedList lista = {NULL, NULL, 0};
    int opc = 0;
    int data;
    int flag = 0;
    int inicioFinal;

    while (flag == 0)
    {
        printf("\nIngrese una opcion entre las posibles: 1-Agregar 2-Eliminar 3-Buscar 4-Imprimir 5-Limpiar 6-Salir: ");
        scanf("%d", &opc);

    switch (opc)
        {
            
        case 1:

            printf("Ingrese el valor del nodo: ");
            scanf("%d", &data);
            printf("Donde desea agregar? 1- Inicio 2- Final: ");
            scanf("%d", &inicioFinal);
            if (inicioFinal == 1)
            {
                prepend(&lista, data);
                data = 0;
                break;
            }
            else if (inicioFinal == 2)
            {
                append(&lista, data);
                data = 0;
                break;
            
        }else{
            printf("Opcion inexistente.");
            break;
        }
            printf("Valor ingresado con exito.");

        case 2:

            printf("Ingrese el valor del nodo a eliminar: ");
            scanf("%d", &data);
            deleteNode(data, &lista);
            data = 0;
            break;

        case 3:
            printf("Ingrese el valor del nodo para buscar en la lista: ");
            scanf("%d", &data);
            nodeDL *nodoBuscado;
            nodoBuscado = findNode(data, &lista);
       
            break;

        case 4:
            printList(&lista);
            break;

        case 5:
            clear(&lista);
            break;

        case 6:
            printf("Muchas gracias por usar este programa! Lo esperamos pronto.\n");
            flag = 1;
            break;

        default:
            printf("Opcion no encontrada, por favor ingrese otro valor.\n");
            break;
        }
}
    }
