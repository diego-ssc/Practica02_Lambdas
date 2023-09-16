#include <stdlib.h>
#include <stdio.h>

#include "sistema.h"
#include "entidad.h"

#define NUMERO_ENTIDADES 3

/* Encapsula la función para eliminar. */
void eliminar(Administrador* administrador);

/* Encapsula la función para editar. */
void editar(Administrador* administrador);

int salir();

int agrega(enum Entidad , Administrador*);

int consulta(enum Entidad e, Administrador* administrador, int id);

/* Hilo de ejecución principal. */
int main(int argc, char** argv) {
  const char * archivos[] = {
    "animal.csv",
    "bioma.csv",
    "veterinario.csv"
  };
  Administrador* administrador = administrador_new(archivos,
                                                   NUMERO_ENTIDADES);


    
  do {
    char line[TAMANO_LINEA];
    int i;
    int  c = 0;
    while (!c) {
      printf("Ingrese el número de la operacion:\n"
             "AGREGAR   : 1\n"
             "ELIMINAR  : 2\n"
             "CONSULTAR : 3\n"
             "EDITAR    : 4\n"
             "SALIR     : 5\n");
      if (fgets(line, TAMANO_LINEA, stdin))
        if(1 == sscanf(line, "%d", &i))
          if (0 < i && i < 6)
            c =1;
    }

    switch (i){
      //AGREGAR
    case 1:
      c = 0;
      while (!c) {
        printf("Ingrese el número de la entidad para operar:\n"
               "ANIMAL      : 1\n"
               "BIOMA       : 2\n"
               "VETERINARIO : 3\n");
        if (fgets(line, TAMANO_LINEA, stdin))
          if(1 == sscanf(line, "%d", &i))
            if (0 < i && i < 4)
              c =1;
      }
      while (!agrega(i-1, administrador)) {
        if (salir())
          break;
      }
      i =0;
      break;

      // ELIMINAR
    case 2:
      eliminar(administrador);
      i =0;
      break;

      // CONSULTA
    case 3:
      c = 0;
      while (!c) {
        printf("Ingrese el número de la entidad para operar:\n"
               "ANIMAL      : 1\n"
               "BIOMA       : 2\n"
               "VETERINARIO : 3\n");
        if (fgets(line, TAMANO_LINEA, stdin))
          if(1 == sscanf(line, "%d", &i))
            if (0 < i)
              c = 1;
      }
      c = 0;
      int id_e;
      while (!c) {
        printf("Ingrese el id de la entidad a consultar:\n");
        if (fgets(line, TAMANO_LINEA, stdin)) 
          if(1 == sscanf(line, "%d", &id_e))
            if (0 < id_e)
              c = 1;
      }
      
      while (!consulta(i-1, administrador, id_e)) {
        if (salir())
          break;
      }
      i = 0;
      break;

      // EDITAR
    case 4:
      editar(administrador);
      i = 0;
      break;
    case 5:
      return 0;
    }
  }while (!salir());

  return 0;
}


/* Encapsula la función para eliminar. */
void eliminar(Administrador* administrador) {
  printf("Ingrese el número de la entidad:\n"
         "ANIMAL      : 1\n"
         "BIOMA       : 2\n"
         "VETERINARIO : 3\n");
  char linea[TAMANO_LINEA] = "\0";
  int i = 0;
  while (*(linea) == '\0')
    fgets(linea, TAMANO_LINEA, stdin);

  sscanf(linea, "%d", &i);
  while (!i || i > 3) {
    fprintf(stderr, "Sistema:\tOpción Inválida\n");
    while (*(linea) == '\0')
      fgets(linea, TAMANO_LINEA, stdin);

    sscanf(linea, "%d", &i);
  }

  /* Decidir sobre qué entidad se hará la operación. */
  switch (i) {

    /* Animal. */
  case 1:
    printf("Ingrese el identificador del animal a eliminar [máximo: %d].\n",
           administrador_animales(administrador)-1);

    *linea = '\0';
    while (*(linea) == '\0')
      fgets(linea, TAMANO_LINEA, stdin);

    sscanf(linea, "%d", &i);
    while (!i || i >= administrador_animales(administrador)) {
      while (*(linea) == '\0')
        fgets(linea, TAMANO_LINEA, stdin);

      sscanf(linea, "%d", &i);
    }

    administrador_elimina(administrador, i, ANIMAL);
    break;

    /* Bioma. */
  case 2:
    printf("Ingrese el identificador del bioma a eliminar [máximo: %d].\n",
           administrador_biomas(administrador)-1);

    *linea = '\0';
    while (*(linea) == '\0')
      fgets(linea, TAMANO_LINEA, stdin);

    sscanf(linea, "%d", &i);
    while (!i || i >= administrador_biomas(administrador)) {
      while (*(linea) == '\0')
        fgets(linea, TAMANO_LINEA, stdin);

      sscanf(linea, "%d", &i);
    }
    administrador_elimina(administrador, i, BIOMA);

    break;

    /* Veterinario. */
  case 3:
    printf("Ingrese el identificador del veterinario a eliminar [máximo: %d].\n",
           administrador_veterinarios(administrador)-1);

    *linea = '\0';
    while (*(linea) == '\0')
      fgets(linea, TAMANO_LINEA, stdin);

    sscanf(linea, "%d", &i);
    while (!i || i >= administrador_veterinarios(administrador)) {
      while (*(linea) == '\0')
        fgets(linea, TAMANO_LINEA, stdin);

      sscanf(linea, "%d", &i);
    }
    administrador_elimina(administrador, i, VETERINARIO);
    break;
  }
}

