#pragma once

/* Define el tamaño designado de los nombres. */
#define TAMANO_NOMBRE 50

#define TAMANO_PROMEDIO_LINEA 16

/* La estructura Administrador opaca. */
typedef struct Administrador_ Administrador;

/* La estructura Veterinario opaca. */
typedef struct Veterinario_ Veterinario;

/* La estructura Veterinario opaca. */
typedef struct Animal_ Animal;

/* La estructura Input_parser opaca. */
typedef struct Bioma_ Bioma;

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "administrador.h"
#include "veterinario.h"
#include "animal.h"
#include "bioma.h"
