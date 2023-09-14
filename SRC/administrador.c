#include "administrador.h"
#include "sistema.h"
#include <stdio.h>
#include <stdlib.h>
/*#include <glib.h>*/

/* La estructura Administrador. */
struct Administrador_ {
  /* El archivo de veterinarios. */
  FILE* fp_v;
  /* El archivo de biomas. */
  FILE* fp_b;
  /* El archivo de animales. */
  FILE* fp_a;

};

/* Construye un Administrador. */
Administrador* administrador_new(char* file_n_vet, char* file_n_bi, char* file_n_an) {
  /* Reservación en heap. */
  Administrador* administrador = malloc(sizeof(struct Administrador_));

  /* Inicialización del heap. */
  administrador->fp_v = fopen(file_n_vet, "r");
  administrador->fp_b = fopen(file_n_bi, "r");
  administrador->fp_a = fopen(file_n_an, "r");

  if (!administrador->fp_v) {
    fprintf(stderr, "Sistema:\tNo se pudo abrir el archivo: %s\n", file_n_vet);
    exit(1);
  }

  if (!administrador->fp_b) {
    fprintf(stderr, "Sistema:\tNo se pudo abrir el archivo: %s\n", file_n_bi);
    exit(1);
  }

  if (!administrador->fp_a) {
    fprintf(stderr, "Sistema:\tNo se pudo abrir el archivo: %s\n", file_n_an);
    exit(1);
  }

  return administrador;
}

/* Libera la memoria usada por el Administrador. */
void administrador_free(Administrador* administrador) {
  fclose(administrador->fp_v);
  fclose(administrador->fp_b);
  fclose(administrador->fp_a);
  free(administrador);
}

void administrador_menu_principal (){
  printf("1.Agregar.");
  printf("2.Consultar.");
  printf("3.Editar.");
  printf("4.Eliminar");
  printf("5.Salir");

  int opcion=getchar();
  switch (opcion) {
    case 1:
      break;
    case 2:
      break;
    case 3:
      break;
    case 4:
      break;
    case 5:
      break;
    default: puts("Se ha pulsado una opcion incorrecta");
  }
}

char* menu_entidades(){
  printf("1.Veterinario.");
  printf("2.Animales.");
  printf("3.Biomas.");
  int opcion = getchar();
  switch (opcion) {
    case 1: return ENTIDAD_VETERINARIO;
    case 2: return ENTIDAD_ANIMAL;
    case 3: return ENTIDAD_BIOMA;
    default:puts("Entidad incorrecta");
  }
  return "salir";
}

void administrador_agrega(Administrador* administrador, char* entidad){

}
