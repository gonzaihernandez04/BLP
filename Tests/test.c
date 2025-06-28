#include <assert.h>

#include "../doubleLinkedList.h"

//Test para la funcion de cargar estudiantes
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
    free(estudiante); // Limpio memoria general
    clear(&lista); // Limpio memoria general

}

//Test para encontrar estudiante mediante su DNI
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

    free(estudiante1);// Limpio memoria general
    free(estudiante2);// Limpio memoria general
    free(estudiante3);// Limpio memoria general
    clear(&lista); // Limpio memoria general

    
}

// Test para buscar por nombre del alumno
void testFindByNombre(){
    doubleLinkedList lista = {NULL, NULL, 0};
    doubleLinkedList listaEncontrados = {NULL, NULL, 0};
    Estudiante *estudiante1 = malloc(sizeof(Estudiante));
    Estudiante *estudiante2 = malloc(sizeof(Estudiante));
    Estudiante *estudiante3 = malloc(sizeof(Estudiante));

    strcpy(estudiante1->nombre, "Ana");
    strcpy(estudiante1->apellido, "Gomez");
    estudiante1->dni = 87654321;
    append(&lista, estudiante1);

    strcpy(estudiante2->nombre, "Gonzalo Gomez");
    estudiante2->dni = 42345678;
    append(&lista, estudiante2);

    strcpy(estudiante3->nombre, "Maria Lopez");
    estudiante3->dni = 12345678;
    append(&lista, estudiante3);

    // Busca el nombre Especifico
    findEstudiante("Ana","Gomez",&listaEncontrados,&lista);
    assert(listaEncontrados.size == 1);
    assert(strcmp(listaEncontrados.head->estudiante->nombre, "Ana") == 0 && strcmp(listaEncontrados.head->estudiante->apellido, "Gomez") == 0) ;

    free(estudiante1);
    free(estudiante2);
    free(estudiante3);
    clear(&lista); // Limpio memoria general
    clear(&listaEncontrados); // Limpio memoria general
}

// Agrega materia a estudiante
void testAgregarMateriaAEstudiante() {
    Estudiante *e = malloc(sizeof(Estudiante));
    strcpy(e->nombre, "Pedro");
    e->cantMaterias = 0;
    Materia m;
    strcpy(m.nombreMateria, "Matematica");
    m.aprobada = 0;

    agregarMateria(e, m);

    assert(e->cantMaterias == 1);
    assert(strcmp(e->materias[0].nombreMateria, "Matematica") == 0);

    free(e);
}


void testEliminarEstudiantePorDNI() {
    doubleLinkedList lista = {NULL, NULL, 0};
    Estudiante *e = malloc(sizeof(Estudiante));
    strcpy(e->nombre, "Laura");
    e->dni = 55555555;
    append(&lista, e);

    deleteNode(e, &lista);

    assert(findByDNI(55555555, &lista) == NULL);

    free(e);
    clear(&lista);
}

//Test para funcion modificar materia
void testModificarMateria(){
    Materia *materias = NULL;
    cantidadMaterias = 9; // Defino la cantidad de materias
   materias = malloc(cantidadMaterias * sizeof(Materia));

    cargarMaterias(materias);
    char nombreMateria[55] = "AyP1";
    char nombreMateriaModificado[55] = "Algoritmos_Programacion_1";
    modificarMateria(nombreMateria,nombreMateriaModificado,materias);
    assert(strcmp(materias[2].nombreMateria, nombreMateriaModificado) == 0);
    free(materias); // Limpio memoria general
}

//Test para funcion de eliminar estudiante 
void testEliminarEstudiante(){
     doubleLinkedList lista = {NULL, NULL, 0};
    Estudiante *estudiante1 = malloc(sizeof(Estudiante));
    Estudiante *estudiante2 = malloc(sizeof(Estudiante));

    strcpy(estudiante1->nombre, "Ana Gomez");
    estudiante1->dni = 87654321;
    append(&lista, estudiante1);

    strcpy(estudiante2->nombre, "Gonzalo Gomez");
    estudiante2->dni = 42345678;
    append(&lista, estudiante2);

    deleteNode(estudiante1, &lista);
    assert(lista.size == 1);
    clear(&lista); // Limpia la lista para evitar fugas de memoria
    free(estudiante1);// Limpio memoria general
    free(estudiante2);// Limpio memoria general
}

