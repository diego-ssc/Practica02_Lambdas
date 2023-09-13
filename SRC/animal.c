#include "animal.h"

/* La estructura Animal. */
struct Animal_ {
  /* El identificador. */
  int id;
  /* El bioma al que pertenece. */
  int bioma;
  /* La fecha de nacimiento. */
  char* fecha_nacimiento;
  /* El nombre común del animal. */
  char* nombre;
  /* La especie. */
  char* especie;
};

/* Constructor para la estructura Animal */
Animal* animal_new(int id, int bioma , char* fecha, char* nombre, char* especie){
  Animal* nuevo_animal = malloc((sizeof(Animal)));
  nuevo_animal->id = id;
  nuevo_animal->bioma = bioma;
  nuevo_animal->fecha_nacimiento = malloc(sizeof(char)*(strnlen(fecha, TAMANO_NOMBRE)+1));
  strcpy(nuevo_animal->fecha_nacimiento, fecha);
  nuevo_animal->nombre = malloc(sizeof(char)*(strnlen(nombre, TAMANO_NOMBRE)+1));
  strcpy(nuevo_animal->nombre, nombre);
  nuevo_animal->especie = malloc(sizeof(char)*(strnlen(especie, TAMANO_NOMBRE)+1));
  strcpy(nuevo_animal->especie, especie);
  return nuevo_animal;
}

/* Libera animal */
void animal_free(Animal* animal){
  if(animal->fecha_nacimiento)
    free(animal->fecha_nacimiento);
  if(animal->nombre)
    free(animal->nombre);
  if(animal->especie)
    free(animal->especie);
  free(animal);
}

/* Setter para el atributo fecha de nacimiento  */
void animal_set_fecha_nacimiento(Animal* animal, char* nueva_fecha){
  if(animal->fecha_nacimiento)
    free(animal->fecha_nacimiento);
  animal->fecha_nacimiento = malloc(sizeof(char)*(strnlen(nueva_fecha, TAMANO_NOMBRE)+1));
  strcpy(animal->fecha_nacimiento, nueva_fecha);
}

/*  Regresa la fecha de nacimiento del animal */
char* animal_get_fecha_nacimiento(Animal* animal) {
  return animal->fecha_nacimiento;
}

/* Setter para el atributo nombre */
void animal_set_nombre(Animal* animal, char* nuevo_nombre) {
  if(animal->nombre)
    free(animal->nombre);
  animal->nombre = malloc(sizeof(char)*(strnlen(nuevo_nombre, TAMANO_NOMBRE)+1));
  strcpy(animal->nombre, nuevo_nombre);
}

/* Regresa el nombre del animal */
char* animal_get_nombre(Animal* animal) {
  return animal->nombre;
}

/*  Setter para el atributo especie */
void animal_set_especie(Animal* animal, char* nueva_especie) {
  if(animal->especie)
    free(animal->especie);
  animal->especie = malloc(sizeof(char)*(strnlen(nueva_especie, TAMANO_NOMBRE)+1));
  strcpy(animal->especie, nueva_especie);
}

/* Regresa la especie del animal */
char* animal_get_especie(Animal* animal) {
  return animal->especie;
}


/* Regresa el id del animal */
int animal_id(Animal* animal) {
  return animal->id;
}

/* Regresa el bioma del animal */
int animal_bioma(Animal* animal) {
  return animal->bioma;
}
