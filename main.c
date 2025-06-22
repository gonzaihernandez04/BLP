#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H
#include "doubleLinkedList.h"

int main()
{
    // Carga la materia de todas las carreras
    cargarMaterias();

    // Inicializa la semilla para la función rand()1
    srand(time(NULL));
    Estudiante *e1 = malloc(sizeof(Estudiante));
    strcpy(e1->nombre, "Ana Gomez");
    strcpy(e1->nacimiento, "15/05/1999");
    e1->dni = 11111111;
    e1->legajo = 1001;
    e1->cantMaterias = 0;

    agregarMateria(e1, materias[0]); // Algebra1
    agregarMateria(e1, materias[1]); // Algebra2
    e1->materias[0].firstTest = 7.5;
    e1->materias[0].secondTest = 8.0;
    e1->materias[0].finalTest = 0;
    e1->materias[0].aprobada = 1;
    e1->materias[1].firstTest = 6.0;
    e1->materias[1].secondTest = 7.0;
    e1->materias[1].finalTest = 0;
    e1->materias[1].aprobada = 1;
    append(&lista, e1);

    // Estudiante 2
    Estudiante *e2 = malloc(sizeof(Estudiante));
    strcpy(e2->nombre, "Bruno Lopez");
    strcpy(e2->nacimiento, "10/10/2000");
    e2->dni = 22222222;
    e2->legajo = 1002;
    e2->cantMaterias = 0;

    agregarMateria(e2, materias[2]); // AyP1
    agregarMateria(e2, materias[3]); // AyP2
    e2->materias[0].firstTest = 8.5;
    e2->materias[0].secondTest = 9.0;
    e2->materias[0].aprobada = 1;
    e2->materias[1].firstTest = 7.0;
    e2->materias[1].secondTest = 8.0;
    e2->materias[1].aprobada = 1;
    append(&lista, e2);

    // Estudiante 3
    Estudiante *e3 = malloc(sizeof(Estudiante));
    strcpy(e3->nombre, "Carla Martinez");
    strcpy(e3->nacimiento, "22/03/1998");
    e3->dni = 33333333;
    e3->legajo = 1003;
    e3->cantMaterias = 0;

    agregarMateria(e3, materias[4]); // AyP3
    agregarMateria(e3, materias[5]); // Base-Datos
    e3->materias[0].firstTest = 6.5;
    e3->materias[0].secondTest = 8.0;
    e3->materias[0].aprobada = 1;
    e3->materias[1].firstTest = 7.0;
    e3->materias[1].secondTest = 9.0;
    e3->materias[1].aprobada = 1;
    append(&lista, e3);

    // Estudiante 4
    Estudiante *e4 = malloc(sizeof(Estudiante));
    strcpy(e4->nombre, "Diego Fernández");
    strcpy(e4->nacimiento, "30/09/1997");
    e4->dni = 44444444;
    e4->legajo = 1004;
    e4->cantMaterias = 0;

    agregarMateria(e4, materias[6]); // Historia
    agregarMateria(e4, materias[7]); // Matematica Discreta
    e4->materias[0].firstTest = 9.0;
    e4->materias[0].secondTest = 9.5;
    e4->materias[0].aprobada = 1;
    e4->materias[1].firstTest = 8.0;
    e4->materias[1].secondTest = 8.5;
    e4->materias[1].aprobada = 1;
    append(&lista, e4);

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
            printf("\n 1- Cargar Estudiante\n 2- Eliminar Estudiante\n 3- Buscar Estudiante\n 4- Imprimir Lista de Estudiantes\n 5- Seleccionar Estudiante \n6- Lista de promedios \n7- Menu\n");
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
                }
                else
                {

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
                    while (i != lista.size)
                    {
                        int anioNacimiento = returnAnioEdad(node->estudiante->nacimiento); // Retorno el año de nacimiento del estudiante en entero
                        int edad = obtenerAnioActual() - anioNacimiento;                   // calculo la edad del estudiante
                        // Verifico si la edad del estudiante esta dentro del rango especificado

                        if (edad >= edadMin && edad <= edadMax)
                        {
                            printf("\n-Estudiante encontrado: Nombre: %s, DNI: %d, Legajo: %d, Edad: %d\n", node->estudiante->nombre, node->estudiante->dni, node->estudiante->legajo, edad);
                        }
                        else
                        {
                            encontrado = 0;
                        }
                        node = node->next;
                        i++;
                    }
                    if (encontrado == 0)
                    {
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

            if (eleccion == 6)
            {
                printf("\n-Lista de promedios de estudiantes:\n");
                printPromedios(&lista);
            }

            break;
        }
        case 2:
        {

            printf("\n1- Modificar Materia \n2- Imprimir Lista de Materias\n3- Volver al menu principal\n");
            scanf("%d", &eleccion);

            if (eleccion == 1)
            {
                char nombreMateria[55];
                printMaterias();
                printf("-Ingrese el nombre de la materia a modificar: ");
                scanf("%s", nombreMateria);

                modificarMateria(nombreMateria);
            }
            if (eleccion == 2)
            {
                printMaterias();
            }
            if (eleccion == 3)
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
