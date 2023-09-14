#include <stdlib.h>
#include <stdio.h>

#include "sistema.h"

/* Hilo de ejecución principal. */
int main(int argc, char** argv) {

  Bioma* bioma = bioma_new("Hello", "There", 1);
  Administrador* administrador = administrador_new("veterinario.csv",
                                                   "bioma.csv",
                                                   "animal.csv");

  /* administrador_agrega_b(administrador, bioma); */
  administrador_consulta_b(administrador, 3);
  
  bioma_free(bioma);
  administrador_free(administrador);
  return 0;
}