/* Encapsula la función para editar. */
void editar(Administrador* administrador) {
  printf("Ingrese el número de la entidad:\n"
         "ANIMAL      : 1\n"
         "BIOMA       : 2\n"
         "VETERINARIO : 3\n");
  char linea[TAMANO_LINEA] = "\0";
  int i = 0, id;

  while (*(linea) == '\0')
    fgets(linea, TAMANO_LINEA, stdin);

  sscanf(linea, "%d", &i);
  while (!i || i > 3) {
    fprintf(stderr, "Sistema:\tOpción Inválida\n");
    while (*(linea) == '\0')
      fgets(linea, TAMANO_LINEA, stdin);

    sscanf(linea, "%d", &i);
  }

  /* Decidir sobre qué entidad se hará la operación. */
  switch (i) {

    /* Animal. */
  case 1:
    printf("Ingrese el identificador del animal a editar [máximo: %d].\n",
           administrador_animales(administrador)-1);
    *linea = '\0';
    while (*(linea) == '\0')
      fgets(linea, TAMANO_LINEA, stdin);

    sscanf(linea, "%d", &i);
    while (!i || i >= administrador_animales(administrador)) {
      while (*(linea) == '\0')
        fgets(linea, TAMANO_LINEA, stdin);

      sscanf(linea, "%d", &i);
    }
    id = i;

    printf("Ingrese el identificador del atributo a editar.\n"
           "BIOMA               : 1\n"
           "FECHA DE NACIMIENTO : 2\n"
           "NOMBRE              : 3\n"
           "ESPECIE             : 4\n");

    i = 0;
    while (*(linea) == '\0')
      fgets(linea, TAMANO_LINEA, stdin);

    sscanf(linea, "%d", &i);
    while (!i || i > 4) {
      fprintf(stderr, "Sistema:\tOpción Inválida\n");

      while (*(linea) == '\0')
        fgets(linea, TAMANO_LINEA, stdin);

      sscanf(linea, "%d", &i);
    }

    int n_atr = i;

    /* Se registra el atributo a cambiar. */
    switch (i) {
      /* Bioma-Animal. */
    case 1:
      printf("Ingrese el bioma nuevo [número entero].\n");
      while (*(linea) == '\0')
        fgets(linea, TAMANO_LINEA, stdin);

      sscanf(linea, "%d", &i);
      administrador_edita(administrador, id, n_atr, (void*)&i, ANIMAL);
      break;
      /* Fecha Nacimiento. */
    case 2:
      printf("Ingrese la nueva fecha de nacimiento.\n");
      while (*(linea) == '\0')
        fgets(linea, TAMANO_LINEA, stdin);

      administrador_edita(administrador, id, n_atr, linea, ANIMAL);
      break;
      /* Nombre. */
    case 3:
      printf("Ingrese el nuevo nombre.\n");
      while (*(linea) == '\0')
        fgets(linea, TAMANO_LINEA, stdin);

      administrador_edita(administrador, id, n_atr, linea, ANIMAL);
      break;
      /* Especie. */
    case 4:
      printf("Ingrese la nueva especie.\n");
      while (*(linea) == '\0')
        fgets(linea, TAMANO_LINEA, stdin);

      administrador_edita(administrador, id, n_atr, linea, ANIMAL);
      break;
    }
    break;

    /* Bioma. */
  case 2:
    printf("Ingrese el identificador del bioma a editar [máximo: %d].\n",
           administrador_biomas(administrador)-1);
    *linea = '\0';
    while (*(linea) == '\0')
      fgets(linea, TAMANO_LINEA, stdin);

    sscanf(linea, "%d", &i);
    while (!i || i >= administrador_biomas(administrador)) {
      while (*(linea) == '\0')
        fgets(linea, TAMANO_LINEA, stdin);

      sscanf(linea, "%d", &i);
    }
    id = i;

    printf("Ingrese el identificador del atributo a editar.\n"
           "NOMBRE              : 1\n"
           "REGIÓN              : 2\n");

    i = 0;
    while (*(linea) == '\0')
      fgets(linea, TAMANO_LINEA, stdin);

    sscanf(linea, "%d", &i);
    while (!i || i > 2) {
      fprintf(stderr, "Sistema:\tOpción Inválida\n");

      while (*(linea) == '\0')
        fgets(linea, TAMANO_LINEA, stdin);

      sscanf(linea, "%d", &i);
    }

    n_atr = i;

    /* Se registra el atributo a cambiar. */
    switch (i) {
      /* Nombre. */
    case 1:
      printf("Ingrese el nuevo nombre.\n");
      while (*(linea) == '\0')
        fgets(linea, TAMANO_LINEA, stdin);

      administrador_edita(administrador, id, n_atr, linea, BIOMA);
      break;
      /* Región. */
    case 2:
      printf("Ingrese la nueva región.\n");
      while (*(linea) == '\0')
        fgets(linea, TAMANO_LINEA, stdin);

      administrador_edita(administrador, id, n_atr, linea, ANIMAL);
      break;
    }
    break;

    /* Veterinario. */
  case 3:
    printf("Ingrese el identificador del veterinario a editar [máximo: %d].\n",
           administrador_veterinarios(administrador)-1);
    *linea = '\0';
    while (*(linea) == '\0')
      fgets(linea, TAMANO_LINEA, stdin);

    sscanf(linea, "%d", &i);
    while (!i || i >= administrador_veterinarios(administrador)) {
      while (*(linea) == '\0')
        fgets(linea, TAMANO_LINEA, stdin);

      sscanf(linea, "%d", &i);
    }
    id = i;

    printf("Ingrese el identificador del atributo a editar.\n"
           "ESPECIALIDAD        : 1\n"
           "NOMBRE              : 2\n"
           "JORNADA             : 3\n"
           "CORREO ELECTRÓNICO  : 4\n"
           "FECHA NACIMIENTO    : 5\n");

    while (*(linea) == '\0')
      fgets(linea, TAMANO_LINEA, stdin);

    sscanf(linea, "%d", &i);
    while (!i || i > 5) {
      fprintf(stderr, "Sistema:\tOpción Inválida\n");

      while (*(linea) == '\0')
        fgets(linea, TAMANO_LINEA, stdin);

      sscanf(linea, "%d", &i);
    }

    n_atr = i;

    /* Se registra el atributo a cambiar. */
    switch (i) {
      /* Especialidad. */
    case 1:
      printf("Ingrese la nueva especialidad.\n");
      while (*(linea) == '\0')
        fgets(linea, TAMANO_LINEA, stdin);

      sscanf(linea, "%d", &i);

      administrador_edita(administrador, id, n_atr, (void*)&i, VETERINARIO);
      break;
      /* Nombre. */
    case 2:
      printf("Ingrese el nuevo nombre.\n");

      while (*(linea) == '\0')
        fgets(linea, TAMANO_LINEA, stdin);

      administrador_edita(administrador, id, n_atr, linea, VETERINARIO);
      break;
      /* Jornada */
    case 3:
      printf("Ingrese la nueva jornada.\n");
      while (*(linea) == '\0')
        fgets(linea, TAMANO_LINEA, stdin);

      sscanf(linea, "%d", &i);

      administrador_edita(administrador, id, n_atr, (void*)&i, VETERINARIO);
      break;
      /* Correo Electrónico. */
    case 4:
      printf("Ingrese el nuevo correo electrónico.\n");
      while (*(linea) == '\0')
        if (strstr(fgets(linea, TAMANO_LINEA, stdin) ? linea : "", "@") != 0)
          break;

      administrador_edita(administrador, id, n_atr, linea, VETERINARIO);
      break;
      /* Fecha de Nacimiento. */
    case 5:
      printf("Ingrese la nueva fecha de nacimiento.\n");

      while (*(linea) == '\0')
        fgets(linea, TAMANO_LINEA, stdin);

      administrador_edita(administrador, id, n_atr, linea, VETERINARIO);
      break;
    }
    break;
  }
}

