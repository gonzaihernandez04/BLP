#include <assert.h>

#include "doubleLinkedList.h"


void testCargarEstudiante(){
    doubleLinkedList lista = {NULL, NULL, 0};
    Estudiante *estudiante = malloc(sizeof(Estudiante));
    strcpy(estudiante->nombre, "Juan Perez");
    strcpy(estudiante->nacimiento, "01/01/2000");
    estudiante->dni = 12345678;
    estudiante->legajo = 1234;
    estudiante->cantMaterias = 0;

    append(&lista, estudiante);
    
    assert(lista.size == 1);
    assert(strcmp(lista.head->estudiante->nombre, "Juan Perez") == 0);
    assert(lista.head->estudiante->dni == 12345678);
    
    clear(&lista);
}

void testFindByDNI(){
    doubleLinkedList lista = {NULL, NULL, 0};
    Estudiante *estudiante1 = malloc(sizeof(Estudiante));
    Estudiante *estudiante2 = malloc(sizeof(Estudiante));
    Estudiante *estudiante3 = malloc(sizeof(Estudiante));
    strcpy(estudiante1->nombre, "Ana Gomez");
    estudiante1->dni = 87654321;

     strcpy(estudiante1->nombre, "Gonzalo Gomez");
    estudiante1->dni = 42345678;

     strcpy(estudiante1->nombre, "Maria Lopez");
    estudiante1->dni = 12345678;
    append(&lista, estudiante1);

    // Busca el DNI Especifico
    nodeDL *foundNode = findByDNI(87654321, &lista);
    assert(foundNode != NULL);
    assert(strcmp(foundNode->estudiante->nombre, "Ana Gomez") == 0);

    clear(&lista);
}