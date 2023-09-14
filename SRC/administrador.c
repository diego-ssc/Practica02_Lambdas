#include <sys/mman.h>
#include <sys/stat.h>

#include "administrador.h"
#include "animal.h"
#include "bioma.h"
#include "sistema.h"
#include "veterinario.h"
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

  GTree tabla_animales;

  GTree tabla_biomas;

  GTree tabla_veterinarios;
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

  administrador->tabla_animales = g_tree_new();
  administrador->tabla_biomas = g_tree_new();
  administrador->tabla_veterinarios = g_tree_new();

  return administrador;
}

/* Libera la memoria usada por el Administrador. */
void administrador_free(Administrador* administrador) {
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
  if(strcmp(entidad, ENTIDAD_VETERINARIO)==0){
    Veterinario* veterinario=administrador_cons_veterinario(administrador);
    g_tree_insert(tabla_veterinario, veterinario_id(veterinario), veterinario );
  }
  else if(strcmp(entidad, ENTIDAD_BIOMA)==0){
    Bioma* bioma= administrador_cons_bioma(administrador);
    g_tree_insert(tabla_bioma, bioma_id(bioma), bioma);
  }
  else if(strcmp(entidad, ENTIDAD_ANIMAL)==0){
    Animal* animal= administrador_cons_animal(administrador);
    g_tree_insert(tabla_animal, animal_id(animal), animal);
  }
}

Animal* administrador_cons_animal(Administrador* administrador){
  char* nombre, especie, sexo, t_alim, ind_med, fecha;
  float peso, altura;
  int n_jaula, bioma;
  printf("Nombre de animal: ");
  scanf("%s", nombre);
  printf("Nommbre de especie: ");
  scanf("%s", especie);
  printf("Peso: ");
  scanf("%f", peso);
  printf("Altura");
  scanf("%f", altura);
  printf("Sexo: ");
  scanf("%s", sexo);
  printf("Tipo de alimentacion: ");
  scanf("%s", t_alim);
  printf("Indicaciones medicas: ");
  scanf("%s", ind_med);
  printf("Bioma:");
  scanf("%d", bioma);
  printf("Fecha de nacimiento: ");
  printf("%s", fecha);
  Animal* animal=animal_new(administrador->n_a++, bioma, &fecha, nombre, &especie, peso,
                            altura, &sexo, n_jaula, &t_alim, &ind_med);

  return animal;
}

Bioma* administrador_cons_bioma(Administrador* administrador){
  char* nombre, region, servicios;
  int n_jaula, n_cuidadores, n_veterinarios, n_animales;
  printf("Nombre del bioma: ");
  scanf("%s", nombre);
  printf("Nommbre de ña region: ");
  scanf("%s", region);
  printf("Numero de jaulas: ");
  scanf("%d", n_jaula);
  printf("Numero de cuidadores: ");
  scanf("%d", n_cuidadores);
  printf("Numero de veterinarios: ");
  scanf("%d", n_veterinarios);
  printf("Numero de animales: ");
  scanf("%d", n_animales);
  printf("Servicios: ");
  scanf("%s", servicios);

  Bioma* bioma= bioma_new(nombre, &region, administrador->n_b, n_jaula, n_cuidadores,
                          n_veterinarios, n_animales, &servicios);
  return bioma;
}

Veterinario* administrador_cons_veterinario(Administrador* administrador){

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

/* Elimina la entidad parámetro de la base de datos. */
void administrador_elimina(Administrador* administrador, void* entidad);

/* Devuelve el índice del inicio de la línea donde se encuentra la entidad
   buscada. */
static int busqueda_binaria_map(char* map, int i) {
  i /= 2;
  int j = i;

  while (1) {
    while (*(map + j) != '\n')
      j++;

    if (atoi(map + j + 1) == i)
      return j + 1;
    if (atoi(map + j + 1) < i)
      j /= 2;
    else
      j += j/2;
  }

  return j + 1;
}

/* Consulta el Animal de la base de datos. */
Animal* administrador_consulta_a(Administrador* administrador, Animal* animal) {
  if (!animal) {
    fprintf(stderr, "Sistema:\tAnimal no válido\n");
    return 0;
  }

  /* Información del archivo. */
  struct stat s;

  /* El archivo mapeado. */
  char* m;

  administrador->fp_a = fopen(administrador->file_n_an, "r");

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

  /* Se supone que los índices son ontinuos. */
  if (animal_id(animal) >= s.st_size) {
    fprintf(stderr, "Sistema:\tPosici\'on no v\'alida\n");
    return 0;
  }

  /* *(m + s.st_size) */
  return 0;
}

/* Consulta el Bioma de la base de datos. */
void administrador_consulta_b(Administrador* administrador, Bioma* bioma);

/* Consulta el Veterinario de la base de datos. */
void administrador_consulta_v(Administrador* administrador, Veterinario* veterinario);

/* Edita la entidad parámetro de la base de datos. */
void administrador_edita(Administrador* administrador, void* entidad);
