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

  Bioma* bioma = bioma_new("nombre", "region", 1);
  Veterinario* vet = veterinario_new(1, 0, "nombre", 0, "correo", "fecha");
  Animal* animal = animal_new(1, 1, "fecha", "nombre", "especie");
  //administrador_agrega(administrador, bioma, BIOMA);
  administrador_agrega(administrador, vet, VETERINARIO);
  administrador_agrega(administrador, animal, ANIMAL);
  
  
  Bioma* bioma1 = administrador_consulta(administrador, 5, BIOMA);
  if (bioma1)
    printf("%d,%s\n", bioma_id(bioma1), bioma_nombre(bioma1));
  bioma_free(bioma);
  if (bioma1)
    bioma_free(bioma1);
  administrador_free(administrador);

  return 0;
}
