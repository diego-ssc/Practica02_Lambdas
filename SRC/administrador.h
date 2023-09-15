#pragma once

#include "sistema.h"
#include "entidad.h"

/**
 * Construye un nuevo Administrador.
 * @param archivos los nombres de los archivos.
 * @param n el número de archivos.
 */
Administrador* administrador_new(const char** archivos, int n);

/**
 * Libera la memoria usada por un Administrador.
 * @param administrador el administrador.
 */
void administrador_free(Administrador* administrador);

/**
 * Devuelve el número de animales.
 * @param administrador el administrador.
 * @return el número de animales.
 */
int administrador_animales(Administrador* administrador);

/**
 * Devuelve el número de biomas.
 * @param administrador el administrador.
 * @return el número de biomas.
 */
int administrador_biomas(Administrador* administrador);

/**
 * Devuelve el número de veterinarios.
 * @param administrador el administrador.
 * @return el número de veterinarios.
 */
int administrador_veterinarios(Administrador* administrador);

/**
 * Agrega el Animal parámetro a la base de datos.
 * @param administrador el administrador.
 * @param entidad la entidad.
 * @param e el enum correspondiente a la entidad.
 */
void administrador_agrega(Administrador* administrador,
                          void* entidad, enum Entidad e);

/**
 * Elimina la entidad parámetro de la base de datos.
 * @param administrador el administrador.
 * @param id el identificador de la entidad a eliminar.
 * @param e el enum asociado a la entidad.
 */
void administrador_elimina(Administrador* administrador, int id, enum Entidad e);


/**
 * Consulta la entidad parámetro de la base de datos.
 * @param administrador el administrador.
 * @param id el identificador.
 * @param e el enum asociado a la entidad.
 * @return la entidad.
 */
void* administrador_consulta(Administrador* administrador, int id, enum Entidad e);


/**
 * Edita la entidad parámetro de la base de datos.
 * @param administrador el administrador.
 * @param id el identificador de la entidad.
 * @param a el identificador del atributo a editar.
 * @param a el atributo a editar.
 * @param e el enum asociado a la entidad.
 */
void administrador_edita(Administrador* administrador, int id, int a, void* atributo, enum Entidad e);
