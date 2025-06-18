#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H

#include "doubleLinkedList.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CANT_ESTUDIANTES 10

///  //////////////////////////////// CARGAR MATERIAS //////////////////////////////////////
char *nombres[] = {"Algebra1", "Algebra2", "AyP1", "AyP2", "AyP3", "Base-Datos", "Historia", "Matematica-Discreta", "Disenio-Logico"};

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
        switch (opc)
        {

        case 1:
        {
            printf("\n 1- Cargar Estudiante\n 2- Eliminar Estudiante\n 3- Buscar Estudiante\n 4- Imprimir Lista de Estudiantes\n 5- Inscribir a materia\n 6- Menu\n");
            scanf("%d", &eleccion);

            if (eleccion == 1)
            {
                cargarEstudiante();
            }
            if(eleccion == 2){
                int dni;
                printf("-Ingrese el DNI del estudiante: ");
                scanf("%d", &dni); // No uso &, porque estudiante ya es un puntero al primer elemento
                nodeDL *alumno = findByDNI(dni, &lista);
                if (alumno != NULL)
                {
                    deleteNode(alumno->estudiante, &lista);
                }
            }


              if (eleccion == 3)
            {
                char estudiante[55];
                printf("-Ingrese el nombre del estudiante: ");
                scanf("%s", estudiante); // No uso &, porque estudiante ya es un puntero al primer elemento
                nodeDL *alumno = findEstudiante(estudiante, &lista);
                if (alumno != NULL)
                {
                    seleccionarEstudiante(alumno, &lista);
                }
             
            }

            if (eleccion == 4)
            {
                printList(&lista);
            }
          

            break;
        }
        case 2:
        {

            printf("\n1- Cargar Materia\n2- Modificar Materia \n3- Eliminar Materia\n4- Imprimir Lista de Materias\n5- Volver al menu principal\n");
            scanf("%d", &eleccion);
            
            if(eleccion == 1){
                printf("Carga materias");
            }
            if(eleccion == 2)
            {
                printf("Modificar materias");
            }
            if(eleccion == 3){
                printf("Eliminar materias");
            }
            if (eleccion == 4)
            {
                printMaterias();
            }
            break;
        }
     

        

        case 3:
          opc = 0;
            clear(&lista);   // Limpia la lista de estudiantes al salir del programa
            clearMaterias(); // Limpia las materias de memoria al salir del programaaa
            printf("\nMuchas gracias por usar este programa! Lo esperamos pronto.\n");
            flag = 1;
            break;

          

        default:
            printf("\n-Opcion no encontrada, por favor ingrese otro valor.\n\n");
            break;
        }
    }
    return 0;
}

// Funcion para cargar un estudiante
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
        return;
    }
    printf("Ingrese el Legajo del estudiante: ");
    scanf("%d", &estudiante->legajo);

    append(&lista, estudiante);
    printf("\n-Estudiante cargado con exito\n");
}

////////////////////////////////////////////////////////////////////

// funcion para mostrar Materias del plan de estudio
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

// No valida por años biciestos
int validarFecha(char *fecha)
{
    char copia[11];
    strcpy(copia, fecha); // strtok modifica la cadena original, por eso copiamos

    // Usamos strtok como un split
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

// Usa libreria time.h para obtener el año actual
int obtenerAnioActual()
{
    time_t t = time(NULL);              // Obtiene el tiempo actual
    struct tm *tm_info = localtime(&t); // Lo convierte a estructura local

    int anio = tm_info->tm_year + 1900; // Año desde 1900 Porque tm_year representa el número de años desde 1900, entonces: se debe sumar 1900

    return anio; // Retorna el año actual
}

// Seleccion de estudiante
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
            break;

        case 4:
            mostrarMaterias(nodoEstudiante);
            break;
        case 5:
            opc = 0;
            flag = 1;
            break;
        default:
            printf("\n-Opcion no encontrada, por favor ingrese otro valor.\n\n");
            break;
        }
    }
}

#endif
