#include <stdlib.h>
#include <stdio.h>

#include "sistema.h"
#include "entidad.h"

#define NUMERO_ENTIDADES 3
#define NUMERO_ENTIDADES 3

int salir();
int agrega(enum Entidad , Administrador* );

/* Hilo de ejecución principal. */
int main(int argc, char** argv) {
  const char * archivos[] = {
    "animal.csv",
    "bioma.csv",
    "veterinario.csv"
  };
  Administrador* administrador = administrador_new(archivos,
                                                   NUMERO_ENTIDADES);


  char line[TAMANO_LINEA];
  int i;
  int  c = 0;
  while (!c) {
    printf("Ingrese el numero de la operacion:\nAGREGAR : 1\nELIMINAR : 2\nCONSULTAR : 3\nEDITAR : 4\n");
    if (fgets(line, sizeof(line), stdin)) 
      if(1 == sscanf(line, "%d", &i))
        if (0 < i && i < 5)
          c =1;
  }
  

  switch (i){
    //AGREGAR
  case 1:
    c = 0;
    while (!c) {
      printf("Ingrese el numero de la entidad para operar:\nANIMAL : 1\nBIOMA : 2\nVETERINARIO : 3\n");
      if (fgets(line, sizeof(line), stdin)) 
        if(1 == sscanf(line, "%d", &i))
          if (0 < i && i < 4)
            c =1;
    }
    while (!agrega(i-1, administrador)) {
      if (salir())
        break;
    } 
    /* printf("Ingrese el numero de la entidad para operar:\nANIMAL : 1\nBIOMA : 2\nVETERINARIO : 3\n"); */
    /* if (fgets(line, sizeof(line), stdin)) { */
    /*   if(1 == sscanf(line, "%d", &i)){ */
              
    /*   } */
    /* } */
    break;
    // ELIMINAR
  case 2:
    break;
    // CONSULTA
  case 3:
    break;
    // EDITAR
  case 4:
    c = 0;
    while (!c) {
      printf("Ingrese el id de la entidad a consultar:\n");
      if (fgets(line, sizeof(line), stdin)) 
        if(1 == sscanf(line, "%d", &i))
          if (0 < i)
            c = 1;
    }
    while (!consulta(i-1, administrador, i)) {
      if (salir())
        break;
    } 
    
   
    break;
  default:
        
  }
  

  return 0;
}

int salir() {
  char line[TAMANO_LINEA];
  int i;
  printf("Salir?(0=no\n1=yes) : ");
  if (!fgets(line, TAMANO_LINEA, stdin)) {
    printf("Error de input\n");
    return 0;
  }
  if (1 != sscanf(line, "%d", &i)){
    printf("Error de input\n");
    return 0;     
  }
  if (i)
    return 1;
  return 0;
}
  
int agrega(enum Entidad e, Administrador* administrador) {
  char line[TAMANO_LINEA], nombre[TAMANO_NOMBRE], fecha[TAMANO_NOMBRE];
  int id;
  
  switch (e) {
  case ANIMAL :
    printf("Datos a ingresar (bioma (int), nombre, especie, fecha_nacimiento)\ningrese los datos separados por espacios.\n");
    if (!fgets(line, TAMANO_LINEA, stdin)) {
      printf("Error de input\n");
      return 0;
    }
    int bioma_id;
    char especie[TAMANO_NOMBRE];
    if (4 != sscanf(line, "%d %s %s %s", &bioma_id, nombre, especie, fecha)){
      printf("Error de input\n");
      return 0;     
    }
    id = administrador_animales(administrador)+1;
    Animal* animal = animal_new(id, bioma_id, nombre, especie, fecha);
    printf("Animal(%d, %d, %s, %s, %s)\n", id, bioma_id, nombre, especie, fecha);
    administrador_agrega(administrador, animal, ANIMAL);
    return 1;
    break;
  case BIOMA :
    printf("Datos a ingresar (nombre, region)\ningrese los datos separados por espacios.\n");
    if (!fgets(line, TAMANO_LINEA, stdin)) {
      printf("Error de input\n");
      return 0;
    }
    char nombre[30], region[30];
    if (2 != sscanf(line, "%s %s", nombre, region)){
      printf("Error de input\n");
      return 0;         
    }
    id = administrador_biomas(administrador)+1;
    Bioma* bioma = bioma_new(nombre, region, id);
    printf("Bioma(%d, %s, %s)\n", id,  nombre, region);
    administrador_agrega(administrador, bioma, BIOMA);
    return 1;
    break;
  case VETERINARIO:
    printf("Datos a ingresar (nombre, especialidad, jornada (0:medio tiempo, 1:tiempo completo), correo, fecha_nacimiento)\ningrese los datos separados por espacios\n");
    if (!fgets(line, TAMANO_LINEA, stdin)) {
      printf("Error de input\n");
      return 0;
    }
    int jornada, esp;
    char  correo[TAMANO_NOMBRE];
    if (5 != sscanf(line, "%s %d %d %s %s", nombre, &esp, &jornada, correo, fecha)){
      printf("Error de input\n");
      return 0;
    }
    if (!(jornada == 0 || jornada == 1)) {
      printf("Error de input\n");
      return 0;
    }
    id = administrador_veterinarios(administrador)+1;
    Veterinario* vet = veterinario_new(id, esp, nombre, jornada, correo, fecha);
    printf("Veterinario(%d, %s, %s)\n", id,  nombre, region);
    administrador_agrega(administrador, vet, VETERINARIO);
    return 1;
    break;
  default:
    printf("Error de input\n");
    return 0;
  }
}



int consulta(enum Entidad e, Administrador* administrador, int id) {
  
  switch (e) {
  case ANIMAL:
    Animal* animal = administrador_consulta(administrador, id, e);
    
    if (animal){
      printf("Animal(%d, %d, %s, %s, %s)",
           animal_id(animal),
           animal_bioma(animal),
           animal_nombre(animal),
           animal_especie(animal),
           animal_fecha_nacimiento(animal));   
      return 1;
    }
    
      break;
  case BIOMA:
    Bioma* bioma = administrador_consulta(administrador, id, e);
    if (bioma) {
      printf("Bioma(%d, %s, %s)",
           bioma_id(bioma),
           bioma_nombre(bioma),
           bioma_region(bioma));
      return 1;
    }
    
    break;
  case VETERINARIO:
    Veterinario* vet= administrador_consulta(administrador, id, e);
    
    if (vet) {
      printf("Veterinario(%d, %d, %s, %d, %s, %s)",
             veterinario_id(vet),
             veterinario_esp(vet),
             veterinario_nombre(vet),
             veterinario_jornada(vet),
             veterinario_correo(vet),
             veterinario_fecha_nacimiento(vet));   
      return 1;
    }
    break;
  default:
    printf("Error de input\n");
    return 0;
  }
  printf("Error de input\n");
  return 0;
}


