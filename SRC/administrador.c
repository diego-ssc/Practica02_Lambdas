#include <sys/mman.h>
#include <sys/stat.h>

#include "administrador.h"
#include "entidades.h"

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

  return administrador;
}

/* Libera la memoria usada por el Administrador. */
void administrador_free(Administrador* administrador) {
  free(administrador);
}

/* Agrega el Animal parámetro a la base de datos. */
void administrador_agrega_a(Administrador* administrador, Animal* animal) {
  if (!animal) {
    fprintf(stderr, "Sistema:\tAnimal no válido\n");
    return;
  }
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
  if (!bioma) {
    fprintf(stderr, "Sistema:\tBioma no válido\n");
    return;
  }
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
  if (!veterinario) {
    fprintf(stderr, "Sistema:\tVeterinario no válido\n");
    return;
  }
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

/* Elimina el animal parámetro de la base de datos. */
void administrador_elimina_a(Administrador* administrador, void* entidad);

/* Devuelve el índice del inicio de la línea donde se encuentra la entidad
   buscada. */
static int busqueda_binaria_map(char* map, int i, size_t file_size) {
  int j = file_size/2;

  while (1) {
    while (*(map + j) != '\n' && j > 0) {
      if (j == 0)
        break;
      j--;
    }

    j = j ? j : -1;
    if (atoi(map + j+1) == i)
      return j+1;
    if (atoi(map + j+1) > i)
      j /= 2;
    else
      j += TAMANO_PROMEDIO_LINEA+j/2;
  }

  return j+1;
}

/* Consulta el Animal de la base de datos. */
Animal* administrador_consulta_a(Administrador* administrador, int id) {
  if (id > administrador->n_a) {
    fprintf(stderr, "Sistema:\tAnimal no válido\n");
    return 0;
  }

  /* Información del archivo. */
  struct stat s;

  /* El archivo mapeado. */
  char* m;

  if (!administrador->fp_a) {
    fprintf(stderr, "Sistema:\tNo se pudo abrir el archivo: %s\n",
            administrador->file_n_an);
    return 0;
  }

  if (0 > fstat(fileno(administrador->fp_a), &s)) {
    fprintf(stderr, "Sistema:\tNo se pudo obtener el tamaño del archivo: %s\n",
            administrador->file_n_an);
    return 0;
  }

  m = mmap(0, s.st_size, PROT_READ, MAP_PRIVATE, fileno(administrador->fp_a), 0);

  if (MAP_FAILED == m) {
    fprintf(stderr, "Sistema:\tError al mapear: %s\n", administrador->file_n_an);
    return 0;
  }

  /* Se supone que los índices son continuos. */
  if (id >= s.st_size) {
    fprintf(stderr, "Sistema:\tPosici\'on no v\'alida\n");
    return 0;
  }

  int b = busqueda_binaria_map(m, id, s.st_size);
  printf("Hello:%d\n", b);
  printf("There: %c%c%c%c%c\n", *(m+b), *(m+b+1), *(m+b+2),
         *(m+b+3), *(m+b+4));

  /* *(m + s.st_size) */
  return 0;
}

/* Consulta el Bioma de la base de datos. */
Bioma* administrador_consulta_b(Administrador* administrador, int id) {
  if (id > administrador->n_b) {
    fprintf(stderr, "Sistema:\tBioma no válido\n");
    return 0;
  }

  /* Información del archivo. */
  struct stat s;

  /* El archivo mapeado. */
  char* m;

  administrador->fp_b = fopen(administrador->file_n_bi, "r");

  if (!administrador->fp_b) {
    fprintf(stderr, "Sistema:\tNo se pudo abrir el archivo: %s\n",
            administrador->file_n_bi);
    return 0;
  }

  if (0 > fstat(fileno(administrador->fp_b), &s)) {
    fprintf(stderr, "Sistema:\tNo se pudo obtener el tamaño del archivo: %s\n",
            administrador->file_n_bi);
    return 0;
  }

  m = mmap(0, s.st_size, PROT_READ, MAP_PRIVATE, fileno(administrador->fp_b), 0);

  if (MAP_FAILED == m) {
    fprintf(stderr, "Sistema:\tError al mapear: %s\n", administrador->file_n_bi);
    return 0;
  }
  /* Se supone que los índices son continuos. */
  if (id >= s.st_size) {
    fprintf(stderr, "Sistema:\tPosici\'on no v\'alida\n");
    return 0;
  }

  int b = busqueda_binaria_map(m, id, s.st_size);
  printf("Hello:%d\n", b);

  return 0;
}

/* Consulta el Veterinario de la base de datos. */
Veterinario* administrador_consulta_v(Administrador* administrador, int id);

/* Para consulta, recibir solo id y archivo: tamano promedio de linea cambia. */

/* Edita la entidad parámetro de la base de datos. */
void administrador_edita(Administrador* administrador, void* entidad);
