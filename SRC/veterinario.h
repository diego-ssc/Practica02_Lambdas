#pragma once

#include "sistema.h"

/**
 * Crea un nuevo veterinario.
 * @param id el número de cuenta.
 * @param esp la especialidad.
 * @param nombre el nombre.
 * @param jornada la jornada.
 * @param correo el correo electrónico.
 * @param fecha_nacimiento la fecha de nacimiento.
 */
Veterinario* veterinario_new(int id, int esp, char* nombre, int jornada,
                             char* correo, char* fecha_nacimiento);

/**
 * Libera la memoria usada por el Veterinario.
 * @param veterinario el veterinario.
 */
void veterinario_free(Veterinario* veterinario);

/**
 * Devuelve el número de cuenta del veterinario.
 * @param veterinario el veterinario.
 * @return el número de cuenta.
 */
int veterinario_id(Veterinario* veterinario);

/**
 * Devuelve la especialidad del veterinario.
 * @param veterinario el veterinario.
 * @return la especialidad.
 */
int veterinario_esp(Veterinario* veterinario);

/**
 * Devuelve el nombre del veterinario.
 * @param veterinario el veterinario.
 * @return el nombre.
 */
char* veterinario_nombre(Veterinario* veterinario);

/**
 * Devuelve la jornada del veterinario.
 * @param veterinario el veterinario.
 * @return el nombre.
 */
int veterinario_jornada(Veterinario* veterinario);

/**
 * Devuelve el correo electrónico del veterinario.
 * @param veterinario el veterinario.
 * @return el correo electrónico.
 */
char* veterinario_correo(Veterinario* veterinario);

/**
 * Devuelve la fecha de nacimiento del veterinario.
 * @param veterinario el veterinario.
 * @return la fecha de nacimiento.
 */
char* veterinario_fecha_nacimiento(Veterinario* veterinario);

/**
 * Asigna el número de cuenta del veterinario.
 * @param veterinario el veterinario.
 * @param id el número de cuenta.
 */
void veterinario_set_id(Veterinario* veterinario, int id);

/**
 * Asigna la especialidad del veterinario.
 * @param veterinario el veterinario.
 * @param esp la especialidad.
 */
void veterinario_set_esp(Veterinario* veterinario, int esp);

/**
 * Asigna el nombre del veterinario.
 * @param veterinario el veterinario.
 * @param nombre el nombre.
 */
void veterinario_set_nombre(Veterinario* veterinario, char* nombre);

/**
 * Asigna la jornada del veterinario.
 * @param veterinario el veterinario.
 * @param jornada la jornada.
 */
void veterinario_set_jornada(Veterinario* veterinario, int jornada);

/**
 * Asigna el correo electrónico del veterinario.
 * @param veterinario el veterinario.
 * @param correo el correo electrónico.
 */
void veterinario_set_correo(Veterinario* veterinario, char* correo);

/**
 * Asigna la fecha de nacimiento del veterinario.
 * @param veterinario el veterinario.
 * @param fecha_nacimiento la fecha de nacimiento.
 */
void veterinario_set_fecha_nacimiento(Veterinario* veterinario, char* fecha_nacimiento);
