#pragma once
#include "sistema.h"

/**
 * Constructor para la estructura Animal
 * @param id el identificador del animal
 * @param bioma el identificador del bioma
 * @param fecha la fecha de nacimiento del animal
 * @param nombre el nombre del animal
 * @param especie la especie del animal
 */
Animal* animal_new(int id, int bioma , char* fecha, char* nombre, char* especie);

/**
 * Libera animal
 * @param animal el animal
 */
void animal_free(Animal* animal);

/**
 * Setter para el atributo fecha de nacimiento 
 * @param animal el animal
 * @param nueva_fecha la nueva fecha
 */
void animal_set_fecha_nacimiento(Animal* animal, char* nueva_fecha);

/**
 * Regresa la fecha de nacimiento del animal
 * @param animal el animal
 * @return la fecha de nacimiento
 */
char* animal_fecha_nacimiento(Animal* animal);

/**
 * Setter para el atributo nombre
 * @param animal el animal
 * @param nuevo_nombre 
 */
void animal_set_nombre(Animal* animal, char* nuevo_nombre);

/**
 * Regresa el nombre del animal
 * @param animal el animal
 * @return el nombre 
 */
char* animal_nombre(Animal* animal);

/**
 * Setter para el atributo especie
 * @param animal el animal
 * @param nueva_especie la nueva especie
 */
void animal_set_especie(Animal* animal, char* nueva_especie);

/**
 * Regresa la especie del animal
 * @param animal el animal
 * @return la especie
 */
char* animal_especie(Animal* animal);


/**
 * Regresa el id del animal
 * @param animal el animal
 */
int animal_id(Animal* animal);

/**
 * Regresa el bioma del animal
 * @param animal el animal
 */
int animal_bioma(Animal* animal);
