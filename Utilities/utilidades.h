#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define STRUCTS_H
#include "structs.h"
#include <windows.h>
#include <conio.h>

#define CANT_ESTUDIANTES 10

// Defino una constante para la cantidad de materias para sumar materias nuevas sin modificar el codigo
#define CANT_MATERIAS (sizeof(nombres) / sizeof(nombres[0]))

char *nombres[] = {"Algebra1", "Algebra2", "AyP1", "AyP2", "AyP3", "Base-Datos", "Historia", "Matematica-Discreta", "Disenio-Logico"};

// Guardar color original
CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
WORD saved_attributes;

// Defino una constante para la cantidad de materias para sumar materias nuevas sin modificar el codigo
doubleLinkedList lista = {NULL, NULL, 0};
Materia *materias = NULL;
int cantidadMaterias = 9;

char *upperCase(char *cadena)
{

    // \0 indica caracter nulo(final de la cadena)
    for (int i = 0; cadena[i] != '\0'; i++)
    {
        cadena[i] = toupper((unsigned char)cadena[i]); // Unsigned char para evitar problemas con caracteres negativos( ejemplo la ñ o caracteres acentuados) y que no crashee.
    }
    return cadena;
}

// Usa libreria time.h para obtener el año actual
int obtenerAnioActual()
{
    time_t t = time(NULL);              // Obtiene el tiempo actual
    struct tm *tm_info = localtime(&t); // Lo convierte a estructura local

    int anio = tm_info->tm_year + 1900; // Año desde 1900 Porque tm_year representa el número de años desde 1900, entonces: se debe sumar 1900

    return anio; // Retorna el año actual
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

int returnAnioEdad(char *fecha)
{
    char copia[11];
    strcpy(copia, fecha); // strtok modifica la cadena original, por eso copiamos

    // Usamos strtok como un split( parte basado en un delimitador )
    char *diaStr = strtok(copia, "/");
    char *mesStr = strtok(NULL, "/");
    char *anioStr = strtok(NULL, "/");
    int anio = atoi(anioStr);
    return anio; // Retorna el año de la fecha ingresada
}

void cargarEstudiantesPrueba(Materia materias[])
{
    Estudiante *e1 = malloc(sizeof(Estudiante));
    strcpy(e1->nombre, "Ana");
     strcpy(e1->apellido, "Gomez");
    strcpy(e1->nacimiento, "15/05/1999");
    e1->dni = 11111111;
    e1->legajo = 1001;
    e1->cantMaterias = 0;

    agregarMateria(e1, materias[0]); // Algebra1
    agregarMateria(e1, materias[1]); // Algebra2
    e1->materias[0].firstTest = 0;
    e1->materias[0].secondTest = 0;
    e1->materias[0].aprobada = 0;

    e1->materias[1].firstTest = 0;
    e1->materias[1].secondTest = 0;
    e1->materias[1].finalTest = 0;
    e1->materias[1].aprobada = 0;
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
     e2->materias[0].firstTest = 0;
     e2->materias[0].secondTest = 0;
     e2->materias[0].aprobada = 0;

     e2->materias[1].firstTest = 0;
     e2->materias[1].secondTest = 0;
     e2->materias[1].finalTest = 0;
     e2->materias[1].aprobada = 0;
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
     e3->materias[0].firstTest = 0;
     e3->materias[0].secondTest = 0;
     e3->materias[0].aprobada = 0;

     e3->materias[1].firstTest = 0;
     e3->materias[1].secondTest = 0;
     e3->materias[1].finalTest = 0;
     e3->materias[1].aprobada = 0;
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
     e4->materias[0].firstTest = 0;
     e4->materias[0].secondTest = 0;
     e4->materias[0].aprobada = 0;

     e4->materias[1].firstTest = 0;
     e4->materias[1].secondTest = 0;
     e4->materias[1].finalTest = 0;
     e4->materias[1].aprobada = 0;
     append(&lista, e4);
    
     // Estudiante 5
      Estudiante *e5 = malloc(sizeof(Estudiante));
     strcpy(e5->nombre, "Juan Perez");
     strcpy(e5->nacimiento, "15/08/2000");
     e5->dni = 55555555;
     e5->legajo = 1005;
     e5->cantMaterias = 0;

     agregarMateria(e5, materias[6]); // Historia
     agregarMateria(e5, materias[7]); // Matematica Discreta
     e5->materias[0].firstTest = 0;
     e5->materias[0].secondTest = 0;
     e5->materias[0].aprobada = 0;

     e5->materias[1].firstTest = 0;
     e5->materias[1].secondTest = 0;
     e5->materias[1].finalTest = 0;
     e5->materias[1].aprobada = 0;
     append(&lista, e5);

     // Estudiante 6
      Estudiante *e6 = malloc(sizeof(Estudiante));
     strcpy(e6->nombre, "Jose Hernandez");
     strcpy(e6->nacimiento, "06/06/1999");
     e6->dni = 66666666;
     e6->legajo = 1006;
     e6->cantMaterias = 0;

     agregarMateria(e6, materias[3]); // AyP2
     agregarMateria(e6, materias[2]); // AyP1
     e6->materias[0].firstTest = 0;
     e6->materias[0].secondTest = 0;
     e6->materias[0].aprobada = 0;

     e6->materias[1].firstTest = 0;
     e6->materias[1].secondTest = 0;
     e6->materias[1].finalTest = 0;
     e6->materias[1].aprobada = 0;
     append(&lista, e6);

     // Estudiante 7
      Estudiante *e7 = malloc(sizeof(Estudiante));
     strcpy(e7->nombre, "Florencia Cruz");
     strcpy(e7->nacimiento, "05/01/2004");
     e7->dni = 7777777;
     e7->legajo = 1007;
     e7->cantMaterias = 0;

     agregarMateria(e7, materias[4]); // AyP3
     agregarMateria(e7, materias[1]); // Algebra2
     e7->materias[0].firstTest = 0;
     e7->materias[0].secondTest = 0;
     e7->materias[0].aprobada = 0;

     e7->materias[1].firstTest = 0;
     e7->materias[1].secondTest = 0;
     e7->materias[1].finalTest = 0;
     e7->materias[1].aprobada = 0;
     append(&lista, e7);

     // Estudiante 8
      Estudiante *e8 = malloc(sizeof(Estudiante));
     strcpy(e8->nombre, "Cristina Wayne");
     strcpy(e8->nacimiento, "15/08/2001");
     e8->dni = 88888888;
     e8->legajo = 1008;
     e8->cantMaterias = 0;

     agregarMateria(e8, materias[0]); // Algebra1
     agregarMateria(e8, materias[4]); // AyP3
     e8->materias[0].firstTest = 0;
     e8->materias[0].secondTest = 0;
     e8->materias[0].aprobada = 0;

     e8->materias[1].firstTest = 0;
     e8->materias[1].secondTest = 0;
     e8->materias[1].finalTest = 0;
     e8->materias[1].aprobada = 0;
     append(&lista, e8);

     // Estudiante 9
      Estudiante *e9 = malloc(sizeof(Estudiante));
     strcpy(e9->nombre, "Federico Ferro");
     strcpy(e9->nacimiento, "01/02/2003");
     e9->dni = 99999999;
     e9->legajo = 1009;
     e9->cantMaterias = 0;

     agregarMateria(e9, materias[5]); // Base-Datos
     agregarMateria(e9, materias[7]); // Matematica Discreta
     e9->materias[0].firstTest = 0;
     e9->materias[0].secondTest = 0;
     e9->materias[0].aprobada = 0;

     e9->materias[1].firstTest = 0;
     e9->materias[1].secondTest = 0;
     e9->materias[1].finalTest = 0;
     e9->materias[1].aprobada = 0;
     append(&lista, e9);

     //estudiante 10
      Estudiante *e10 = malloc(sizeof(Estudiante));
     strcpy(e10->nombre, "Tobias Kent");
     strcpy(e10->nacimiento, "12/09/1990");
     e10->dni = 10101010;
     e10->legajo = 10010;
     e10->cantMaterias = 0;

     agregarMateria(e10, materias[0]); // Algebra1
     agregarMateria(e10, materias[1]); // Algebra2
    e10->materias[0].firstTest = 0;
     e10->materias[0].secondTest = 0;
    e10->materias[0].aprobada = 0;

     e10->materias[1].firstTest = 0;
     e10->materias[1].secondTest = 0;
     e10->materias[1].finalTest = 0;
     e10->materias[1].aprobada = 0;
     append(&lista, e10);



     //estudiante 11
      Estudiante *e11 = malloc(sizeof(Estudiante));
     strcpy(e11->nombre, "Federico Lacrosse");
     strcpy(e11->nacimiento, "12/10/1999");
     e11->dni = 13623789;
     e11->legajo = 10015;
     e11->cantMaterias = 0;

     agregarMateria(e11, materias[6]); // Historia
     agregarMateria(e11, materias[1]); // Algebra2
    e11->materias[0].firstTest = 0;
     e11->materias[0].secondTest = 0;
    e11->materias[0].aprobada = 0;

     e11->materias[1].firstTest = 0;
     e11->materias[1].secondTest = 0;
     e11->materias[1].finalTest = 0;
     e11->materias[1].aprobada = 0;
     append(&lista, e11);
}

void cargarMaterias(Materia materias[]) // Recibo Materia materias[] que es equivalente a Materia *materias
{
    for (int i = 0; i < CANT_MATERIAS; i++)
    {
        strcpy(materias[i].nombreMateria, nombres[i]);
        materias[i].inscripto = 0;
        materias[i].aprobada = 0;
        materias[i].firstTest = 0;
        materias[i].secondTest = 0;
    }
}
void inicializarFuncionRand()
{
    srand(time(NULL)); // Inicializa la semilla para generar números aleatorios
}

// Configuracion para consola, carga libreria de windowns para personalizar terminal
HANDLE cargarSetWindowsAPI()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //Obtiene variable para personalizacion de consola
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;
    return hConsole; // Retorna el handle del console
}



