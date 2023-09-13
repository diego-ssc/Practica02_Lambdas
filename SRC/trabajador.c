#include "trabajador.h"
#include "sistema.h"
#include <stdlib.h>
#include <string.h>


struct Trabajador_ {
  char* rfc;
  char* nombre;
  char* a_paterno;
  char* a_materno;
  char* calle;
  int num_interior;
  int num_exterior;
  char* colonia;
  char* estado;
  int telefono;
  char* fecha_ini_con;
  char* fecha_fin_con;
  char* fecha_nacimiento;
  char* correo;
  char* genero;
};

Trabajador* trabajador_new(char* rfc,char* nombre, char* a_paterno,
                           char* a_materno, char* calle, int num_interior,
                           int num_exterior, char* colonia, char* estado,
                           int telefono, char* fecha_ini_con,
                           char* fecha_fin_con, char* fecha_nacimiento,
                           char* correo, char* genero){
    Trabajador* trabajador= malloc(sizeof(struct Trabajador_));
    
    trabajador->rfc = rfc ;
    trabajador->nombre = nombre;
    trabajador->a_paterno = a_paterno;
    trabajador->a_materno = a_materno;
    trabajador->calle = calle;
    trabajador->num_interior = num_interior;
    trabajador->num_exterior = num_exterior;
    trabajador->colonia = colonia;
    trabajador->estado = estado;
    trabajador->telefono = telefono;
    trabajador->fecha_ini_con = fecha_ini_con;
    trabajador->fecha_fin_con = fecha_fin_con;
    trabajador->fecha_nacimiento = fecha_nacimiento;
    trabajador->correo = correo;
    trabajador->genero = genero;
    
    trabajador->rfc = malloc(sizeof(char)*(strnlen(rfc, TAMANO_RFC)+1));
    trabajador->nombre = malloc(sizeof(char)*(strnlen(nombre,TAMANO_NOMBRE)+1));
    trabajador->a_paterno = malloc(sizeof(char)*(strnlen(a_paterno,TAMANO_NOMBRE)+1));
    trabajador->a_materno = malloc(sizeof(char)*(strnlen(a_materno, TAMANO_NOMBRE)+1));
    trabajador->calle = malloc(sizeof(char)*(strnlen(calle, TAMANO_NOMBRE)+1));
    trabajador->colonia = malloc(sizeof(char)*(strnlen(colonia, TAMANO_NOMBRE)+1));
    trabajador->estado = malloc(sizeof(char)*(strnlen(estado, TAMANO_NOMBRE)+1));
    trabajador->fecha_ini_con = malloc(sizeof(char)*(strnlen(fecha_ini_con, TAMANO_FECHA)+1));
    trabajador->fecha_fin_con = malloc(sizeof(char)*(strnlen(fecha_fin_con,TAMANO_FECHA)+1));
    trabajador->fecha_nacimiento = malloc(sizeof(char)*(strnlen(fecha_nacimiento,TAMANO_FECHA)+1));
    trabajador->correo = malloc(sizeof(char)*(strnlen(correo, TAMANO_NOMBRE)+1));
    trabajador->genero = malloc(sizeof(char)*(strnlen(genero, TAMANO_NOMBRE)+1));
    
    return trabajador;
    }

void trabajador_free(Trabajador* trabajador){
  if (trabajador->rfc) free(trabajador->rfc);
  if (trabajador->nombre) free(trabajador->nombre);
  if (trabajador->a_paterno) free(trabajador->a_paterno);
  if (trabajador->a_materno) free(trabajador->a_materno);
  if (trabajador->calle) free(trabajador->calle);
  if (trabajador->colonia) free(trabajador->colonia);
  if (trabajador->estado) free(trabajador->estado);
  if (trabajador->fecha_ini_con) free(trabajador->fecha_ini_con);
  if (trabajador->fecha_fin_con) free(trabajador->fecha_fin_con);
  if (trabajador->fecha_nacimiento) free(trabajador->fecha_nacimiento);
  if (trabajador->genero) free(trabajador->correo);
  free(trabajador);
}

char* trabajador_rfc(Trabajador* trabajador){
  return trabajador->rfc;
}

char* trabajador_nombre(Trabajador* trabajador){
  return trabajador->nombre;
}

char* trabajador_a_paterno(Trabajador* trabajador){
  return trabajador->a_paterno;
}

char* trabajador_materno(Trabajador* trabajador){
  return trabajador->a_materno;
}

char* trabajador_calle(Trabajador* trabajador){
  return trabajador->calle;
}

int trabajador_num_interior(Trabajador* trabajador){
  return trabajador->num_interior;
}

int trabajador_num_exterior(Trabajador* trabajador){
  return trabajador->num_exterior;
}

char* trabajador_colonia(Trabajador* trabajador){
  return trabajador->colonia;
}

char* trabajador_estado(Trabajador* trabajador){
  return trabajador->estado;
}

int trabajador_telefono(Trabajador* trabajador){
  return trabajador->telefono;
}

