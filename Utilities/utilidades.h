#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define CANT_ESTUDIANTES 10

// Defino una constante para la cantidad de materias para sumar materias nuevas sin modificar el codigo
#define CANT_MATERIAS (sizeof(nombres) / sizeof(nombres[0]))

char *nombres[] = {"Algebra1", "Algebra2", "AyP1", "AyP2", "AyP3", "Base-Datos", "Historia", "Matematica-Discreta", "Disenio-Logico"};

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