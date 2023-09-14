#pragma once

#include "sistema.h"

/**
 * Construye un nuevo Administrador.
 * @param file_n_vet el nombre de archivo de veterinarios.
 * @param file_n_bi el nombre de archivo de biomas.
 * @param file_n_an el nombre de archivo de animales.
 */
Administrador* administrador_new(char* file_n_vet, char* file_n_bi, char* file_n_an);

/**
 * Libera la memoria usada por un Administrador.
 * @param administrador el administrador.
 */
void administrador_free(Administrador* administrador);

/**
 * Agrega el Animal parámetro a la base de datos.
 * @param administrador el administrador.
 * @param animal el animal.
 */
void administrador_agrega(Administrador* administrador, char* entidad);
void administrador_agrega_a(Administrador* administrador, Animal* animal);

/**
 * Agrega el Animal parámetro a la base de datos.
 * @param administrador el administrador.
 * @param bioma el bioma.
 */
void administrador_agrega_b(Administrador* administrador, Bioma* bioma);

/**
 * Agrega el Animal parámetro a la base de datos.
 * @param administrador el administrador.
 * @param veterinario el veterinario.
 */
void administrador_agrega_v(Administrador* administrador, Veterinario* veterinario);

/**
 * Elimina la entidad parámetro de la base de datos.
 * @param administrador el administrador.
 * @param entidad la entidad.
 */
void administrador_elimina(Administrador* administrador, void* entidad);


/**
 * Consulta el Animal parámetro de la base de datos.
 * @param administrador el administrador.
 * @param animal el animal.
 * @return el animal.
 */
Animal* administrador_consulta_a(Administrador* administrador, Animal* animal);

/**
 * Consulta el Bioma parámetro de la base de datos.
 * @param administrador el administrador.
 * @param bioma el bioma.
 */
void administrador_consulta_b(Administrador* administrador, Bioma* bioma);

/**
 * Consulta el Veterinario parámetro de la base de datos.
 * @param administrador el administrador.
 * @param veterinario el veterinario.
 */
void administrador_consulta_v(Administrador* administrador, Veterinario* veterinario);

/**
 * Edita la entidad parámetro de la base de datos.
 * @param administrador el administrador.
 * @param entidad la entidad.
 */
void administrador_edita(Administrador* administrador, void* entidad);

void administrador_agrega_animal(Administrador* administrador, Animal animal);

void administrador_agrega_bioma(Administrador* administrador, Bioma bioma);

void administrador_agrega_veterinario(Administrador* administrador, Veterinario veterinario);

Animal* administrador_cons_animal(Administrador* administrador);

Bioma* administrador_cons_bioma(Administrador* administrador);

Veterinario* administrador_cons_veterinario(Administrador* administrador);
