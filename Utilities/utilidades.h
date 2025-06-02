#include <string.h>
#include <ctype.h>
char *upperCase(char *cadena)
{
    for (int i = 0; cadena[i] != '\0'; i++) {
        cadena[i] = toupper((unsigned char)cadena[i]);
    }
    return cadena;
}