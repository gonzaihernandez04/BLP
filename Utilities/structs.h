//////////////////// ESTRUCTURA ///////////////////////
typedef struct Materia
{
    char nombreMateria[55];
    int inscripto;
    int aprobada; // Indica si aprobo la materia
    float firstTest;
    float secondTest;
    float finalTest; // Indica si aprobo el final

} Materia;

typedef struct Estudiante
{
    char nombre[45];
    char apellido [45];
    char nacimiento[10];
    int dni;
    int legajo;
    Materia materias[48]; // Hasta 48 materias.
    int cantMaterias;

} Estudiante;

typedef struct nodeDL
{
    Estudiante *estudiante;
    struct nodeDL *next;
    struct nodeDL *prev;
} nodeDL;

typedef struct
{
    nodeDL *head;
    nodeDL *tail;
    int size;
} doubleLinkedList;
