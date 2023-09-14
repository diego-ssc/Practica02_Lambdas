#include <stdlib.h>
#include <stdio.h>

#include "sistema.h"

/* Ejecución del hilo de ejecución principal. */
int main(int argc, char** argv) {

  Bioma* bioma = bioma_new("Hello", "There", 5);
  Administrador* administrador = administrador_new("veterinario.csv",
                                                   "bioma.csv",
                                                   "animal.csv");

  administrador_agrega_b(administrador, bioma);

  bioma_free(bioma);
  administrador_free(administrador);
  return 0;
}
