#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H
#include "doubleLinkedList.h"

int main()
{

    // Carga la materia de todas las carreras
    cargarMaterias();
    cargarEstudiantesPrueba(); // Carga estudiantes de prueba
    inicializarFuncionRand();  // Inicializa la semilla para rand()
    HANDLE hConsole = cargarSetWindowsAPI();
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);

    printf("\nBIENVENIDO AL SISTEMA DE GESTION DE ESTUDIANTES Y MATERIAS\n");
    SetConsoleTextAttribute(hConsole, saved_attributes);

    printf("\n-----------------------------------------------------------\n");
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("\nESPERE UN MOMENTO POR FAVOR...\n\n");
    printf("\n-----------------------------------------------------------\n");
    SetConsoleTextAttribute(hConsole, saved_attributes);

    Sleep(2000); // Espera 2000 milisegundos = 2 segundos

    char opc;
    int flag = 0;
    char eleccion;
    while (flag == 0)
    {

        printf("\nElija una opcion\n");
        printf("------------------\n");
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        printf(" 1- Gestion de estudiantes\n");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        printf(" 2- Gestion de materias\n");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf(" 3- Salir del programa\n");
        SetConsoleTextAttribute(hConsole, saved_attributes);

        opc = getch() - '0';

        switch (opc)
        {

        case 1:
        {
            printf("\nGestion de estudiantes\n");
            printf("----------------------\n");
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            printf(" 1- Cargar Estudiante\n");

            // Opción 2 - Rojo brillante
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
            printf(" 2- Eliminar Estudiante\n");

            // Opción 3 - Azul brillante
            SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            printf(" 3- Buscar Estudiante\n");

            // Opción 4 - Amarillo brillante (rojo + verde)
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            printf(" 4- Imprimir Lista de Estudiantes\n");

            // Opción 5 - Cian brillante (verde + azul)
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            printf(" 5- Seleccionar Estudiante\n");

            // Opción 6 - Magenta brillante (rojo + azul)
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            printf(" 6- Lista de promedios\n");

            // Opción 7 - Blanco brillante
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            printf(" 7- Menu\n");

            // Restaurar el color original
            SetConsoleTextAttribute(hConsole, saved_attributes);
            eleccion = getch() - '0';

            if (eleccion == 1)
            {
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                printf("\nCargar Estudiante");
                SetConsoleTextAttribute(hConsole, saved_attributes);

                printf("\n-----------------\n");
                cargarEstudiante();
            }
            if (eleccion == 2)
            {
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);

                printf("\nEliminar estudiantes\n");
                SetConsoleTextAttribute(hConsole, saved_attributes);

                printf("--------------------\n");
                int dni;
                printf("Ingrese el DNI del estudiante: ");
                scanf("%d", &dni); // No uso &, porque estudiante ya es un puntero al primer elemento
                nodeDL *alumno = findByDNI(dni, &lista);
                if (alumno != NULL)
                {
                    deleteNode(alumno->estudiante, &lista);
                }
            }

            if (eleccion == 3)
            {
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

                printf("\nBuscar estudiantes\n");
                SetConsoleTextAttribute(hConsole, saved_attributes);
                printf("---------------------\n");
                printf("\nDesea buscar por:\n 1- NOMBRE\n 2- RANGO DE EDAD\n");
                eleccion = getch() - '0';

                if (eleccion == 1)
                {
                    char estudiante[55];
                    printf("Ingrese el nombre del estudiante: ");
                    scanf("%s", estudiante); // No uso &, porque estudiante ya es un puntero al primer elemento

                    doubleLinkedList *listaEncontradosNombre;
                    nodeDL *alumno = findEstudiante(estudiante, &lista);
                    if (alumno != NULL)
                    {
                        printf("\n-Estudiante encontrado: %s, DNI: %d, Legajo: %d\n", alumno->estudiante->nombre, alumno->estudiante->dni, alumno->estudiante->legajo);
                        append(&listaEncontradosNombre, alumno->estudiante); // Agrego el estudiante encontrado a la lista de encontrados
                    }
                    else
                    {
                        printf("\n-Estudiante no encontrado.\n");
                    }
                }
                else
                { // TODO ESTO SE CAMBIO

                    if (lista.size == 0)
                    {
                        printf("\n-No hay estudiantes cargados.\n");
                        return;
                    }
                    doubleLinkedList *listaEncontradosEdad;

                    int edadMin, edadMax;
                    printf("-Ingrese la edad minima: ");
                    scanf("%d", &edadMin);
                    printf("-Ingrese la edad maxima: ");
                    scanf("%d", &edadMax);


                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                    printf("\nListado de alumnos encontrados entre %d y %d anios:\n", edadMin, edadMax);
                    SetConsoleTextAttribute(hConsole, saved_attributes);

                    printf("\n----------------------------------------------------------------------------------\n");


                    findByRange(edadMin, edadMax, &listaEncontradosEdad);
                    clear(&listaEncontradosEdad);

                }
            }

            if (eleccion == 4)
            {
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

                printf("\nLISTA DE ESTUDIANTES\n");
                SetConsoleTextAttribute(hConsole, saved_attributes);
                printf("-------------------------\n");
                printList(&lista);
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

            if (eleccion == 6)
            {
                printf("\n-Lista de promedios de estudiantes:\n");
                printPromedios(&lista);
            }

            break;
        }
        case 2:
        {
            printf("\nElija una opcion\n");
            printf("------------------\n");
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            printf(" 1- Modificar Materia\n");
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            printf(" 2- Imprimir Lista de Materias\n");
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
            printf(" 3- Volver al menu principal\n");
            SetConsoleTextAttribute(hConsole, saved_attributes);

            eleccion = getch() - '0';

            if (eleccion == 1)
            {
                char nombreMateria[55];
                printMaterias();
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                printf("\n-Ingrese el nombre de la materia a modificar: ");
                scanf("%s", nombreMateria);
                SetConsoleTextAttribute(hConsole, saved_attributes);
                printf("\nIngrese el nuevo nombre de la materia: ");
                char nuevoNombre[55];
                scanf("%s", nuevoNombre);
                modificarMateria(nombreMateria, nuevoNombre);
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
