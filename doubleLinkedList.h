#define UTILIDADES_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "Utilities/utilidades.h"
#define CANT_ESTUDIANTES 10

//////////////////// ESTRUCTURA ///////////////////////
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
    int cantMaterias;

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

char *nombres[] = {"Algebra1", "Algebra2", "AyP1", "AyP2", "AyP3", "Base-Datos", "Historia", "Matematica-Discreta", "Disenio-Logico"};

// Defino una constante para la cantidad de materias para sumar materias nuevas sin modificar el codigo
#define CANT_MATERIAS (sizeof(nombres) / sizeof(nombres[0]))
doubleLinkedList lista = {NULL, NULL, 0};
Materia *materias[CANT_MATERIAS];

//////////////////// FUNCIONES PARA NODE ///////////////////////
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
                printf("Nombre: %s, DNI: %d\n", node->estudiante->nombre, node->estudiante->dni);
            }
            else
            {
                printf("Nombre: %s, DNI: %d\n", node->estudiante->nombre, node->estudiante->dni);
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

            if (node->estudiante->dni == estudiante->dni) // Comparamos el dni del estudiante con el nodo actual
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

//////////////////// FUNCIONES PARA ESTUDIANTE ///////////////////////
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

    return NULL;
}

// Buscar estudiante por DNI
nodeDL *findByDNI(int dni, doubleLinkedList *lista)
{
    nodeDL *node = lista->head;
    if (lista->size > 0)
    {
        while (node != NULL)
        {
            if (node->estudiante->dni == dni)
            {
                return node;
            }

            node = node->next;
        }
    }

    return NULL;
}

// Buscar estudiante por Legajo
nodeDL *findByLegajo(int legajo, doubleLinkedList *lista)
{
    nodeDL *node = lista->head;
    if (lista->size > 0)
    {
        while (node != NULL)
        {
            if (node->estudiante->legajo == legajo)
            {
                return node;
            }

            node = node->next;
        }
    }

    return NULL;
}

void seleccionarEstudiante(nodeDL *nodoEstudiante, doubleLinkedList *lista)
{
    int opc = 0;
    int flag = 0;

    while (flag == 0)
    {
        printf(" \n 1-Anotarse a Materia\n 2-Abandonar Materia\n 3-Rendir Parciales\n 4-Materias anotadas\n 5-Salir\n");
        scanf("%d", &opc);

        switch (opc)
        {
        case 1:
        {
            char nombreMateria[55];
            printf("-Ingrese el nombre de la materia: ");
            scanf("%s", nombreMateria);
            anortarseMateria(nodoEstudiante, nombreMateria, CANT_MATERIAS, materias);

            break;
        }
        case 2:
        {
            char nombre[55];
            printf("-Ingrese el nombre de la materia:");
            scanf("%s", nombre);
            eliminarMateria(nodoEstudiante->estudiante, nombre);

            break;
        }
        case 3:
        {
            char nombre[55];
            printf("-Ingrese el nombre de la materia:");
            scanf("%s", nombre);
            rendirMateria(nodoEstudiante, nombre);

            break;
        }
        case 4:
            mostrarMaterias(nodoEstudiante);

            break;
        case 5:
            flag = 1;
            break;
        default:
            printf("\n-Opcion no encontrada, por favor ingrese otro valor.\n\n");
            break;
        }
    }
}

