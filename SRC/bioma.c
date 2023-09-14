#include "bioma.h"
#include <stdlib.h>
#include <string.h>

/* La estructura bioma. */
struct Bioma_ {
  /* El nombre. */
  char* nombre;
  /* La región. */
  char* region;
  /* El identificador. */
  int id;
  /*El numero de jaulas. */
  int n_jaulas;
  /*EL numero de cuidadores.*/
  int n_cuidadores;
  /*El numero de veterinarios. */
  int n_veterinarios;
  /*El numero de animales. */
  int n_animales;
  /*La lista de servicios del bioma*/
  char* servicios;
};

/* Crea un nuevo Bioma. */
Bioma* bioma_new(char* nombre, char* region, int id, int n_jaulas, int n_cuidadores,
                int n_veterinarios, int n_animales, char* servicios) {
  /* Reservación en el heap. */
  Bioma* bioma = malloc(sizeof(struct Bioma_));

  /* Inicialización del heap. */
  bioma->nombre = malloc(sizeof(char)*(strnlen(nombre, TAMANO_NOMBRE)+1));
  strcpy(bioma->nombre, nombre);

  bioma->region = malloc(sizeof(char)*(strnlen(region, TAMANO_NOMBRE)+1));
  strcpy(bioma->region, region);
                
  bioma->servicios = malloc(sizeof(char)*(strnlen(servicios, TAMANO_NOMBRE)+1));
  strcpy(bioma->servicios, servicios);

  bioma->id = id;
  bioma->n_jaulas = n_jaulas;         
  bioma->n_cuidadores = n_cuidadores;
  bioma->n_veterinarios = n_veterinarios;
  bioma->n_animales = n_animales;              

  return bioma;
}

/* Libera la memoria usada por un Bioma. */
void bioma_free(Bioma* bioma) {
  if (bioma->nombre)
    free(bioma->nombre);
  if (bioma->region)
    free(bioma->region);
  free(bioma);
}

/* Devuelve el nombre del bioma. */
char* bioma_nombre(Bioma* bioma) {
  return bioma->nombre;
}

/* Devuelve la región del bioma. */
char* bioma_region(Bioma* bioma) {
  return bioma->region;
}

/* Devuelve el identificador del bioma. */
int bioma_id(Bioma* bioma) {
  return bioma->id;
}

/* Asigna el nombre del bioma. */
void bioma_set_nombre(Bioma* bioma, char* nombre) {
  if (bioma->nombre)
    free(bioma->nombre);
  bioma->nombre = malloc(sizeof(char)*(strnlen(nombre, TAMANO_NOMBRE)+1));
  strcpy(bioma->nombre, nombre);
}

/* Asigna la región del bioma. */
void bioma_set_region(Bioma* bioma, char* region) {
  if (bioma->region)
    free(bioma->region);
  bioma->region = malloc(sizeof(char)*(strnlen(region, TAMANO_NOMBRE)+1));
  strcpy(bioma->region, region);
}

/* Asigna el identificador del bioma. */
void bioma_set_id(Bioma* bioma, int id) {
  bioma->id = id;
}