int salir() {
  char line[TAMANO_LINEA];
  int i;
  printf("Salir?(0=no, 1=yes) :\n");
  if (!fgets(line, TAMANO_LINEA, stdin)) {
    printf("Error de input\n");
    return 0;
  }
  if (1 != sscanf(line, "%d", &i)){
    printf("Error de input\n");
    return 0;
  }
  if (i)
    return 1;
  return 0;
}

int agrega(enum Entidad e, Administrador* administrador) {
  char line[TAMANO_LINEA], nombre[TAMANO_NOMBRE], fecha[TAMANO_NOMBRE];
  int id;

  switch (e) {
  case ANIMAL :
    printf("Datos a ingresar (bioma (int), nombre, especie, fecha_nacimiento)\ningrese los datos separados por espacios.\n");
    if (!fgets(line, TAMANO_LINEA, stdin)) {
      printf("Error de input\n");
      return 0;
    }
    int bioma_id;
    char especie[TAMANO_NOMBRE];
    if (4 != sscanf(line, "%d %s %s %s", &bioma_id, nombre, especie, fecha)){
      printf("Error de input\n");
      return 0;
    }
    id = administrador_animales(administrador)+1;
    Animal* animal = animal_new(id, bioma_id, fecha, nombre, especie);
    printf("Animal(%d, %d, %s, %s, %s)\n", id, bioma_id, nombre, especie, fecha);
    administrador_agrega(administrador, animal, ANIMAL);
    return 1;
    break;
  case BIOMA :
    printf("Datos a ingresar (nombre, region)\ningrese los datos separados por espacios.\n");
    if (!fgets(line, TAMANO_LINEA, stdin)) {
      printf("Error de input\n");
      return 0;
    }
    char nombre[30], region[30];
    if (2 != sscanf(line, "%s %s", nombre, region)){
      printf("Error de input\n");
      return 0;
    }
    id = administrador_biomas(administrador)+1;
    Bioma* bioma = bioma_new(nombre, region, id);
    printf("Bioma(%d, %s, %s)\n", id,  nombre, region);
    administrador_agrega(administrador, bioma, BIOMA);
    return 1;
    break;
  case VETERINARIO:
    printf("Datos a ingresar (nombre, especialidad (int), jornada (0:medio tiempo, 1:tiempo completo), correo, fecha_nacimiento)\ningrese los datos separados por espacios\n");
    if (!fgets(line, TAMANO_LINEA, stdin)) {
      printf("Error de input\n");
      return 0;
    }
    int jornada, esp;
    char  correo[TAMANO_NOMBRE];
    if (5 != sscanf(line, "%s %d %d %s %s", nombre, &esp, &jornada, correo, fecha)){
      printf("Error de input\n");
      return 0;
    }
    if (!(jornada == 0 || jornada == 1)) {
      printf("Error de input\n");
      return 0;
    }
    id = administrador_veterinarios(administrador)+1;
    Veterinario* vet = veterinario_new(id, esp, nombre, jornada, correo, fecha);
    printf("Veterinario(%d, %s, %d, %d, %s, %s )\n", id,  nombre, esp, jornada, correo, fecha);
    administrador_agrega(administrador, vet, VETERINARIO);
    return 1;
    break;
  default:
    printf("Error de input\n");
    return 0;
  }
}



