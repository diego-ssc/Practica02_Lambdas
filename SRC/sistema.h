#pragma once

/* Define el tamaño designado de los nombres. */
#define TAMANO_NOMBRE 50
/* Define el tamaño designado de las fechas. */
#define TAMANO_FECHA 8
/* Define el tamaño designado del rfc*/
#define TAMANO_RFC 13
/*Define la cadena de la entidad veterinario*/
#define ENTIDAD_VETERINARIO "veterinario"
/*Define la cadena de la entidad bioma*/
#define ENTIDAD_BIOMA "bioma"
/*Define la cadena de la entidad animal*/
#define ENTIDAD_ANIMAL "animal"

/* La estructura Administrador opaca. */
typedef struct Administrador_ Administrador;

/* La estructura Veterinario opaca. */
typedef struct Veterinario_ Veterinario;

typedef struct Trabajador_ Trabajador;

/* La estructura Veterinario opaca. */
typedef struct Animal_ Animal;

/* La estructura Input_parser opaca. */
typedef struct Bioma_ Bioma;

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "administrador.h"
#include "veterinario.h"
#include "trabajador.h"
#include "animal.h"
#include "bioma.h"
