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

    *(administrador->cantidades + n) = i;
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

/* Devuelve el número de animales. */
int administrador_animales(Administrador* administrador) {
  return *(administrador->cantidades + ANIMAL);
}

/* Devuelve el número de biomas. */
int administrador_biomas(Administrador* administrador) {
  return *(administrador->cantidades + BIOMA);
}

/* Devuelve el número de veterinarios. */
int administrador_veterinarios(Administrador* administrador) {
  return *(administrador->cantidades + VETERINARIO);
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
void administrador_elimina(Administrador* administrador, int id, enum Entidad e) {
  if (id > *(administrador->cantidades + e)) {
    fprintf(stderr, "Sistema:\tEntidad no válida\n");
    return;
  }
  administrador->fp = fopen(*(administrador->archivos + e), "r");

  if (!administrador->fp) {
    fprintf(stderr, "Sistema:\tNo se pudo abrir el archivo: %s\n",
            *(administrador->archivos + e));
    exit(1);
  }

  char s[TAMANO_LINEA];
  int i = 0, j, eliminado = 0, a;

  switch (e) {
  case ANIMAL:
    Animal** animales = malloc(sizeof(Animal*)*(*(administrador->cantidades + ANIMAL)));
    a = *(administrador->cantidades + ANIMAL);
    while (!feof(administrador->fp) && a--) {
      fgets(s, TAMANO_LINEA, administrador->fp);

      /* Análisis de Propiedades. */
      int id    = atoi(strtok(s, ",\n"));
      int bioma = atoi(strtok(0, ",\n"));
      char* f_n = strtok(0, ",\n");
      char* n   = strtok(0, ",\n");
      char* e   = strtok(0, ",\n");

      *(animales + i) = animal_new(id, bioma, f_n, n, e);
      i++;
    }

    fclose(administrador->fp);

    administrador->fp = fopen(*(administrador->archivos + e), "w");
    j = i;
    while (j--) {
      Animal* animal = *(animales + i - (j+1));
      if (id == animal_id(animal)) {
        eliminado = 1;
        continue;
      }

      fprintf(administrador->fp, "%d,%d,%s,%s,%s\n",
              eliminado ? animal_id(animal) - 1 : animal_id(animal),
              animal_bioma(animal), animal_fecha_nacimiento(animal),
              animal_nombre(animal), animal_especie(animal));
    }

    fclose(administrador->fp);

    j = i;
    while (j--)
      animal_free(*(animales + i - (j+1)));
    free(animales);
    break;
  case BIOMA:
    Bioma** biomas = malloc(sizeof(Bioma*)*(*(administrador->cantidades + BIOMA)));
    a = *(administrador->cantidades + BIOMA);
    while (!feof(administrador->fp) && a--) {
      fgets(s, TAMANO_LINEA, administrador->fp);

      /* Análisis de Propiedades. */
      int id    = atoi(strtok(s, ",\n"));
      char* n   = strtok(0, ",\n");
      char* r   = strtok(0, ",\n");

      *(biomas + i) = bioma_new(n, r, id);
      i++;
    }

    fclose(administrador->fp);

    administrador->fp = fopen(*(administrador->archivos + e), "w");
    j = i;
    while (j--) {
      Bioma* bioma = *(biomas + i - (j+1));
      if (id == bioma_id(bioma)) {
        eliminado = 1;
        continue;
      }

      fprintf(administrador->fp, "%d,%s,%s\n",
              eliminado ? bioma_id(bioma) - 1 : bioma_id(bioma),
              bioma_nombre(bioma), bioma_region(bioma));
    }

    fclose(administrador->fp);

    j = i;
    while (j--)
      bioma_free(*(biomas + i - (j+1)));

    free(biomas);
    break;
  case VETERINARIO:
    Veterinario** veterinarios = malloc(sizeof(Veterinario*)*
                                        (*(administrador->cantidades + VETERINARIO)));
    a = *(administrador->cantidades + VETERINARIO);
    while (!feof(administrador->fp) && a--) {
      fgets(s, TAMANO_LINEA, administrador->fp);

      /* Análisis de Propiedades. */
      int id     = atoi(strtok(s, ",\n"));
      int esp    = atoi(strtok(0, ",\n"));
      char* n    = strtok(0, ",\n");
      int jr     = atoi(strtok(0, ",\n"));
      char* c_e  = strtok(0, ",\n");
      char* f_n  = strtok(0, ",\n");

      *(veterinarios + i) = veterinario_new(id, esp, n, jr, c_e, f_n);
      i++;
    }

    fclose(administrador->fp);

    administrador->fp = fopen(*(administrador->archivos + e), "w");
    j = i;
    while (j--) {
      Veterinario* veterinario = *(veterinarios + i - (j+1));
      if (id == veterinario_id(veterinario)) {
        eliminado = 1;
        continue;
      }

      fprintf(administrador->fp, "%d,%d,%s,%d,%s,%s\n",
              eliminado ? veterinario_id(veterinario) - 1 :
              veterinario_id(veterinario), veterinario_esp(veterinario),
              veterinario_nombre(veterinario), veterinario_jornada(veterinario),
              veterinario_correo(veterinario), veterinario_fecha_nacimiento(veterinario));
    }

    fclose(administrador->fp);

    j = i;
    while (j--)
      veterinario_free(*(veterinarios + i - (j+1)));
    free(veterinarios);
    break;
  }

  --*(administrador->cantidades + e);
}


/* Consulta el Animal de la base de datos. */
void* administrador_consulta(Administrador* administrador, int id, enum Entidad entidad) {
  /* Abrimos el archivo correspondiente */
  char* archivo = *(administrador->archivos + entidad);
  administrador->fp = fopen(archivo, "r");
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

  char datos[TAMANO_LINEA];

  while(!feof(administrador->fp)) {
    if(fgets(datos, TAMANO_LINEA, administrador->fp)) {
      if (atoi(datos) == id)
        break;
    }
  }

  int ide;
  char* nombre;
  char* fecha;
  switch (entidad) {
  case ANIMAL:
    ide = atoi(strtok(datos, ",\n"));
    int bioma = atoi(strtok(NULL, ",\n"));
    fecha = strtok(NULL, ",\n");
    nombre = strtok(NULL, ",\n");
    char* especie = strtok(NULL, "\n");
    return animal_new(ide, bioma, fecha, nombre, especie);
    break;

  case BIOMA:
    char* p;
    char* region;
    p = strtok(datos, ",\n");

    if (!p) {
      fprintf(stderr, "Sistema1:\tError al leer datos en el archivo: %s\n", archivo);
      return 0;
    }

    ide = atoi(p);
    p = strtok(NULL, ",\n");
    if (!p) {
      fprintf(stderr, "Sistema1:\tError al leer datos en el archivo: %s\n", archivo);
      return 0;
    }

    nombre = p;
    p = strtok(NULL, ",\n");
    if (!p) {
      fprintf(stderr, "Sistema1:\tError al leer datos en el archivo: %s\n", archivo);
      return 0;
    }
    region = p;

    return bioma_new(nombre,
                     region,
                     ide);
    break;

  case VETERINARIO:
    ide = atoi(strtok(datos, ",\n"));
    int esp = atoi(strtok(NULL, ",\n"));
    nombre = strtok(NULL, ",\n");
    int jornada = atoi(strtok(NULL, ",\n"));
    char* correo = strtok(NULL, ",\n");
    fecha = strtok(NULL, ",\n");
    return veterinario_new(ide, esp, nombre, jornada, correo, fecha);
    break;
  default:
    fprintf(stderr, "Sistema:\tEntidad no v\'alida.");
  }

  //free(datos);
  /*Cerramos el archivo*/
  fclose(administrador->fp);

  return 0;
}


/* Edita la entidad parámetro de la base de datos. */
void administrador_edita(Administrador* administrador, int id, int n_a, void* atributo, enum Entidad e) {
  administrador->fp = fopen(*(administrador->archivos + e), "r");

  if (!administrador->fp) {
    fprintf(stderr, "Sistema:\tNo se pudo abrir el archivo: %s\n",
            *(administrador->archivos + e));
    exit(1);
  }

  char s[TAMANO_LINEA];
  int i = 0, j, a;

  switch (e) {
  case ANIMAL:
    if (n_a > 4 || !n_a) {
      fprintf(stderr, "Sistema:\tAtributo inválido\n");
      fclose(administrador->fp);
      return;
    }
    Animal** animales = malloc(sizeof(Animal*)*(*(administrador->cantidades + ANIMAL)));
    a = *(administrador->cantidades + ANIMAL);
    while (!feof(administrador->fp) && a--) {
      fgets(s, TAMANO_LINEA, administrador->fp);

      /* Análisis de Propiedades. */
      int id    = atoi(strtok(s, ",\n"));
      int bioma = atoi(strtok(0, ",\n"));
      char* f_n = strtok(0, ",\n");
      char* n   = strtok(0, ",\n");
      char* e   = strtok(0, ",\n");
      printf("EEEEE: %s\n", e);
      switch (n_a) {
      case 1:
        bioma = *((int*)atributo);
        break;
      case 2:
        f_n = (char*)atributo;
        break;
      case 3:
        n = (char*)atributo;
        break;
      case 4:
        e = (char*)atributo;
        break;
      default:
        fprintf(stderr, "Sistema:\tAtributo inválido\n");
        fclose(administrador->fp);
        return;
      }

     
      *(animales + i) = animal_new(id, bioma, f_n, n, e);
      i++;
    }

    fclose(administrador->fp);

    administrador->fp = fopen(*(administrador->archivos + e), "w");
    j = i;
    while (j--) {
      Animal* animal = *(animales + i - (j+1));
      fprintf(administrador->fp, "%d,%d,%s,%s,%s\n",
              animal_id(animal),
              animal_bioma(animal), animal_fecha_nacimiento(animal),
              animal_nombre(animal), animal_especie(animal));
    }

    fclose(administrador->fp);

    j = i;
    while (j--)
      animal_free(*(animales + i - (j+1)));
    free(animales);
    break;
  case BIOMA:
    if (n_a > 2 || !n_a) {
      fprintf(stderr, "Sistema:\tAtributo inválido\n");
      fclose(administrador->fp);
      return;
    }
    Bioma** biomas = malloc(sizeof(Bioma*)*(*(administrador->cantidades + BIOMA)));
    a = *(administrador->cantidades + BIOMA);
    while (!feof(administrador->fp) && a--) {
      fgets(s, TAMANO_LINEA, administrador->fp);

      /* Análisis de Propiedades. */
      int id    = atoi(strtok(s, ",\n"));
      char* n   = strtok(0, ",\n");
      char* r   = strtok(0, ",\n");

      switch (n_a) {
      case 1:
        n = (char*)atributo;
        break;
      case 2:
        r = (char*)atributo;
        break;
      default:
        fprintf(stderr, "Sistema:\tAtributo inválido\n");
        fclose(administrador->fp);
        return;
      }

      *(biomas + i) = bioma_new(n, r, id);
      i++;
    }

    fclose(administrador->fp);

    administrador->fp = fopen(*(administrador->archivos + e), "w");
    j = i;
    while (j--) {
      Bioma* bioma = *(biomas + i - (j+1));
      fprintf(administrador->fp, "%d,%s,%s\n",
              bioma_id(bioma),
              bioma_nombre(bioma), bioma_region(bioma));
    }

    fclose(administrador->fp);

    j = i;
    while (j--)
      bioma_free(*(biomas + i - (j+1)));
    free(biomas);
    break;
  case VETERINARIO:
    if (n_a > 5 || !n_a) {
      fprintf(stderr, "Sistema:\tAtributo inválido\n");
      fclose(administrador->fp);
      return;
    }
    Veterinario** veterinarios = malloc(sizeof(Veterinario*)*
                                        (*(administrador->cantidades + VETERINARIO)));
    a = *(administrador->cantidades + VETERINARIO);
    while (!feof(administrador->fp) && a--) {
      fgets(s, TAMANO_LINEA, administrador->fp);

      /* Análisis de Propiedades. */
      int id     = atoi(strtok(s, ",\n"));
      int esp    = atoi(strtok(0, ",\n"));
      char* n    = strtok(0, ",\n");
      int jr     = atoi(strtok(0, ",\n"));
      char* c_e  = strtok(0, ",\n");
      char* f_n  = strtok(0, ",\n");

      switch (n_a) {
      case 1:
        esp = *(int*)atributo;
        break;
      case 2:
        n = (char*)atributo;
        break;
      case 3:
        jr = *(int*)atributo;
        break;
      case 4:
        c_e = (char*)atributo;
        break;
      case 5:
        f_n = (char*)atributo;
        break;
      default:
        fprintf(stderr, "Sistema:\tAtributo inválido\n");
        fclose(administrador->fp);
        return;
      }

      *(veterinarios + i) = veterinario_new(id, esp, n, jr, c_e, f_n);
      i++;
    }

    fclose(administrador->fp);

    administrador->fp = fopen(*(administrador->archivos + e), "w");
    j = i;
    while (j--) {
      Veterinario* veterinario = *(veterinarios + i - (j+1));
      fprintf(administrador->fp, "%d,%d,%s,%d,%s,%s\n",
              veterinario_id(veterinario), veterinario_esp(veterinario),
              veterinario_nombre(veterinario), veterinario_jornada(veterinario),
              veterinario_correo(veterinario), veterinario_fecha_nacimiento(veterinario));
    }

    j = i;
    while (j--)
      veterinario_free(*(veterinarios + i - (j+1)));
    free(veterinarios);
    break;
  }
}