int consulta(enum Entidad e, Administrador* administrador, int id) {
  
  switch (e) {
  case ANIMAL:
    Animal* animal = administrador_consulta(administrador, id, e);

    if (animal){
      printf("Animal(%d, %d, %s, %s, %s)\n",
           animal_id(animal),
           animal_bioma(animal),
           animal_nombre(animal),
           animal_especie(animal),
           animal_fecha_nacimiento(animal));
      return 1;
    }

      break;
  case BIOMA:
    Bioma* bioma = administrador_consulta(administrador, id, e);
    if (bioma) {
      printf("Bioma(%d, %s, %s)\n",
           bioma_id(bioma),
           bioma_nombre(bioma),
           bioma_region(bioma));
      return 1;
    }

    break;
  case VETERINARIO:
    Veterinario* vet= administrador_consulta(administrador, id, e);

    if (vet) {
      printf("Veterinario(%d, %d, %s, %d, %s, %s)\n",
             veterinario_id(vet),
             veterinario_esp(vet),
             veterinario_nombre(vet),
             veterinario_jornada(vet),
             veterinario_correo(vet),
             veterinario_fecha_nacimiento(vet));
      return 1;
    }
    break;
  default:
    printf("Error de input\n");
    return 0;
  }
  printf("Error de input\n");
  return 0;
}