void cargarEstudiantesPruebaMasivo(int cantidad)
{
    for (int i = 0; i < cantidad; i++)
    {
        Estudiante *e = malloc(sizeof(Estudiante));
        sprintf(e->nombre, "Estudiante");
        sprintf(e->apellido, "%d", i + 1);

        sprintf(e->nacimiento, "01/01/199%d", (i % 10) + 1); // años 1991-2000
        e->dni = 10000000 + i;
        e->legajo = 2000 + i;
        e->cantMaterias = 0;

        // Asignar materias de prueba
        for (int j = 0; j < CANT_MATERIAS && j < 3; j++) // Solo 3 materias por estudiante
        {
            agregarMateria(e, materias[j]);
            e->materias[j].firstTest = 6 + (i % 5);
            e->materias[j].secondTest = 7 + (i % 3);
            e->materias[j].aprobada = 1;

        }
        append(&lista, e);
    }
    printList(&lista); // Imprime la lista de estudiantes cargados
}

void cargarMateriasMasivo(int cantidad)
{
    for (int i = cantidadMaterias; i < cantidad; i++)
    {
        sprintf(materias[i].nombreMateria, "Materia%d", i + 1);
        materias[i].inscripto = 0;
        materias[i].aprobada = 0;
        materias[i].firstTest = 0;
        materias[i].secondTest = 0;
        cantidadMaterias++;
    }
    printMaterias(materias); // Imprime las materias cargadas
}