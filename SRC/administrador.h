#pragma once

#include "sistema.h"

/**
 * Construye un nuevo Administrador.
 */
Administrador* administrador_new();

/**
 * Libera la memoria usada por un Administrador.
 * @param administrador el administrador.
 */
void administrador_free(Administrador* administrador);

/**
 * Agrega la entidad parámetro de la base de datos.
 * @param administrador el administrador.
 * @param entidad la entidad.
 */
void administrador_agrega(Administrador* administrador, char* entidad);

/**
 * Elimina la entidad parámetro de la base de datos.
 * @param administrador el administrador.
 * @param entidad la entidad.
 */
void administrador_elimina(Administrador* administrador, void* entidad);

/**
 * Consulta la entidad parámetro de la base de datos.
 * @param administrador el administrador.
 * @param entidad la entidad.
 */
void administrador_consulta(Administrador* administrador, void* entidad);

/**
 * Edita la entidad parámetro de la base de datos.
 * @param administrador el administrador.
 * @param entidad la entidad.
 */
void administrador_edita(Administrador* administrador, void* entidad);
