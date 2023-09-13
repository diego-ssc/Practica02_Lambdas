#pragma once

#include "sistema.h"

Trabajador* trabajador_new(char* rfc,char* nombre, char* a_paterno,
                           char* a_materno, char* calle, int num_interior,
                           int num_exterior, char* colonia, char* estado,
                           int telefono, char* fecha_ini_con,
                           char* fecha_fin_con, char* fecha_nacimiento,
                           char* correo, char* genero);

void trabajador_free(Trabajador* trabajador);

char* trabajador_rfc(Trabajador* trabajador);

char* trabajador_nombre(Trabajador* trabajador);

char* trabajador_a_paterno(Trabajador* trabajador);

char* trabajador_materno(Trabajador* trabajador);

char* trabajador_calle(Trabajador* trabajador);

int trabajador_num_interior(Trabajador* trabajador);

int trabajador_num_exterior(Trabajador* trabajador);

char* trabajador_colonia(Trabajador* trabajador);

char* trabajador_estado(Trabajador* trabajador);

int trabajador_telefono(Trabajador* trabajador);

char* trabajador_fecha_ini_con(Trabajador* trabajador);

char* trabajador_fecha_fin_con(Trabajador* trabajador);

char* trabajador_fecha_nacimiento(Trabajador* trabajador);

char* trabajador_correo(Trabajador* trabajador);

char* trabajador_genero(Trabajador* trabajador);