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

  /*Contamos el numero de entidades ya existentes en los archivos*/
   n = administrador->n;
  char buff[101];
  while (n--) {
    int i = 0;
    administrador->fp = fopen(*(administrador->archivos + n), "r");
    while (fgets(buff, TAMANO_LINEA, administrador->fp)) {
      i++;
    }
    *(administrador->cantidades + n) = i+1;
    printf("%d:%d\n",n, i);
    fclose(administrador->fp);
  }

  
    
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

/* Consulta el Animal de la base de datos. */
void* administrador_consulta(Administrador* administrador, int id, enum Entidad entidad) {
  
  /* Abrimos el archivo correspondiente */
  char* archivo = *(administrador->archivos + entidad);
  administrador->fp = fopen(archivo, "r");
  printf("%d\n", *(administrador->cantidades+entidad));
  if (id > *(administrador->cantidades+entidad)) {
    return 0;
  }
   
  /* Información del archivo. */
  struct stat s;

  /* El archivo mapeado. */
  char* m;

  if (!administrador->fp) {
    fprintf(stderr, "Sistema:\tNo se pudo abrir el archivo: %s\n",
            archivo);
    return 0;
  }
  
  if (0 > fstat(fileno(administrador->fp), &s)) {
    fprintf(stderr, "Sistema:\tNo se pudo obtener el tamaño del archivo: %s\n",
            archivo);
    return 0;
  }

  m = mmap(0, s.st_size, PROT_READ, MAP_PRIVATE, fileno(administrador->fp), 0);

  if (MAP_FAILED == m) {
    fprintf(stderr, "Sistema:\tError al mapear: %s\n", archivo);
    return 0;
  }

  printf("%d\n", id);
  int b = busqueda_binaria_map(m, id, s.st_size);
  printf("%d\n", b);
  printf("There: %c%c%c%c%c\n", *(m+b), *(m+b+1), *(m+b+2),
         *(m+b+3), *(m+b+4));

  /* Cantidad de chars en la linea */
  int i = 0;
  while (*(m+b+i) != '\n') {
    if ((m+b+i) == (m+s.st_size-1))
      break;
    i++;
  }
 
  printf("%d\n", i);
  
  char* datos = malloc((i+1)*sizeof(char));
  
  for (int j = 0; j < i; j++ ) {
    datos[j] = *(m+b+j);
  }
  datos[i]= '\0';
  printf("Datos: %s\n", datos);
  switch (entidad) {
  case ANIMAL:
    return animal_new(atoi(strtok(datos, ",")),
                      atoi(strtok(NULL, ",")),
                      strtok(NULL, ","),
                      strtok(NULL, ","),
                      strtok(NULL, ","));

    break;
    
  case BIOMA:
    char* p;
    int id;
    char* nombre;
    char* region;
    p = strtok(datos, ",");
    
    if (!p) {
      fprintf(stderr, "Sistema1:\tError al leer datos en el archivo: %s\n", archivo);
      return 0;
    }
      
    id = atoi(p);
    p = strtok(NULL, ",");
    if (!p) {
      fprintf(stderr, "Sistema1:\tError al leer datos en el archivo: %s\n", archivo);
      return 0;
    }
    nombre = p;
    printf("Nombre: %s\n", nombre);
    p = strtok(NULL, ",");
   if (!p) {
      fprintf(stderr, "Sistema1:\tError al leer datos en el archivo: %s\n", archivo);
      return 0;
    }
    region = p;
    
    return bioma_new(nombre,
                     region,
                     id);
    break;
    
  case VETERINARIO:
    return veterinario_new(atoi(strtok(datos, ",")),
                       atoi(strtok(NULL, ",")),
                       strtok(NULL, ","),
                       atoi(strtok(NULL, ",")),
                       strtok(NULL, ","),
                       strtok(NULL, ","));
    break;
  default:
    fprintf(stderr, "Sistema:\tEntidad no v\'alida.");
  }

  free(datos);
  /*Cerramos el archivo*/
  fclose(administrador->fp);
  
  return 0;
}


/* Edita la entidad parámetro de la base de datos. */
void administrador_edita(Administrador* administrador, void* entidad, enum Entidad e);
