#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H

#include "doubleLinkedList.h"

#include <stdio.h>
#include <stdlib.h>

int main()
{
    // Carga la materia de todas las carreras
    cargarMaterias();
    // Inicializa la semilla para la función rand()1
    srand(time(NULL));

    Estudiante *estudiante = malloc(sizeof(Estudiante));
    estudiante->cantMaterias = 0;
    strcpy(estudiante->nombre, "Juan Perez");
    strcpy(estudiante->nacimiento, "01/01/2000");
    estudiante->dni = 12345678;
    estudiante->legajo = 1234;
    append(&lista, estudiante); // Agrega un estudiante de prueba a la lista

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
            printf("\n 1- Cargar Estudiante\n 2- Eliminar Estudiante\n 3- Buscar Estudiante\n 4- Imprimir Lista de Estudiantes\n 5- Seleccionar Estudiante\n 6- Menu\n");
            scanf("%d", &eleccion);

            if (eleccion == 1)
            {
                cargarEstudiante();
            }
            if (eleccion == 2)
            {
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
                printf("\n- Desea buscar por: 1- Nombre 2- Rango de edad");
                scanf("%d", &eleccion);

                if (eleccion == 1)
                {
                    char estudiante[55];
                    printf("-Ingrese el nombre del estudiante: ");
                    scanf("%s", estudiante); // No uso &, porque estudiante ya es un puntero al primer elemento
                    nodeDL *alumno = findEstudiante(estudiante, &lista);
                    if (alumno != NULL)
                    {
                        printf("\n-Estudiante encontrado: %s, DNI: %d, Legajo: %d\n", alumno->estudiante->nombre, alumno->estudiante->dni, alumno->estudiante->legajo);
                    }
                    else
                    {
                        printf("\n-Estudiante no encontrado.\n");
                    }
                }else{

                    if (lista.size == 0)
                    {
                        printf("\n-No hay estudiantes cargados.\n");
                        return;
                    }
                    int edadMin, edadMax;
                    printf("-Ingrese la edad minima: ");
                    scanf("%d", &edadMin);
                    printf("-Ingrese la edad maxima: ");
                    scanf("%d", &edadMax);

                    nodeDL *node = lista.head;
                    int encontrado = 1;
                    

                    int i = 0;
                    printf("Listado de alumnos encontrados entre %d y %d anios:\n", edadMin, edadMax);
                    while(i != lista.size){
                        int anioNacimiento = returnAnioEdad(node->estudiante->nacimiento); // Retorno el año de nacimiento del estudiante en entero
                       int edad = obtenerAnioActual() - anioNacimiento; // calculo la edad del estudiante
                        // Verifico si la edad del estudiante esta dentro del rango especificado

                        if (edad >= edadMin && edad <= edadMax)
                        {
                            printf("\n-Estudiante encontrado: Nombre: %s, DNI: %d, Legajo: %d, Edad: %d\n", node->estudiante->nombre, node->estudiante->dni, node->estudiante->legajo, edad);
                        }else{
                            encontrado =0 ;
                        }
                        node = node->next;
                        i++;

                        
                    }
                    if(encontrado == 0){
                        printf("\n-No se encontraron estudiantes en el rango de edad especificado.\n");
                    }
                   
                }
            }

            if (eleccion == 5)
            {
                int legajo;
                printf("-Ingrese el legajo del estudiante: ");
                scanf("%d", &legajo); // No uso &, porque estudiante ya es un puntero al primer elemento
                nodeDL *alumno = findByLegajo(legajo, &lista);

                if (alumno != NULL)
                {
                    printf("\nUsted va a afectar al siguiente estudiante: Nombre: %s, DNI: %d, Legajo: %d\n", alumno->estudiante->nombre, alumno->estudiante->dni, alumno->estudiante->legajo);
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

            if (eleccion == 2)
            {
                char nombreMateria[55];
                printMaterias();
                printf("-Ingrese el nombre de la materia a modificar: ");
                scanf("%s", nombreMateria);

                modificarMateria(nombreMateria);
            }
            if (eleccion == 4)
            {
                printMaterias();
            }
            if (eleccion == 5)
            {
                opc = 0; // Vuelve al menu principal
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

#endif