void cargarEstudiante()
{
    int fechaEsValida = 0;
    Estudiante *estudiante = malloc(sizeof(Estudiante));
    estudiante->cantMaterias = 0;
    if (estudiante == NULL)
    {
        printf("Error al reservar memoria para el estudiante.\n");
        return;
    }

    printf("-Ingrese el nombre del estudiante: ");
    scanf("%s", estudiante->nombre);
    printf("Ingrese la fecha de nacimiento del estudiante (DD/MM/AAAA): ");
    scanf("%s", estudiante->nacimiento);

    fechaEsValida = validarFecha(estudiante->nacimiento);

    if (fechaEsValida == 0)
    {
        printf("Fecha de nacimiento invalida. Por favor, ingrese una fecha en formato DD/MM/AAAA.\n");
        free(estudiante); // libero toda la memoria reservada para el estudiante ya que ingreso mal un dato.
        return;
    }

    printf("Ingrese el DNI del estudiante: ");
    scanf("%d", &estudiante->dni);
    if (estudiante->dni < 10000000 || estudiante->dni > 99999999)
    {
        printf("DNI invalido. Debe tener 8 digitos.\n");
        free(estudiante); // libero toda la memoria reservada para el estudiante ya que ingreso mal un dato.
        return;
    }

    nodeDL *alumno = findByDNI(estudiante->dni, &lista);
    if (alumno != NULL)
    {
                free(estudiante); // libero toda la memoria reservada para el estudiante ya que ingreso mal un dato.

        return;
    }
    printf("Ingrese el Legajo del estudiante: ");
    scanf("%d", &estudiante->legajo);
    nodeDL *alumno2 = findByLegajo(estudiante->legajo, &lista);

    if (alumno2 != NULL)
    {
        printf("Ya existe un estudiante con el mismo Legajo.\n");
        free(estudiante); // libero toda la memoria reservada para el estudiante ya que ingreso mal
        return;
    }
    append(&lista, estudiante);
    printf("\n-Estudiante cargado con exito\n");
}

//////////////////// FUNCIONES PARA MATERIAS ///////////////////////

void cargarMaterias()
{
    for (int i = 0; i < CANT_MATERIAS; i++)
    {
        materias[i] = malloc(sizeof(Materia)); // Reserva memoria para cada materia
        strcpy(materias[i]->nombreMateria, nombres[i]);
        materias[i]->inscripto = 0;
        materias[i]->aprobada = 0;
        materias[i]->firstTest = 0;
        materias[i]->secondTest = 0;
    }
}

// Funcion para buscar materias ingresando un string | Cant de materias | Arreglo de Materia
int findMateria(char nombreMateria[55], int cantMaterias, Materia *materias[])
{
    char nombreMateriaMayus[55];
    // Creo copia de nombre de materia para no afectar la original
    strcpy(nombreMateriaMayus, nombreMateria);
    upperCase(nombreMateriaMayus); // Convierte a mayúsculas la materia ingresada

    char mayusNamePuntero[55];
    for (int i = 0; i < cantMaterias; i++)
    {
        // Copia de nombre materia del array de puntero para no modificar la original
        strcpy(mayusNamePuntero, materias[i]->nombreMateria);
        upperCase(mayusNamePuntero); // Convierte a mayúsculas el nombre de la materia del plan

        if (strcmp(mayusNamePuntero, nombreMateriaMayus) == 0)
        {
            return i; // Devuelve el índice si la encuentra
        }
    }
    printf("No se encontro la materia\n");
    return -1; // No se encontró la materia
}

// Busca en arreglo de structs Materia (para materias del estudiante)
int findMateriaAlumno(char nombreMateria[55], int cantMaterias, Materia materias[])
{
    char nombreMateriaMayus[55];
    strcpy(nombreMateriaMayus, nombreMateria);
    upperCase(nombreMateriaMayus);

    char mayusNamePuntero[55];
    for (int i = 0; i < cantMaterias; i++)
    {
        strcpy(mayusNamePuntero, materias[i].nombreMateria);
        upperCase(mayusNamePuntero);

        if (strcmp(mayusNamePuntero, nombreMateriaMayus) == 0)
        {
            return i;
        }
    }
    printf("No se encontro la materia\n");
    return -1;
}

// Funcion para agregar materia en un alumno ingresando un alumno tipo Estudiante | Una materia tipo Materia
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

