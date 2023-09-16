#include <stdlib.h>
#include <stdio.h>

#include "sistema.h"
#include "entidad.h"

#define NUMERO_ENTIDADES 3
#define NUMERO_ENTIDADES 3

/* Hilo de ejecución principal. */
int main(int argc, char** argv) {
  const char * archivos[] = {
    "animal.csv",
    "bioma.csv",
    "veterinario.csv"
  };

  Administrador* administrador = administrador_new(archivos,
                                                   NUMERO_ENTIDADES);

  Bioma* bioma = bioma_new("wen", "wen", 1);
  administrador_agrega(administrador, bioma, BIOMA);

  bioma_free(bioma);
  administrador_free(administrador);
  return 0;
}
