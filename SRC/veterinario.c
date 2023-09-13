#include "veterinario.h"

/* La estructura Veterinario. */
struct Veterinario_ {
  /* El identificador. */
  int id;
  /* La especialidad. */
  int esp;
  /* El nombre. */
  char* nombre;
  /* La jornada. */
  int jornada;
  /* El correo electrónico. */
  char* correo;
  /* La fecha de nacimiento. */
  char* fecha_nacimiento;
};

/* Los tipos de jornada. */
enum {
  MEDIO_TIEMPO = 0,
  TIEMPO_COMPLETO = 1
};

/**
 * Crea un nuevo veterinario.
 * @param id; el número de cuenta.
 * @param esp la especialidad.
 * @param nombre el nombre.
 * @param jornada la jornada.
 * @param correo el correo electrónico.
 * @param fecha_nacimiento la fecha de nacimiento.
 */
Veterinario* veterinario_new(int id, int esp, char* nombre, int jornada,
                             char* correo, char* fecha_nacimiento) {
  /* Reservación en el heap. */
  Veterinario* veterinario = malloc(sizeof(struct Veterinario_));

  /* Inicialización del heap. */
  veterinario->id      = id;
  veterinario->esp     = esp;
  veterinario->jornada = jornada;

  veterinario->nombre           = malloc(sizeof(char)*
                                         (strnlen(nombre,
                                                  TAMANO_NOMBRE)+1));
  veterinario->correo           = malloc(sizeof(char)*
                                         (strnlen(correo,
                                                  TAMANO_NOMBRE)+1));
  veterinario->fecha_nacimiento = malloc(sizeof(char)*
                                         (strnlen(fecha_nacimiento,
                                                  TAMANO_NOMBRE)+1));
  strcpy(veterinario->nombre, nombre);
  strcpy(veterinario->correo, correo);
  strcpy(veterinario->fecha_nacimiento, fecha_nacimiento);

  return veterinario;
}

/**
 * Libera la memoria usada por el Veterinario.
 * @param veterinario el veterinario.
 */
void veterinario_free(Veterinario* veterinario) {
  if (veterinario->nombre)
    free(veterinario->nombre);
  if (veterinario->correo)
    free(veterinario->correo);
  if (veterinario->fecha_nacimiento)
    free(veterinario->fecha_nacimiento);
  free(veterinario);
}

/* Devuelve el número de cuenta del veterinario. */
int veterinario_id(Veterinario* veterinario) {
  return veterinario->id;
}

/* Devuelve la especialidad del veterinario. */
int veterinario_esp(Veterinario* veterinario) {
  return veterinario->esp;
}

/* Devuelve el nombre del veterinario. */
char* veterinario_nombre(Veterinario* veterinario) {
  return veterinario->nombre;
}

/* Devuelve la jornada del veterinario. */
int veterinario_jornada(Veterinario* veterinario) {
  veterinario->jornada;
}

/* Devuelve el correo electrónico del veterinario. */
char* veterinario_correo(Veterinario* veterinario) {
  return veterinario->correo;
}

/* Devuelve la fecha de nacimiento del veterinario. */
char* veterinario_fecha_nacimiento(Veterinario* veterinario) {
  return veterinario->fecha_nacimiento;
}

/* Asigna el número de cuenta del veterinario. */
void veterinario_set_id(Veterinario* veterinario, int id) {
  veterinario->id = id;
}

/* Asigna la especialidad del veterinario. */
void veterinario_set_esp(Veterinario* veterinario, int esp) {
  veterinario->esp = esp;
}

/* Asigna el nombre del veterinario. */
void veterinario_set_nombre(Veterinario* veterinario, char* nombre) {
  if(veterinario->nombre)
    free(veterinario->nombre);
  veterinario->nombre = malloc(sizeof(char)*(strnlen(nombre, TAMANO_NOMBRE)+1));
  strcpy(veterinario->nombre, nombre);
}

/* Asigna la jornada del veterinario. */
void veterinario_set_jornada(Veterinario* veterinario, int jornada) {
  veterinario->jornada = jornada;
}

/* Asigna el correo electrónico del veterinario. */
void veterinario_set_correo(Veterinario* veterinario, char* correo) {
  if(veterinario->correo)
    free(veterinario->correo);
  veterinario->correo = malloc(sizeof(char)*(strnlen(correo, TAMANO_NOMBRE)+1));
  strcpy(veterinario->correo, correo);
}

/* Asigna la fecha de nacimiento del veterinario. */
void veterinario_set_fecha_nacimiento(Veterinario* veterinario, char* fecha_nacimiento) {
  if(veterinario->fecha_nacimiento)
    free(veterinario->fecha_nacimiento);
  veterinario->fecha_nacimiento = malloc(sizeof(char)*(strnlen(fecha_nacimiento, TAMANO_NOMBRE)+1));
  strcpy(veterinario->fecha_nacimiento, fecha_nacimiento);
}