// Funcion para eliminar materia de un estudiante ingresando un alumno tipo Estudiante | nombre de la materia
void eliminarMateria(Estudiante *estudiante, char materia[55])
{
    if (estudiante == NULL)
    {
        printf("Error: puntero estudiante es NULL.\n");
        return;
    }

    int indice = -1;
    for (int i = 0; i < estudiante->cantMaterias; i++) // Recorre la cantidad de materias anotadas del alumno
    {
        if (strcmp(estudiante->materias[i].nombreMateria, materia) == 0)
        {
            indice = i; // Guarda el indice de la materia
            break;
        }
    }
    if (indice != -1)
    {
        for (int i = indice; i < estudiante->cantMaterias; i++)
        {
            estudiante->materias[i] = estudiante->materias[i + 1]; // Sobreescribe con la siguiente
        }
        estudiante->cantMaterias--;
        printf("\n-Materia eliminada con exito.\n");
        return;
    }
    else
    {
        printf("\n-Materia no encontrada.\n");
        return;
    }
}

// Funcion para mostrar Materias del plan de estudio
void printMaterias()
{
    printf("\nMaterias del plan de estudio:\n");
    printf("\n-------------------------------\n");

    for (int i = 0; i < CANT_MATERIAS; i++)
    {
        printf("%s\n", materias[i]->nombreMateria);
    }
    printf("\n-------------------------------\n");
}

clearMaterias()
{
    for (int i = 0; i < CANT_MATERIAS; i++)
    {
        free(materias[i]); // Libera la memoria para cada materia
    }
}

// Funcion para mostrar materias de un alumno
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

// Funcion para anotar un alumno a una materia
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

// Funcion para rendir primer parcial ingresando un alumno | Nombre de materia a rendir
void rendirFirst(nodeDL *nodoEstudiante, char materia[55])
{
    int cantMaterias = nodoEstudiante->estudiante->cantMaterias;
    int indice = findMateriaAlumno(materia, cantMaterias, nodoEstudiante->estudiante->materias);

    if (indice != -1)
    {
        float valor = ((float)rand() / RAND_MAX) * 9.0f + 1.0f; // Genera un valor float aleatorio de 1 a 10
        nodoEstudiante->estudiante->materias[indice].firstTest = valor;
        printf("\nAprobaste con: %.1f\n", valor); // Al valor le pedimos que muestre solo 1 decimal
        return;
    }
    else
    {
        printf("\n-Materia no encontrada.\n");
        return;
    }
}

// Funcion para rendir segundo parcial ingresando un alumno | Nombre de materia a rendir
void rendirSecond(nodeDL *nodoEstudiante, char materia[55])
{
    int cantMaterias = nodoEstudiante->estudiante->cantMaterias;
    int indice = findMateriaAlumno(materia, cantMaterias, nodoEstudiante->estudiante->materias);

    if (indice != -1)
    {
        float valor = ((float)rand() / RAND_MAX) * 9.0f + 1.0f; // Genera un valor float aleatorio de 1 a 10
        nodoEstudiante->estudiante->materias[indice].secondTest = valor;
        printf("\nAprobaste con: %.1f\n", valor);
        return;
    }
    else
    {
        printf("\n-Materia no encontrada.\n");
        return;
    }
}

// Funcion para rendir final ingresando un alumno | Nombre de materia a rendir
void rendirFinal(nodeDL *nodoEstudiante, char materia[55])
{
    int cantMaterias = nodoEstudiante->estudiante->cantMaterias;
    int indice = findMateria(materia, cantMaterias, nodoEstudiante->estudiante->materias);

    if (indice != -1)
    {
        float valor = ((float)rand() / RAND_MAX) * 9.0f + 1.0f; // Genera un valor float aleatorio de 1 a 10
        float primerParcial = nodoEstudiante->estudiante->materias[indice].firstTest;
        float segundoParcial = nodoEstudiante->estudiante->materias[indice].secondTest;


        // FUNCION PROMEDIO
        float promedio = (primerParcial + segundoParcial) / 2; // Promedio de primer y segundo parcial

        if (promedio >= 4)
        {

            if (valor >= 4)
            {
                printf("\n-Felicidades Papa, aprobaste con: %1.f\n", valor);
                return;
            }
            else
            {
                printf("\n-Final desaprobado con: %1.f\n", valor);
                return;
            }
        }
        else
        {
            printf("\n-No tenes aprobada la cursada: %1.f\n", valor);
            return;
        }
    }
    else
    {
        printf("\n-Materia no encontrada.\n");
        return;
    }
}

