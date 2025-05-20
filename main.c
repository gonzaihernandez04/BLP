#include <stdio.h>
#include <stdlib.h>

typedef struct nodeDL
{
    int date;
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
void printList(doubleLinkedList *lista)
{
    nodeDL *node = lista->head;
    printf("Lista: ");
    while (node != NULL)
    {
        if (node->next != NULL)
        {
            printf("%d->", node->date);
        }
        else
        {
            printf("%d", node->date);
        }

        node = node->next;
    }
    printf("\n");
}

// Limpiar la lista
void clear(doubleLinkedList *lista)
{
    nodeDL *current = lista->head;
    while (current != NULL)
    {
        nodeDL *next = current->next;
        free(current);
        current = next;
    }
    lista->head = NULL;
    lista->tail = NULL;
    lista->size = 0;
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
                }else
                {
                    lista->tail = node->prev; // Es el último nodo
                }

                free(node); //libero memoria en nodo ya que encontro el valor y lo elimino
                lista->size--;
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
    if (lista->size > 0)
    {
 

        while (node!=NULL)
        {
            if (node->date == date)
            {
                return node;
            }
            
              node = node->next;
               
        }
    }
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
        printf("\nIngrese una opcion entre las posibles: 1-Agregar 2-Eliminar 3-Buscar 4-Imprimir 5-Salir: ");
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
            else
            {
                append(&lista, data);
                data = 0;
                break;
            }

            printf("Valor ingresado con exito");

        case 2:

            printf("Ingrese el valor del nodo a eliminar: ");
            scanf("%d", &data);
            deleteNode(data, &lista);
            printf("Valor eliminado con exito");
            data = 0;
            break;

        case 3:
            printf("Ingrese el valor del nodo para buscar en la lista: ");
            scanf("%d", &data);
            nodeDL *nodoBuscado;
            nodoBuscado = findNode(data, &lista);
            printf("El valor del nodo encontrado: %d ", nodoBuscado->date);
            break;

        case 4:
            printList(&lista);
            break;

        default:
            printf("Muchas gracias por usar este programa! Lo esperamos pronto");
            flag = 1;
        }
    }
}