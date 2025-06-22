#include <assert.h>

#include "../doubleLinkedList.h"

void testCargarEstudiante()
{
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

}

void testFindByDNI()
{
    doubleLinkedList lista = {NULL, NULL, 0};
    Estudiante *estudiante1 = malloc(sizeof(Estudiante));
    Estudiante *estudiante2 = malloc(sizeof(Estudiante));
    Estudiante *estudiante3 = malloc(sizeof(Estudiante));

    strcpy(estudiante1->nombre, "Ana Gomez");
    estudiante1->dni = 87654321;
    append(&lista, estudiante1);

    strcpy(estudiante2->nombre, "Gonzalo Gomez");
    estudiante2->dni = 42345678;
    append(&lista, estudiante2);

    strcpy(estudiante3->nombre, "Maria Lopez");
    estudiante3->dni = 12345678;
    append(&lista, estudiante3);

    // Busca el DNI Especifico
    nodeDL *foundNode = findByDNI(87654321, &lista);
    assert(foundNode != NULL);
    assert(strcmp(foundNode->estudiante->nombre, "Ana Gomez") == 0);

    
}
// Buscar por nombre
void testFindByNombre(){
    doubleLinkedList lista = {NULL, NULL, 0};
    Estudiante *estudiante1 = malloc(sizeof(Estudiante));
    Estudiante *estudiante2 = malloc(sizeof(Estudiante));
    Estudiante *estudiante3 = malloc(sizeof(Estudiante));

    strcpy(estudiante1->nombre, "Ana Gomez");
    estudiante1->dni = 87654321;
    append(&lista, estudiante1);

    strcpy(estudiante2->nombre, "Gonzalo Gomez");
    estudiante2->dni = 42345678;
    append(&lista, estudiante2);

    strcpy(estudiante3->nombre, "Maria Lopez");
    estudiante3->dni = 12345678;
    append(&lista, estudiante3);

    // Busca el nombre Especifico
    nodeDL *foundNode = findEstudiante("Ana Gomez", &lista);
    assert(foundNode != NULL);
    assert(strcmp(foundNode->estudiante->nombre, "Ana Gomez") == 0);
}
int main()
{
    testCargarEstudiante();
    testFindByDNI();
    // Agrega aquí más tests si tienes
    printf("Todos los tests pasaron correctamente.\n");
    return 0;
}