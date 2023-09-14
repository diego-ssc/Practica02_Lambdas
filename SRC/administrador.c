#include "administrador.h"

/* La estructura Administrador. */
struct Administrador_ {
  /* El archivo de veterinarios. */
  FILE* fp_v;
  /* El archivo de biomas. */
  FILE* fp_b;
  /* El archivo de animales. */
  FILE* fp_a;
  /* El nombre de arhivo de Veterinarios. */
  char* file_n_vet;
  /* El nombre de arhivo de Biomas. */
  char* file_n_bi;
  /* El nombre de arhivo de Animales. */
  char* file_n_an;
  /* El número de animales. */
  int n_a;
  /* El número de biomas. */
  int n_b;
  /* El número de veterinarios. */
  int n_v;
};

/* Construye un Administrador. */
Administrador* administrador_new(char* file_n_vet, char* file_n_bi, char* file_n_an) {
  /* Reservación en heap. */
  Administrador* administrador = malloc(sizeof(struct Administrador_));

  /* Inicialización del heap. */
  administrador->file_n_vet = malloc(sizeof(char)*(strnlen(file_n_vet,
                                                           TAMANO_NOMBRE)+1));
  administrador->file_n_bi = malloc(sizeof(char)*(strnlen(file_n_bi,
                                                          TAMANO_NOMBRE)+1));
  administrador->file_n_an = malloc(sizeof(char)*(strnlen(file_n_an,
                                                         TAMANO_NOMBRE)+1));

  strcpy(administrador->file_n_vet, file_n_vet);
  strcpy(administrador->file_n_bi, file_n_bi);
  strcpy(administrador->file_n_an, file_n_an);

  /* Se comenzará con índice 1. */
  administrador->n_a = 1;
  administrador->n_b = 1;
  administrador->n_v = 1;

  /* if (!administrador->fp_b) { */
  /*   fprintf(stderr, "Sistema:\tNo se pudo abrir el archivo: %s\n", file_n_bi); */
  /*   exit(1); */
  /* } */

  /* if (!administrador->fp_a) { */
  /*   fprintf(stderr, "Sistema:\tNo se pudo abrir el archivo: %s\n", file_n_an); */
  /*   exit(1); */
  /* } */

  return administrador;
}

/* Libera la memoria usada por el Administrador. */
void administrador_free(Administrador* administrador) {
  free(administrador);
}

/* Agrega el Animal parámetro a la base de datos. */
void administrador_agrega_a(Administrador* administrador, Animal* animal) {
  administrador->fp_a = fopen(administrador->file_n_an, "a");

  if (!administrador->fp_a) {
    fprintf(stderr, "Sistema:\tNo se pudo abrir el archivo: %s\n", administrador->file_n_an);
    exit(1);
  }

  fprintf(administrador->fp_a, "%d,%d,%s,%s,%s\n", animal_id(animal), animal_bioma(animal),
          animal_fecha_nacimiento(animal), animal_nombre(animal), animal_especie(animal));

  fclose(administrador->fp_a);

  ++administrador->n_a;
}

/* Agrega el Bioma parámetro a la base de datos. */
void administrador_agrega_b(Administrador* administrador, Bioma* bioma) {
  administrador->fp_b = fopen(administrador->file_n_bi, "a");

  if (!administrador->fp_b) {
    fprintf(stderr, "Sistema:\tNo se pudo abrir el archivo: %s\n", administrador->file_n_bi);
    exit(1);
  }

  fprintf(administrador->fp_b, "%d,%s,%s\n", bioma_id(bioma), bioma_nombre(bioma),
          bioma_region(bioma));

  fclose(administrador->fp_b);

  ++administrador->n_b;
}

/* Agrega el Veterinario parámetro a la base de datos. */
void administrador_agrega_v(Administrador* administrador, Veterinario* veterinario) {
  administrador->fp_v = fopen(administrador->file_n_vet, "a");

  if (!administrador->fp_v) {
    fprintf(stderr, "Sistema:\tNo se pudo abrir el archivo: %s\n", administrador->file_n_vet);
    exit(1);
  }

  fprintf(administrador->fp_v, "%d,%d,%s,%d,%s,%s\n", veterinario_id(veterinario),
          veterinario_esp(veterinario), veterinario_nombre(veterinario),
          veterinario_jornada(veterinario), veterinario_correo(veterinario),
          veterinario_fecha_nacimiento(veterinario));

  fclose(administrador->fp_v);

  ++administrador->n_v;
}

/* Elimina la entidad parámetro de la base de datos. */
void administrador_elimina(Administrador* administrador, void* entidad);

/* Consulta la entidad parámetro de la base de datos. */
void administrador_consulta(Administrador* administrador, void* entidad);

/* Edita la entidad parámetro de la base de datos. */
void administrador_edita(Administrador* administrador, void* entidad);