char* trabajador_fecha_ini_con(Trabajador* trabajador){
  return trabajador->fecha_ini_con;
}

char* trabajador_fecha_fin_con(Trabajador* trabajador){
  return trabajador->fecha_fin_con;
}

char* trabajador_fecha_nacimiento(Trabajador* trabajador){
  return trabajador->fecha_nacimiento;
}

char* trabajador_correo(Trabajador* trabajador){
  return trabajador->correo;
}

char* trabajador_genero(Trabajador* trabajador){
  return trabajador->genero;
}

void trabajador_set_rfc(Trabajador* trabajador, char* rfc){
  if(trabajador->rfc) free(trabajador->rfc);
  trabajador->rfc = malloc(sizeof(char)*(strnlen(rfc, TAMANO_RFC)+1));
  strcpy(trabajador->rfc, rfc);
}

void trabajador_set_nombre(Trabajador* trabajador, char* nombre){
  if(trabajador->nombre) free(trabajador->nombre);
  trabajador->rfc = malloc(sizeof(char)*(strnlen(nombre, TAMANO_NOMBRE)+1));
  strcpy(trabajador->nombre, nombre);
}

void trabajador_set_a_paterno(Trabajador* trabajador, char* a_paterno){
  if(trabajador->a_paterno) free(trabajador->a_paterno);
  trabajador->a_paterno = malloc(sizeof(char)*(strnlen(a_paterno, TAMANO_NOMBRE)+1));
  strcpy(trabajador->a_paterno, a_paterno);
}

void trabajador_set_a_materno(Trabajador* trabajador, char* a_materno){
  if(trabajador->a_materno) free(trabajador->a_materno);
  trabajador->a_materno = malloc(sizeof(char)*(strnlen(a_materno, TAMANO_NOMBRE)+1));
  strcpy(trabajador->a_materno, a_materno);
}

void trabajador_set_calle(Trabajador* trabajador, char* calle){
  if(trabajador->calle) free(trabajador->calle);
  trabajador->a_paterno = malloc(sizeof(char)*(strnlen(calle, TAMANO_NOMBRE)+1));
  strcpy(trabajador->calle, calle);
}

void trabajador_set_num_interior(Trabajador* trabajador, int num_interior){
  trabajador->num_interior=num_interior;
}

void trabajador_set_num_exterior(Trabajador* trabajador, int num_exterior){
  trabajador->num_exterior=num_exterior;
}

void trabajador_set_colonia(Trabajador* trabajador, char* colonia){
  if(trabajador->colonia) free(trabajador->colonia);
  trabajador->colonia = malloc(sizeof(char)*(strnlen(colonia, TAMANO_NOMBRE)+1));
  strcpy(trabajador->colonia, colonia);
}

void trabajador_set_estado(Trabajador* trabajador, char* estado){
  if(trabajador->estado) free(trabajador->estado);
  trabajador->estado = malloc(sizeof(char)*(strnlen(estado, TAMANO_NOMBRE)+1));
  strcpy(trabajador->estado, estado);
}

void trabajador_set_telefono(Trabajador* trabajador, int telefono){
    trabajador->telefono=telefono;
}

void trabajador_set_fecha_ini_con(Trabajador* trabajador, char* fecha_ini_con){
  if(trabajador->fecha_ini_con) free(trabajador->fecha_ini_con);
  trabajador->fecha_ini_con = malloc(sizeof(char)*(strnlen(fecha_ini_con, TAMANO_NOMBRE)+1));
  strcpy(trabajador->fecha_ini_con, fecha_ini_con);
}

void trabajador_set_fecha_fin_con(Trabajador* trabajador, char* fecha_fin_con){
  if(trabajador->fecha_fin_con) free(trabajador->fecha_fin_con);
  trabajador->fecha_fin_con = malloc(sizeof(char)*(strnlen(fecha_fin_con, TAMANO_NOMBRE)+1));
  strcpy(trabajador->fecha_fin_con, fecha_fin_con);
}

void trabajador_set_fecha_nacimiento(Trabajador* trabajador, char* fecha_nacimiento){
  if(trabajador->fecha_nacimiento) free(trabajador->fecha_nacimiento);
  trabajador->fecha_nacimiento = malloc(sizeof(char)*(strnlen(fecha_nacimiento, TAMANO_NOMBRE)+1));
  strcpy(trabajador->fecha_nacimiento, fecha_nacimiento);
}

void trabajador_set_correo(Trabajador* trabajador, char* correo){
  if(trabajador->correo) free(trabajador->correo);
  trabajador->correo = malloc(sizeof(char)*(strnlen(correo, TAMANO_NOMBRE)+1));
  strcpy(trabajador->correo, correo);
}

void trabajador_set_genero(Trabajador* trabajador, char* genero){
  if(trabajador->genero) free(trabajador->genero);
  trabajador->genero = malloc(sizeof(char)*(strnlen(genero, TAMANO_NOMBRE)+1));
  strcpy(trabajador->genero, genero);
}