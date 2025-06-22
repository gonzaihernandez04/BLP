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
Materia *materias[CANT_MATERIAS];


char *upperCase(char *cadena)
{

    // \0 indica caracter nulo(final de la cadena)
    for (int i = 0; cadena[i] != '\0'; i++) {
        cadena[i] = toupper((unsigned char)cadena[i]); //Unsigned char para evitar problemas con caracteres negativos( ejemplo la ñ o caracteres acentuados) y que no crashee.
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


void cargarEstudiantesPrueba(){
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
}


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
void inicializarFuncionRand()
{
    srand(time(NULL)); // Inicializa la semilla para generar números aleatorios
}


// Configuracion para consola
HANDLE cargarSetWindowsAPI(){
      HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;
    return hConsole; // Retorna el handle del console
}