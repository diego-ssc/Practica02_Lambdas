#pragma once

#include "sistema.h"

/**
 * Crea un nuevo Bioma.
 * @param nombre el nombre.
 * @param region la región.
 * @param id el identificador.
 */
Bioma* bioma_new(char* nombre, char* region, int id);

/**
 * Libera la memoria usada por un Bioma.
 * @param bioma el bioma.
 */
void bioma_free(Bioma* bioma);

/**
 * Devuelve el nombre del bioma.
 * @param bioma el bioma.
 * @return el nombre.
 */
char* bioma_nombre(Bioma* bioma);

/**
 * Devuelve la región del bioma.
 * @param bioma el bioma.
 * @return la región.
 */
char* bioma_region(Bioma* bioma);

/**
 * Devuelve el identificador del bioma.
 * @param bioma el bioma.
 * @return el identificador.
 */
int bioma_id(Bioma* bioma);

/**
 * Asigna el nombre del bioma.
 * @param bioma el bioma.
 * @param nombre el nombre.
 */
void bioma_set_nombre(Bioma* bioma, char* nombre);

/**
 * Asigna la región del bioma.
 * @param bioma el bioma.
 * @param region la región.
 */
void bioma_set_region(Bioma* bioma, char* region);

/**
 * Asigna el identificador del bioma.
 * @param bioma el bioma.
 * @param id el identificador.
 */
void bioma_set_id(Bioma* bioma, int id);
