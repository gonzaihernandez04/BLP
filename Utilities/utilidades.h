#include <string.h>
#include <ctype.h>
char *upperCase(char *cadena)
{

    // \0 indica caracter nulo(final de la cadena)
    for (int i = 0; cadena[i] != '\0'; i++) {
        cadena[i] = toupper((unsigned char)cadena[i]); //Unsigned char para evitar problemas con caracteres negativos( ejemplo la ñ o caracteres acentuados) y que no crashee.
    }
    return cadena;
}