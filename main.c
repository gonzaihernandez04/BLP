#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H
#include "doubleLinkedList.h"

int main()
{
    materias = malloc(cantidadMaterias * sizeof(Materia)); // guardo arreglo de structs. Debo usar . y no flecha

    // Carga la materia de todas las carreras
    cargarMaterias(materias);
    cargarEstudiantesPrueba(materias); // Carga estudiantes de prueba
    inicializarFuncionRand();          // Inicializa la semilla para rand()

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
                int opc = 0;
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                printf("\nCargar Estudiante");
                printf("\n-----------------\n");
                SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);

                printf("1- Cargar individualmente\n");
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

                printf("2- Cargar masivamente\n");
                SetConsoleTextAttribute(hConsole, saved_attributes);

                opc = getch() - '0';
                if (opc == 1)
                {
                    cargarEstudiante();
                }
                else
                {
                    printf("Ingrese un numero de estudiantes a cargar: ");
                    int cantidad;
                    scanf("%d", &cantidad);
                    if (cantidad <= 0)
                    {
                        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
                        printf("\n-Cantidad invalida. Debe ser mayor a 0.\n");
                        SetConsoleTextAttribute(hConsole, saved_attributes);
                        continue;
                    }
                    cargarEstudiantesPruebaMasivo(cantidad);
                }
            }
            if (eleccion == 2)
            {
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);

                printf("\nEliminar estudiantes\n");
                printf("--------------------\n");
                SetConsoleTextAttribute(hConsole, saved_attributes);
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
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                printf("---------------------\n");
                printf("\nDesea buscar por:\n 1- NOMBRE y APELLIDO\n 2- RANGO DE EDAD\n");
                SetConsoleTextAttribute(hConsole, saved_attributes);
                eleccion = getch() - '0';
                if (eleccion == 1)
                {
                    char nombre[55];
                    char apellido[55];
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                    printf("Ingrese el apellido del estudiante: ");
                    scanf("%s", apellido); // No uso &, porque estudiante ya es un puntero al primer elemento
                    printf("Ingrese el nombre del estudiante: ");
                    scanf("%s", nombre); // No uso &, porque estudiante ya es un puntero al primer elemento

                    doubleLinkedList listaEncontradosNombre = {0}; // Inicializa la lista vacía
                    findEstudiante(nombre, apellido, &listaEncontradosNombre, &lista);
                    if (listaEncontradosNombre.size > 0)
                    {
                        nodeDL *node = listaEncontradosNombre.head;
                        int i = 0;
                        while (i < listaEncontradosNombre.size)
                        {
                            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                            printf("\n-Estudiante encontrado: Nombre: %s, Apellido: %s, DNI: %d, Legajo: %d\n", node->estudiante->nombre, node->estudiante->apellido, node->estudiante->dni, node->estudiante->legajo);
                            SetConsoleTextAttribute(hConsole, saved_attributes);
                            node = node->next;
                            i++;
                        }
                        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                        printf("\n1- Seleccionar estudiante(Ingrese el legajo dentro de los estudiantes mostrados)\n");
                        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                        printf("\n2- Volver al menu principal\n");
                        int opc;
                        opc = getch() - '0';
                        if (opc == 1)
                        {
                            seleccionarEstudiante(&lista);
                        }
                        else
                        {
                            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
                            printf("\n-Volviendo al menu principal...\n");
                            SetConsoleTextAttribute(hConsole, saved_attributes);
                            continue;
                        }
                        clear(&listaEncontradosNombre); // Limpio la lista de estudiantes encontrados
                    }
                    else
                    {
                        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                        printf("\n-Estudiante no encontrado.\n");
                    }
                }
                else
                {

                    if (lista.size == 0)
                    {
                        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
                        printf("\n-No hay estudiantes cargados.\n");
                        SetConsoleTextAttribute(hConsole, saved_attributes);
                    }
                    doubleLinkedList listaEncontradosEdad = {0};

                    int edadMin, edadMax;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                    printf("-Ingrese la edad minima: ");
                    scanf("%d", &edadMin);
                    printf("-Ingrese la edad maxima: ");
                    scanf("%d", &edadMax);

                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                    printf("\nListado de alumnos encontrados entre %d y %d anios:\n", edadMin, edadMax);
                    printf("\n----------------------------------------------------------------------------------\n");
                    SetConsoleTextAttribute(hConsole, saved_attributes);

                    findByRange(edadMin, edadMax, &listaEncontradosEdad);

                    if (listaEncontradosEdad.size > 0)
                    {
                        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                        printf("\n1- Seleccionar estudiante(Ingrese el legajo dentro de los estudiantes mostrados)\n");
                        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                        printf("\n2- Volver al menu principal\n");
                        int opc;
                        opc = getch() - '0';
                        if (opc == 1)
                        {
                            seleccionarEstudiante(&lista);
                        }
                        else
                        {
                            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
                            printf("\n-Volviendo al menu principal...\n");
                            SetConsoleTextAttribute(hConsole, saved_attributes);
                            continue;
                        }
                    }

                    clear(&listaEncontradosEdad);
                }
            }

            if (eleccion == 4)
            {
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

                printf("\nLISTA DE ESTUDIANTES\n");

                printf("-------------------------\n");
                SetConsoleTextAttribute(hConsole, saved_attributes);
                printList(&lista);
            }

            if (eleccion == 5)
            {
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
               

                seleccionarEstudiante(&lista);
                
                SetConsoleTextAttribute(hConsole, saved_attributes);
            }

            if (eleccion == 6)
            {
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                printf("\n-Lista de promedios de estudiantes:\n");
                SetConsoleTextAttribute(hConsole, saved_attributes);
                printPromedios(&lista);
            }

            break;
        }
        case 2:
        {
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            printf("\nElija una opcion\n");
            printf("------------------\n");
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            printf(" 1- Modificar Materia\n");
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            printf(" 2- Imprimir Lista de Materias\n");
            SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            printf(" 3- Agregar Materia\n");
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
            printf(" 4- Eliminar Materia\n");
            SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            printf(" 5- Salir\n");
            SetConsoleTextAttribute(hConsole, saved_attributes);
            eleccion = getch() - '0';

            if (eleccion == 1)
            {
                char nombreMateria[55];
                printMaterias(materias);

                
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                printf("\n-Ingrese el nombre de la materia a modificar(Sin espacios): ");
                scanf("%s", nombreMateria);
                printf("\nIngrese el nuevo nombre de la materia(Sin espacios): ");
                SetConsoleTextAttribute(hConsole, saved_attributes);
                char nuevoNombre[55];
                scanf("%s", nuevoNombre);
                modificarMateria(nombreMateria, nuevoNombre, materias);
            }
            if (eleccion == 2)
            {
                printMaterias(materias);
                
            }
            if (eleccion == 3)
            {
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                printf("\nAgregar Materia\n");
                printf("----------------\n");
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

                printf("\n1- Cargar Materia individualemente");
                SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);

                printf("\n2- Cargar Materia masivamente\n");
                SetConsoleTextAttribute(hConsole, saved_attributes);
                opc = getch() - '0';
                if (opc == 1)
                {
                    char nombreMateriaNueva[55];

                    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                    printf("\nIngrese el nombre de la nueva materia(Sin espacios): ");
                    scanf("%s", nombreMateriaNueva);
                    materias = realloc(materias, (cantidadMaterias + 1) * sizeof(Materia));
                    strcpy(materias[cantidadMaterias].nombreMateria, nombreMateriaNueva);

                    materias[cantidadMaterias].inscripto = 0;
                    materias[cantidadMaterias].aprobada = 0;
                    materias[cantidadMaterias].firstTest = 0;
                    materias[cantidadMaterias].secondTest = 0;
                    materias[cantidadMaterias].finalTest = 0;
                    cantidadMaterias++;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                    printf("\nMATERIA AGREGADA CON EXITO\n");
                }
                else
                {
                    int cant = 0;
                    printf("Ingrese una cantidad de materias a cargar: ");
                    scanf("%d", &cant);
                    if (cant <= 0)
                    {
                        printf("\n-Cantidad invalida. Debe ser mayor a 0.\n");
                        continue;
                    }
                    cargarMateriasMasivo(cant);
                }
            }

            if (eleccion == 4)
            {
                printf("\nEliminar Materia\n");
                printf("----------------\n");
                char nombreMateria[55];
                printf("\nIngrese el nombre de la materia a eliminar(Sin espacios): ");
                scanf("%s", nombreMateria);
                eliminarMateriaAlumno(nombreMateria); // Elimina la materia de los alumnos
            }

            if (eleccion == 5)
            {
                opc = 0; // Vuelve al menu principal
            }
            break;
        }

        case 3:
            opc = 0;
            clear(&lista);           // Limpia la lista de estudiantes al salir del programa
            clearMaterias(materias); // Limpia las materias de memoria al salir del programaaa
            SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            printf("\nMuchas gracias por usar este programa! Lo esperamos pronto.\n");

            flag = 1;
            break;

        default:
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
            printf("\n-Opcion no encontrada, por favor ingrese otro valor.\n\n");
            break;
        }
        SetConsoleTextAttribute(hConsole, saved_attributes);
    }
    return 0;
}

#endif
