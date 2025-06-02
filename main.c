#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H

#include "doubleLinkedList.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CANT_ESTUDIANTES 10

///  //////////////////////////////// CARGAR MATERIAS //////////////////////////////////////
char *nombres[] = {"Algebra 1", "AyP1", "AyP2", "Base de Datos", "Historia", "AYP3", "Materia Discreta", "Disenio Local"};
// Defino una constante para la cantidad de materias para sumar materias nuevas sin modificar el codigo
#define CANT_MATERIAS (sizeof(nombres) / sizeof(nombres[0]))
doubleLinkedList lista = {NULL, NULL, 0};
Materia *materias[CANT_MATERIAS];

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

//////////////////////////////////////////////////////////////////////

int main()
{

    // Carga la materia de todas las carreras
    cargarMaterias();

    int opc = 0;
    int flag = 0;
    int eleccion = 0;

    while (flag == 0)
    {

        printf("\nQue desea hacer? 1- Estudiantes 2- Materias  3- Salir: \n ");
        scanf("%d", &opc);
        if (opc < 1 || opc > 5)
        {
            printf("Opcion no valida, por favor ingrese un valor entre 1 y 3.\n");
            continue;
        }

        switch (opc)
        {
        case 1:
            eleccion = 0;
            printf("\n1- Cargar Estudiante\n2- Eliminar Estudiante\n3- Buscar Estudiante\n4- Imprimir Lista de Estudiantes\n5- Volver al menu principal\n");
            scanf("%d", &eleccion);

            if (eleccion == 1)
            {
                cargarEstudiante();
            }
            if (eleccion == 4)
            {
                printList(&lista);
            }
            if (eleccion == 3)
            {
                buscarEstudiante();
            }

            break;

        case 2:
            eleccion = 0;
            printf("\n1- Cargar Materia\n2- Modificar Materia \n3- Eliminar Materia\n4- Imprimir Lista de Materias\n5- Volver al menu principal\n");
            scanf("%d", &eleccion);

            if (eleccion == 4)
            {
                printMaterias();
            }
            break;

        case 5:
            opc = 0;
            clear(&lista);   // Limpia la lista de estudiantes al salir del programa
            clearMaterias(); // Limpia las materias de memoria al salir del programaaa
            printf("\nMuchas gracias por usar este programa! Lo esperamos pronto.\n");
            flag = 1;
            break;

        default:
            printf("Opcion no encontrada, por favor ingrese otro valor.\n");
            break;
        }
    }
    return 0;
}

//     // doubleLinkedList lista = {NULL, NULL, 0};
//     int opc = 0;
//     int data;
//     int flag = 0;
//     int inicioFinal;

//     while (flag == 0)
//     {
//         printf("\nIngrese una opcion entre las posibles: 1-Agregar 2-Eliminar 3-Buscar 4-Imprimir 5-Limpiar 6-Salir: ");
//         scanf("%d", &opc);

//     switch (opc)
//         {

//         case 1:

//             printf("Ingrese el valor del nodo: ");
//             scanf("%d", &data);
//             printf("Donde desea agregar? 1- Inicio 2- Final: ");
//             scanf("%d", &inicioFinal);
//             if (inicioFinal == 1)
//             {
//                 prepend(&lista, data);
//                 data = 0;
//                 break;
//             }
//             else if (inicioFinal == 2)
//             {
//                 append(&lista, data);
//                 data = 0;
//                 break;

//         }else{
//             printf("Opcion inexistente.");
//             break;
//         }
//             printf("Valor ingresado con exito.");

//         case 2:

//             printf("Ingrese el valor del nodo a eliminar: ");
//             scanf("%d", &data);
//             deleteNode(data, &lista);
//             data = 0;
//             break;

//         case 3:
//             printf("Ingrese el valor del nodo para buscar en la lista: ");
//             scanf("%d", &data);
//             nodeDL *nodoBuscado;
//             nodoBuscado = findNode(data, &lista);

//             break;

//         case 4:
//             printList(&lista);
//             break;

//         case 5:
//             clear(&lista);
//             break;

//         case 6:
//             printf("Muchas gracias por usar este programa! Lo esperamos pronto.\n");
//             flag = 1;
//             break;

//         default:
//             printf("Opcion no encontrada, por favor ingrese otro valor.\n");
//             break;
//         }
// }

////////////////////// FUNCIONES DE ESTUDIANTES //////////////////////////////////////

////////////////////////CARGAR ESTUDIANTES////////////////////////////////////

void cargarEstudiante()
{
    int fechaEsValida = 0;
    Estudiante *estudiante = malloc(sizeof(Estudiante));
    if (estudiante == NULL)
    {
        printf("Error al reservar memoria para el estudiante.\n");
        return;
    }

    printf("Ingrese el nombre del estudiante: ");
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
    printf("Ingrese el Legajo del estudiante: ");
    scanf("%d", &estudiante->legajo);

    append(&lista, estudiante);
    printf("Estudiante cargado con exito:");
}

void buscarEstudiante()
{

    if (lista.size == 0)
    {
        printf("No hay estudiantes cargados en la lista.\n");
        return;
    }

    char nombreBuscado[45];
    printf("Ingrese el nombre del estudiante a buscar: ");
    scanf("%s", nombreBuscado);
    if (strlen(nombreBuscado) < 3)
    {
        printf("Nombre invalido. Debe tener al menos un caracter.\n");
        return;
    }
    nodeDL *nodoBuscado = findNodeByName(&lista, nombreBuscado);
    if (nodoBuscado == NULL)
    {
        printf("No se encontro el estudiante con el nombre: %s\n", nombreBuscado);
        free(nodoBuscado); // libero la memoria reservada para el nodo
        return;
    }
    printf("El estudiante buscado es: %s\n", nodoBuscado->estudiante->nombre);
}

// funcion para mostrar Materias del plan de estudio

// No valida por años biciestos
int validarFecha(char *fecha)
{
    char copia[11];
    strcpy(copia, fecha); // strtok modifica la cadena original, por eso copiamos

    // Usamos strtok como un split
    char *diaStr = strtok(copia, "/");
    char *mesStr = strtok(NULL, "/");
    char *anioStr = strtok(NULL, "/");

    if (diaStr == NULL || mesStr == NULL || anioStr == NULL ||
        strlen(diaStr) != 2 || strlen(mesStr) != 2 || strlen(anioStr) != 4)
    {
        printf("Fecha invalida. Formato esperado: DD/MM/AAAA.\n");
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

// Usa libreria time.h para obtener el año actual
int obtenerAnioActual()
{
    time_t t = time(NULL);              // Obtiene el tiempo actual
    struct tm *tm_info = localtime(&t); // Lo convierte a estructura local

    int anio = tm_info->tm_year + 1900; // Año desde 1900 Porque tm_year representa el número de años desde 1900, entonces: se debe sumar 1900

    return anio; // Retorna el año actual
}

////////////////////// FUNCIONES DE ESTUDIANTES //////////////////////////////////////

// FUNCIONES DE MATERIAS /////

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

#endif;
