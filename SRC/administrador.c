#include <sys/mman.h>
#include <sys/stat.h>

#include "administrador.h"
#include "entidad.h"

/* La estructura Administrador. */
struct Administrador_ {
  /* El archivo. */
  FILE* fp;
  /* El número de entidades. */
  int n;
  /* Los archivos. */
  char** archivos;
  /* Arreglo del número de entidades. */
  int* cantidades;
};

/* Construye un Administrador. */
Administrador* administrador_new(const char** archivos, int n) {
  /* Reservación en heap. */
  Administrador* administrador = malloc(sizeof(struct Administrador_));
  administrador->archivos      = malloc(sizeof(char*)*n);
  administrador->cantidades    = calloc(1, sizeof(int)*n);
  administrador->n             = n;

  /* Inicialización del heap. */
  while (n--)
    *(administrador->archivos + administrador->n-(n+1)) =
      malloc(sizeof(char)*(strnlen(*(archivos + administrador->n-(n+1)),
                                   TAMANO_NOMBRE)+1));

  n = administrador->n;
  while (n--)
    strcpy(*(administrador->archivos + administrador->n-(n+1)),
           (*(archivos + administrador->n-(n+1))));

  /* Se comenzará con índice 1. */
  n = administrador->n;
  while (n--)
    ++*(administrador->cantidades + administrador->n-(n+1));

  return administrador;
}

/* Libera la memoria usada por el Administrador. */
void administrador_free(Administrador* administrador) {
  if (administrador->archivos) {
    int n = administrador->n;
    while (n--)
      free(*(administrador->archivos + administrador->n-(n+1)));
    free (administrador->archivos);
  }

  if (administrador->cantidades)
    free(administrador->cantidades);
  free(administrador);
}

/* Agrega el Animal parámetro administrador->n la base de datos. */
void administrador_agrega(Administrador* administrador, void* entidad, enum Entidad e) {
  if (!entidad) {
    fprintf(stderr, "Sistema:\tEntidad no válida\n");
    return;
  }
  administrador->fp = fopen(*(administrador->archivos + e), "a");

  if (!administrador->fp) {
    fprintf(stderr, "Sistema:\tNo se pudo abrir el archivo: %s\n",
            *(administrador->archivos + e));
    exit(1);
  }

  switch (e) {
  case ANIMAL:
    Animal* animal = (Animal*)entidad;
    fprintf(administrador->fp, "%d,%d,%s,%s,%s\n", animal_id(animal), animal_bioma(animal),
            animal_fecha_nacimiento(animal), animal_nombre(animal), animal_especie(animal));
    break;
  case BIOMA:
    Bioma* bioma = (Bioma*)entidad;
    fprintf(administrador->fp, "%d,%s,%s\n", bioma_id(bioma), bioma_nombre(bioma),
            bioma_region(bioma));
    break;
  case VETERINARIO:
    Veterinario* veterinario = (Veterinario*)entidad;
    fprintf(administrador->fp, "%d,%d,%s,%d,%s,%s\n", veterinario_id(veterinario),
            veterinario_esp(veterinario), veterinario_nombre(veterinario),
            veterinario_jornada(veterinario), veterinario_correo(veterinario),
            veterinario_fecha_nacimiento(veterinario));
    break;
  }

  fclose(administrador->fp);

  ++*(administrador->cantidades + e);
}

/* Elimina el animal parámetro de la base de datos. */
void administrador_elimina(Administrador* administrador, void* entidad, enum Entidad e);

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

/* Consulta la entidad parámetro de la base de datos. */
void* administrador_consulta(Administrador* administrador, int id,
                             enum Entidad e);


/* Edita la entidad parámetro de la base de datos. */
void administrador_edita(Administrador* administrador, void* entidad, enum Entidad e);