//Test para buscar alumnos en un rango de edad
void testBuscarRangoEdad(){
    doubleLinkedList listaEncontrados = {NULL, NULL, 0};
       materias = malloc(cantidadMaterias * sizeof(Materia));

    cargarEstudiantesPrueba(materias);
    cargarMaterias(materias);
    int edadMin = 20;
    int edadMax = 30;
    findByRange(edadMin, edadMax, &listaEncontrados);
    assert(listaEncontrados.size == 9); // Verifica que se hayan encontrado estudiantes en el rango de edad

}

// ELIMINAR MATERIA DEL PLAN GENERAL
void testEliminarMateria(){
        cantidadMaterias = 10; // Defino la cantidad de materias
    Materia *materias = malloc(cantidadMaterias * sizeof(Materia));

    cargarMaterias(materias);
 

    char nombreMateria[55] = "AyP1";
    eliminarMateriaPlan(nombreMateria,materias);
 
    assert(findMateria(nombreMateria, cantidadMaterias, materias) == -1); // Verifica que la materia haya sido eliminada

    free(materias); // Limpio memoria general
}


void testModificarNombreAlumno(){
    doubleLinkedList lista = {NULL, NULL, 0};
    Estudiante *estudiante = malloc(sizeof(Estudiante));
    strcpy(estudiante->nombre, "Carlos");
    strcpy(estudiante->apellido, "Viejo");

    append(&lista, estudiante);
    strcpy(estudiante->nombre, "Carlos");
    strcpy(estudiante->apellido, "Nuevo");
    assert(strcmp(estudiante->nombre, "Carlos") == 0);
    assert(strcmp(estudiante->apellido, "Nuevo") == 0);

    free(estudiante); // Limpio memoria general
    clear(&lista); // Limpio memoria general

}


void testModificarDniAlumno(){
    doubleLinkedList lista = {NULL, NULL, 0};
    Estudiante *estudiante = malloc(sizeof(Estudiante));
    int nuevoDni = 87654321;
    strcpy(estudiante->nombre, "Carlos");
    strcpy(estudiante->apellido, "Viejo");
    estudiante->dni = 12345678;

    append(&lista, estudiante);
   estudiante->dni = nuevoDni; // Modifico el DNI
   assert(estudiante->dni == nuevoDni);
    free(estudiante); // Limpio memoria general
    clear(&lista); // Limpio memoria general

}

void testModificarLegajoAlumno(){
    doubleLinkedList lista = {NULL, NULL, 0};
    Estudiante *estudiante = malloc(sizeof(Estudiante));
    int nuevoLegajo = 72001;
    strcpy(estudiante->nombre, "Carlos");
    strcpy(estudiante->apellido, "Viejo");
    estudiante->dni = 12345678;
    estudiante->legajo = 72000;

    append(&lista, estudiante);
   estudiante->legajo = nuevoLegajo; // Modifico el DNI
   assert(estudiante->legajo == nuevoLegajo);
    free(estudiante); // Limpio memoria general
    clear(&lista); // Limpio memoria general

}


int main()
{
    testCargarEstudiante();
    testFindByDNI();
    testFindByNombre();
    testAgregarMateriaAEstudiante();
    testModificarMateria();
    testEliminarEstudiantePorDNI();
    testEliminarEstudiante();
    testBuscarRangoEdad();
    testEliminarMateria();
    testModificarNombreAlumno();
    testModificarDniAlumno();
    testModificarLegajoAlumno();
    // Agrega aquí más tests si tienes
    printf("\nTodos los tests pasaron correctamente.\n");
    return 0;
}