// Funcion para rendir primer,segundo parcial y final ingresando un estudiante | Materia a rendir
void rendirMateria(nodeDL *nodoEstudiante, char materia[55])
{
    int opc = 0;
    int flag = 0;
    printf("\n1-Rendir First\n2-Rendir Second\n3-Rendir Final\n4-Salir\n");
    scanf("%d", &opc);
    while (flag == 0)
    {
        switch (opc)
        {
        case 1:
        {
            rendirFirst(nodoEstudiante, materia);
            flag = 1;
            break;
        }
        case 2:
        {
            rendirSecond(nodoEstudiante, materia);
            flag = 1;
            break;
        }
        case 3:
        {
            rendirFinal(nodoEstudiante, materia);
            flag = 1;
            break;
        }
        case 4:
        {
            flag = 1;
            break;
        }
        default:
            printf("\n-Opcion no encontrada, por favor ingrese otro valor.\n");
            break;
        }
    }
}

// No valida por años biciestos
int validarFecha(char *fecha)
{
    char copia[11];
    strcpy(copia, fecha); // strtok modifica la cadena original, por eso copiamos

    // Usamos strtok como un split( parte basado en un delimitador )
    char *diaStr = strtok(copia, "/");
    char *mesStr = strtok(NULL, "/");
    char *anioStr = strtok(NULL, "/");

    if (diaStr == NULL || mesStr == NULL || anioStr == NULL)
    {
        return 0; // Formato inválido
    }
    // Convertimos las cadenas a enteros
    int dia = atoi(diaStr);
    int mes = atoi(mesStr);
    int anio = atoi(anioStr);

    if (anio < 1900 || anio > 2100)
    {
        return 0; // Año fuera de rango
    }
    if (mes < 1 || mes > 12)
    {
        return 0; // Mes fuera de rango
    }
    if (dia < 1 || dia > 31)
    {
        return 0; // Día fuera de rango
    }

    if ((obtenerAnioActual() - anio) < 18)
    {
        printf("El estudiante debe ser mayor de edad.\n");
        return 0; // El estudiante debe ser mayor de edad
    }
    return 1; // Placeholder, siempre retorna válido
}

int returnAnioEdad(char *fecha){
 char copia[11];
    strcpy(copia, fecha); // strtok modifica la cadena original, por eso copiamos

    // Usamos strtok como un split( parte basado en un delimitador )
    char *diaStr = strtok(copia, "/");
    char *mesStr = strtok(NULL, "/");
    char *anioStr = strtok(NULL, "/");
    int anio = atoi(anioStr);
    return anio; // Retorna el año de la fecha ingresada

}

// Usa libreria time.h para obtener el año actual
int obtenerAnioActual()
{
    time_t t = time(NULL);              // Obtiene el tiempo actual
    struct tm *tm_info = localtime(&t); // Lo convierte a estructura local

    int anio = tm_info->tm_year + 1900; // Año desde 1900 Porque tm_year representa el número de años desde 1900, entonces: se debe sumar 1900

    return anio; // Retorna el año actual
}


// FUNCIONES MATERIAS


void modificarMateria(char nombreMateria[55])
{
    int indice = findMateria(nombreMateria, CANT_MATERIAS, materias);
    if (indice != -1)
    {
        printf("\nIngrese el nuevo nombre de la materia: ");
        char nuevoNombre[55];
        scanf("%s", nuevoNombre);
        strcpy(materias[indice]->nombreMateria, nuevoNombre);
        printf("\nMateria modificada con exito.\n");
    }
    else
    {
        printf("\nMateria no encontrada.\n");
    }
}


