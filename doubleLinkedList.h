#define UTILIDADES_H
#define STRUCTS_H
#include "Utilities/utilidades.h"
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

//////////////////// FUNCIONES PARA NODE y LISTA ///////////////////////
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
    int contPaginado = 0;
    int pagina = 1;
    int continuar = 1;
    nodeDL *node = lista->head;
    if (node != NULL)
    {
        printf("\nPAGINA %d\n", pagina);

        while (node != NULL) // Mientras el nodo no sea nulo y continuar sea 1
        {

            if (node != NULL)
            {
                printf("Nombre y apellido: %s %s, DNI: %d, Legajo: %d\n", node->estudiante->nombre, node->estudiante->apellido, node->estudiante->dni, node->estudiante->legajo);

                contPaginado++;

                if (contPaginado % determinarModulo(lista) == 0) // Determino la cantidad segun tamaño de la lista
                {
                    printf("\nPresione cualquier tecla para continuar...\n");
                    getch();
                    contPaginado = 0; // Reinicia el contador de paginado
                    pagina++;
                    printf("\nPAGINA %d\n", pagina);
                }
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

////////////////////////////////////////////////////////////////////////////////////

//////////////////// FUNCIONES PARA ESTUDIANTE ///////////////////////
doubleLinkedList *findEstudiante(char nombre[55], char apellido[55], doubleLinkedList *listaEncontrados, doubleLinkedList *lista)
{
    nodeDL *node = lista->head;
    if (lista->size > 0)
    {
        while (node != NULL)
        {
            if ((strcmp(node->estudiante->nombre, nombre) == 0) && (strcmp(node->estudiante->apellido, apellido) == 0))
            {
                append(listaEncontrados, node->estudiante);
            }
            node = node->next;
        }
        return listaEncontrados;
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

void seleccionarEstudiante(doubleLinkedList *lista)
{
    int opc = 0;
    int flag = 0;

    int legajo;
    HANDLE hConsole = cargarSetWindowsAPI();
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("-Ingrese el legajo del estudiante: ");
    scanf("%d", &legajo); // No uso &, porque estudiante ya es un puntero al primer elemento
    nodeDL *alumno = findByLegajo(legajo, &lista);

    if (alumno != NULL)
    {
        printf("\nUsted va a afectar al siguiente estudiante: Nombre: %s, DNI: %d, Legajo: %d\n", alumno->estudiante->nombre, alumno->estudiante->dni, alumno->estudiante->legajo);
    }

    while (flag == 0)
    {
        HANDLE hConsole = cargarSetWindowsAPI();
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        printf("\nElija una opcion\n");
        printf("------------------\n");
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        printf(" 1-Anotarse a una Materia\n");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf(" 2-Abandonar Materia\n");
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        printf(" 3-Rendir Parciales\n");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        printf(" 4-Modificar alumno\n");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        printf(" 5-Materias anotadas\n");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf(" 6-Salir\n");
        SetConsoleTextAttribute(hConsole, saved_attributes);

        opc = getch() - '0';
        switch (opc)
        {
        case 1:
        {
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
            printf(" \nAnotarse a una Materia\n");
            printf("----------------------\n");
            char nombreMateria[55];
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            printf("-Ingrese el nombre de la materia: ");
            scanf("%s", nombreMateria);
            anotarseMateria(alumno, nombreMateria, CANT_MATERIAS, materias);
            SetConsoleTextAttribute(hConsole, saved_attributes);
            break;
        }
        case 2:
        {
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            printf("\nAbandonar una Materia\n");
            printf("----------------------\n");
            char nombre[55];
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            printf("-Ingrese el nombre de la materia:");
            scanf("%s", nombre);
            eliminarMateria(alumno->estudiante, nombre);
            SetConsoleTextAttribute(hConsole, saved_attributes);
            break;
        }
        case 3:
        {
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
            printf("\nRendir Parciales\n");
            printf("----------------------\n");
            char nombre[55];
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            printf("-Ingrese el nombre de la materia:");
            scanf("%s", nombre);
            rendirMateria(alumno, nombre);
            SetConsoleTextAttribute(hConsole, saved_attributes);
            break;
        }
        case 4:
        {
            SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            printf("\nModificar alumno\n");
            printf("----------------------\n");
            modificarAlumno(alumno);
            SetConsoleTextAttribute(hConsole, saved_attributes);
            break;
        }

        case 5:
        {
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            printf("\nMaterias anotadas\n");
            printf("----------------------\n");
            mostrarMaterias(alumno);
            SetConsoleTextAttribute(hConsole, saved_attributes);
            break;
        }

        case 6:
        {
            flag = 1;
            break;
        }
        default:
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            printf("\n-Opcion no encontrada, por favor ingrese otro valor.\n\n");
            SetConsoleTextAttribute(hConsole, saved_attributes);
            break;
        }
    }
}

void modificarAlumno(nodeDL *alumno)
{
    HANDLE hConsole = cargarSetWindowsAPI();
    int opc = 0;
    if (alumno != NULL)
    {

        printf("\nElija una opcion\n");
        printf("------------------\n");
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        printf(" 1- Modificar Nombre\n");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        printf(" 2- Modificar DNI\n");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf(" 3- Modificar Legajo\n");
        SetConsoleTextAttribute(hConsole, saved_attributes);
        opc = getch() - '0';
        switch (opc)
        {
        case 1:
        {
            char nuevoNombre[55];
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            printf("\nIngrese el nuevo nombre: ");
            SetConsoleTextAttribute(hConsole, saved_attributes);
            scanf("%s", &nuevoNombre);
            strcpy(alumno->estudiante->nombre, nuevoNombre);
            break;
        }
        case 2:
        {
            int nuevoDNI;
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            printf(" Ingrese el nuevo DNI: \n");
            SetConsoleTextAttribute(hConsole, saved_attributes);
            scanf("%d", &nuevoDNI);
            alumno->estudiante->dni = nuevoDNI;
            break;
        }
        case 3:
        {
            int nuevoLegajo;
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            printf(" Ingrese el nuevo legajo: \n");
            SetConsoleTextAttribute(hConsole, saved_attributes);
            scanf("%d", &nuevoLegajo);
            alumno->estudiante->legajo = nuevoLegajo;
            break;
        }
        default:
        {
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            printf("Opcion invalida");
            SetConsoleTextAttribute(hConsole, saved_attributes);
            break;
        }
        }
    }
    else
    {
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        printf("\nAlumno no encontrado.\n");
        SetConsoleTextAttribute(hConsole, saved_attributes);
    }
}

void cargarEstudiante()
{
    HANDLE hConsole = cargarSetWindowsAPI();
    int fechaEsValida = 0;
    Estudiante *estudiante = malloc(sizeof(Estudiante));
    estudiante->cantMaterias = 0;
    if (estudiante == NULL)
    {
        printf("Error al reservar memoria para el estudiante.\n");
        return;
    }
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("Ingrese el apellido del estudiante: ");
    scanf("%s", estudiante->apellido);
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

    nodeDL *alumno = findByDNI(estudiante->dni, &lista);
    if (alumno != NULL)
    {
        free(estudiante); // libero toda la memoria reservada para el estudiante ya que ingreso mal un dato.

        return;
    }
    printf("Ingrese el Legajo del estudiante: ");
    scanf("%d", &estudiante->legajo);
    nodeDL *alumno2 = findByLegajo(estudiante->legajo, &lista);

    if (alumno != NULL)
    {

        printf("Ya existe un estudiante con el mismo Legajo.\n");
        free(estudiante); // libero toda la memoria reservada para el estudiante ya que ingreso mal
        return;
    }
    append(&lista, estudiante);
    printf("\nEspere por favor...\n");
    Sleep(500); // Espera 1000 milisegundos = 1 segundo
    printf("\nEstudiante cargado con exito\n");
    SetConsoleTextAttribute(hConsole, saved_attributes);
}

//////////////////// FUNCIONES PARA MATERIAS ///////////////////////

// Funcion para buscar materias ingresando un string | Cant de materias | Arreglo de Materia
int findMateria(char nombreMateria[55], int cantMaterias, Materia materias[])
{
    HANDLE hConsole = cargarSetWindowsAPI();
    char nombreMateriaMayus[55];
    // Creo copia de nombre de materia para no afectar la original
    strcpy(nombreMateriaMayus, nombreMateria);
    upperCase(nombreMateriaMayus); // Convierte a mayúsculas la materia ingresada

    char mayusNamePuntero[55];
    for (int i = 0; i < cantMaterias; i++)
    {
        // Copia de nombre materia del array de puntero para no modificar la original
        strcpy(mayusNamePuntero, materias[i].nombreMateria);
        upperCase(mayusNamePuntero); // Convierte a mayúsculas el nombre de la materia del plan
        if (strcmp(mayusNamePuntero, nombreMateriaMayus) == 0)
        {
            return i; // Devuelve el índice si la encuentra
        }
    }
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("No se encontro la materia\n");
    SetConsoleTextAttribute(hConsole, saved_attributes);
    return -1; // No se encontró la materia
}

// Busca en arreglo de structs Materia (para materias del estudiante)
int findMateriaAlumno(char nombreMateria[55], int cantMaterias, Materia materias[])
{
    HANDLE hConsole = cargarSetWindowsAPI();
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
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("No se encontro la materia\n");
    SetConsoleTextAttribute(hConsole, saved_attributes);
    return -1;
}

// Funcion para agregar materia en un alumno ingresando un alumno tipo Estudiante | Una materia tipo Materia
void agregarMateria(Estudiante *estudiante, Materia materia)
{
    HANDLE hConsole = cargarSetWindowsAPI();
    if (estudiante->cantMaterias < 48)
    {
        estudiante->materias[estudiante->cantMaterias] = materia;
        estudiante->cantMaterias++;
    }
    else
    {
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        printf("No se pueden agregar más materias.\n");
        SetConsoleTextAttribute(hConsole, saved_attributes);
    }
}

// Funcion para mostrar Materias del plan de estudio
void printMaterias(Materia materias[])
{
    int pagina = 1;
    int contadorMaterias = 0;
    HANDLE hConsole = cargarSetWindowsAPI();
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("\nMaterias del plan de estudio:\n");
    printf("\n-------------------------------\n");
    SetConsoleTextAttribute(hConsole, saved_attributes);

    printf("Pagina %d\n", pagina);
    for (int i = 0; i < cantidadMaterias; i++)
    {
        printf("%d. %s\n", i + 1, materias[i].nombreMateria);
        contadorMaterias++;
        if (contadorMaterias % determinarModuloMateria(cantidadMaterias) == 0)
        {
            printf("\nPresione cualquier tecla para continuar...\n");
            getch();
            pagina++;
            printf("\nPagina %d\n", pagina);
            contadorMaterias = 0; // Reinicia el contador de materias
        }
    }
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("\n-------------------------------\n");
    SetConsoleTextAttribute(hConsole, saved_attributes);
}

clearMaterias(Materia *materias[])
{
    free(materias);
}

// Funcion para mostrar materias de un alumno
void mostrarMaterias(nodeDL *nodoEstudiante)
{
    for (int i = 0; i < nodoEstudiante->estudiante->cantMaterias; i++)
    {
        if (i == 0)
        {
            printf("\n[%s]->", nodoEstudiante->estudiante->materias[i].nombreMateria);
        }
        else if (i > 0 && i < nodoEstudiante->estudiante->cantMaterias - 1)
        {
            printf("[%s]->", nodoEstudiante->estudiante->materias[i].nombreMateria);
        }
        else
        {
            printf("[%s]\n", nodoEstudiante->estudiante->materias[i].nombreMateria);
        }
    }
}

// Funcion para anotar un alumno a una materia
void anotarseMateria(nodeDL *nodoEstudiante, char nombreMateria[55], int cantMaterias, Materia materias[])
{
    HANDLE hConsole = cargarSetWindowsAPI();
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
                    nodoEstudiante->estudiante->materias[i].inscripto = 1; // Marca como inscripto
                }
                else
                {
                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                    printf("Ya estás anotado en esa materia.\n");
                }
                return; // Salir después de encontrar la materia
            }
        }
        // Si no está anotado, agregar la materia

        agregarMateria(nodoEstudiante->estudiante, materias[encontrado]);
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        printf("\n-Materia agregada con éxito.\n");
    }
    else
    {
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        printf("Materia no encontrada en el plan.\n");
    }
    SetConsoleTextAttribute(hConsole, saved_attributes);
}

// Funcion para rendir primer parcial ingresando un alumno | Nombre de materia a rendir
void rendirFirst(nodeDL *nodoEstudiante, char materia[55])
{
    HANDLE hConsole = cargarSetWindowsAPI();
    int cantMaterias = nodoEstudiante->estudiante->cantMaterias;
    int indice = findMateriaAlumno(materia, cantMaterias, nodoEstudiante->estudiante->materias);

    if (indice != -1)
    {
        float valor = ((float)rand() / RAND_MAX) * 9.0f + 1.0f; // Genera un valor float aleatorio de 1 a 10
        nodoEstudiante->estudiante->materias[indice].firstTest = valor;
        if (valor < 4)
        {
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
            printf("\nDesaprobaste con: %.1f\n", valor);
        }
        else
        {
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            printf("\nAprobaste con: %.1f\n", valor); // Al valor le pedimos que muestre solo 1 decimal
        }
        return;
    }
    else
    {
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        printf("\n-Materia no encontrada.\n");
        return;
    }
    SetConsoleTextAttribute(hConsole, saved_attributes);
}

// Funcion para rendir segundo parcial ingresando un alumno | Nombre de materia a rendir
void rendirSecond(nodeDL *nodoEstudiante, char materia[55])
{
    HANDLE hConsole = cargarSetWindowsAPI();
    int cantMaterias = nodoEstudiante->estudiante->cantMaterias;
    int indice = findMateriaAlumno(materia, cantMaterias, nodoEstudiante->estudiante->materias);

    if (indice != -1)
    {
        float valor = ((float)rand() / RAND_MAX) * 9.0f + 1.0f; // Genera un valor float aleatorio de 1 a 10
        nodoEstudiante->estudiante->materias[indice].secondTest = valor;
        if (valor < 4)
        {
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
            printf("\nDesaprobaste con: %.1f\n", valor);
        }
        else
        {
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            printf("\nAprobaste con: %.1f\n", valor); // Al valor le pedimos que muestre solo 1 decimal
        }
        return;
    }
    else
    {
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        printf("\n-Materia no encontrada.\n");
        return;
    }
    SetConsoleTextAttribute(hConsole, saved_attributes);
}

// Funcion para rendir final ingresando un alumno | Nombre de materia a rendir
void rendirFinal(nodeDL *nodoEstudiante, char materia[55])
{
    HANDLE hConsole = cargarSetWindowsAPI();
    int cantMaterias = nodoEstudiante->estudiante->cantMaterias;
    int indice = findMateriaAlumno(materia, cantMaterias, nodoEstudiante->estudiante->materias);

    if (indice != -1)
    {
        float valor = ((float)rand() / RAND_MAX) * 9.0f + 1.0f; // Genera un valor float aleatorio de 1 a 10
        float primerParcial = nodoEstudiante->estudiante->materias[indice].firstTest;
        float segundoParcial = nodoEstudiante->estudiante->materias[indice].secondTest;

        // FUNCION PROMEDIO
        float promedio = (primerParcial + segundoParcial) / 2; // Promedio de primer y segundo parcial

        if (promedio < 4)
        {
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
            printf("\n-No tenes aprobada la cursada: %.1f\n", valor);
            return;
        }
        else
        {
            if (valor < 4)
            {
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
                printf("\n-Final desaprobado con: %.1f\n", valor);
                return;
            }
            else
            {

                nodoEstudiante->estudiante->materias[indice].finalTest = valor; // Asigna el valor al final
                nodoEstudiante->estudiante->materias[indice].aprobada = 1;      // Marca la materia como aprobada
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                printf("\n-Felicidades aprobaste, tu nota es: %.1f\n", valor);
                return;
            }
        }
    }
    else
    {
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        printf("\n-Materia no encontrada.\n");
        return;
    }
    SetConsoleTextAttribute(hConsole, saved_attributes);
}

// Funcion para rendir primer,segundo parcial y final ingresando un estudiante | Materia a rendir
void rendirMateria(nodeDL *nodoEstudiante, char materia[55])
{
    HANDLE hConsole = cargarSetWindowsAPI();
    int opc = 0;
    int flag = 0;
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("\nElija una opcion\n");
    printf("------------------\n");
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    printf("1-Rendir First\n");
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("2-Rendir Second\n");
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("3-Rendir Final\n");
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
    printf("4-Salir\n");
    SetConsoleTextAttribute(hConsole, saved_attributes);
    opc = getch() - '0';
    while (flag == 0)
    {
        switch (opc)
        {
        case 1:
        {
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            printf("\nPrimer Parcial\n");
            printf("------------------\n");
            rendirFirst(nodoEstudiante, materia);
            flag = 1;
            break;
        }
        case 2:
        {
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            printf("\nSegundo Parcial\n");
            printf("------------------\n");
            rendirSecond(nodoEstudiante, materia);
            flag = 1;
            break;
        }
        case 3:
        {
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            printf("\nEvaluación Final\n");
            printf("------------------\n");
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
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            printf("\n-Opcion no encontrada, por favor ingrese otro valor.\n");
            break;
        }
    }
    SetConsoleTextAttribute(hConsole, saved_attributes);
}

// FUNCIONES MATERIAS

void modificarMateria(char nombreMateria[55], char nuevoNombre[55], Materia materias[])
{
    HANDLE hConsole = cargarSetWindowsAPI();
    int indice = findMateria(nombreMateria, cantidadMaterias, materias);
    if (indice != -1)
    {
        strcpy(materias[indice].nombreMateria, nuevoNombre);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        printf("\nMateria modificada con exito.\n");
    }
    else
    {
        printf("\nMateria no encontrada.\n");
    }
    SetConsoleTextAttribute(hConsole, saved_attributes);
}

void printPromedios(doubleLinkedList *lista)
{
    HANDLE hConsole = cargarSetWindowsAPI();
    float promedioAlumno = 0;
    float sumaFinales = 0;
    nodeDL *node = lista->head;
    int i = 0;
    if (lista->size == 0)
    {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        printf("\n-No hay estudiantes cargados.\n");
        SetConsoleTextAttribute(hConsole, saved_attributes);
        return;
    }

    while (i != lista->size)
    {
        promedioAlumno = 0;
        for (int i = 0; i < node->estudiante->cantMaterias; i++)
        {
            if (node->estudiante->materias[i].finalTest > 0)
            {
                sumaFinales += node->estudiante->materias[i].finalTest;
            }
        }
        promedioAlumno = sumaFinales / node->estudiante->cantMaterias; // Promedio de las materias aprobadas
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        printf("Nombre: %s, Promedio: %.1f\n", node->estudiante->nombre, promedioAlumno);
        SetConsoleTextAttribute(hConsole, saved_attributes);
        sumaFinales = 0; // Reinicio la suma para el siguiente alumno
        promedioAlumno = 0;
        if (node->next != NULL)
        {
            node = node->next;
        }

        i++;
    }
}

void findByRange(int edadMin, int edadMax, doubleLinkedList *listaEncontradosEdad)
{

    HANDLE hConsole = cargarSetWindowsAPI();
    int encontrados = 0;
    nodeDL *node = lista.head; // Usas la variable global 'lista'
    int i = 0;
    while (i != lista.size)
    {
        int anioNacimiento = returnAnioEdad(node->estudiante->nacimiento);
        int edad = obtenerAnioActual() - anioNacimiento;

        if (edad >= edadMin && edad <= edadMax)
        {
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            printf("\n-Estudiante encontrado: Nombre: %s, DNI: %d, Legajo: %d, Edad: %d\n", node->estudiante->nombre, node->estudiante->dni, node->estudiante->legajo, edad);
            encontrados++;
             SetConsoleTextAttribute(hConsole, saved_attributes);
            append(listaEncontradosEdad, node->estudiante);
        }

        node = node->next;
        i++;
    }
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("\n----------------------------------------------------------------------------------\n");

    if (encontrados == 0)
    {
        printf("\n-No se encontraron estudiantes en el rango de edad especificado.\n");
        SetConsoleTextAttribute(hConsole, saved_attributes);
    }
;
}

// Funcion para eliminar materia de un estudiante ingresando un alumno tipo Estudiante | nombre de la materia
void eliminarMateria(Estudiante *estudiante, char materia[55])
{
    HANDLE hConsole = cargarSetWindowsAPI();
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
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        printf("\n-Materia eliminada con exito para todos los alumnos.\n", estudiante->nombre);
        SetConsoleTextAttribute(hConsole, saved_attributes);
        return;
    }
    else
    {
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        printf("\n-Materia no encontrada.\n");
        SetConsoleTextAttribute(hConsole, saved_attributes);
        return;
    }
}

// ELIMINAR MATERIA PARA ALUMNO: NUEVO

void eliminarMateriaAlumno(char nombreMateria[55])
{
    HANDLE hConsole = cargarSetWindowsAPI();
    nodeDL *nodoEstudiante = lista.head;
    if (nodoEstudiante == NULL)
        return;
    int i = 0;
    while (i != lista.size)
    {
        if (strcmp(nodoEstudiante->estudiante->materias[i].nombreMateria, nombreMateria) == 0)
        {
            eliminarMateria(nodoEstudiante->estudiante, nombreMateria); // Elimino la materia para todos los alumnos
        }
        nodoEstudiante = nodoEstudiante->next;
        i++;
    }

    eliminarMateriaPlan(nombreMateria, materias); // Elimino la materia del plan de estudio
}

// ELIMINAR MATERIA EN PLAN

void eliminarMateriaPlan(char nombreMateria[55], Materia materias[])
{
    HANDLE hConsole = cargarSetWindowsAPI();
    int indice = findMateria(nombreMateria, cantidadMaterias, materias);
    if (indice != -1)
    {
        for (int i = indice; i < cantidadMaterias - 1; i++)
        {
            materias[i] = materias[i + 1]; // Sobreescribe con la siguiente
        }
        cantidadMaterias--;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf("\n-Materia eliminada del plan de estudio con exito.\n");
    }

    SetConsoleTextAttribute(hConsole, saved_attributes);
}

int determinarModuloMateria(cantidadMaterias)
{
    if (cantidadMaterias % 2 == 0)
    {
        return cantidadMaterias / 2; // Si es par, retorna la mitad
    }
    else
    {
        return (cantidadMaterias / 2) + 1; // Si es impar, retorna la mitad + 1
    }
}

int determinarModulo(doubleLinkedList *lista)
{

    if (lista->size % 2 == 0) // Si el tamaño de la lista es par
    {
        return lista->size / 2; // Retorna la mitad del tamaño
    }
    else
    {
        return (lista->size + 1) / 2; // Retorna la mitad redondeada hacia arriba en caso de impar. Ej Lista tam = 11 = 12 / 2 = 6
    }
}