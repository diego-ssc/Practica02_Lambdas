#include <stdlib.h>
#include <stdio.h>

#include "sistema.h"
#include "entidad.h"

#define NUMERO_ENTIDADES 3
#define NUMERO_ENTIDADES 3

/* Hilo de ejecución principal. */
int main(int argc, char** argv) {
  const char * archivos[] = {
    "animal.csv",
    "bioma.csv",
    "veterinario.csv"
  };
  Administrador* administrador = administrador_new(archivos,
                                                   NUMERO_ENTIDADES);

  //  printf("Ingrese el numero de la entidad para operar:\nANIMAL : 1\nBIOMA : 2\nVETERINARIO : 3\n");
  printf("Ingrese el numero de la operacion:\nAGREGAR : 1\nELIMINAR : 2\nCONSULTAR : 3\n");
  char line[200];
  int i;
  if (fgets(line, sizeof(line), stdin)) {
    if(1 == sscanf(line, "%d", &i)){
      switch (i){
        //AGREGAR
      case 1:
        //printf("Ingrese el numero de la operacion:\nAGREGAR : 1\nELIMINAR : 2\nCONSULTAR : 3\n");
        printf("Ingrese el numero de la entidad para operar:\nANIMAL : 1\nBIOMA : 2\nVETERINARIO : 3\n");
        if (fgets(line, sizeof(line), stdin)) {
          if(1 == sscanf(line, "%d", &i)){
            
            switch (i-1) {
            case ANIMAL:
              printf("Datos a ingresar (bioma (int), nombre, especie, fecha_nacimiento)\ningrese los datos separados por espacios");
              if (fgets(line, sizeof(line), stdin)) {
                int bioma;
                char nombre[30], especie[30], fecha[30];
                if (1 == sscanf(line, "%d %s %s %s", nombre, especie, fecha)){
                  int id = administrador_animales(administrador)+1;
                  Animal* animal = animal_new(id, bioma, nombre, especie, fecha);
                  printf("Animal(%d, %d, %s, %s, %s)", id, bioma, nombre, especie, fecha);
                  administrador_agrega(administrador, animal, ANIMAL)                  
                }else {
                  printf("Error de input");
                  return 0;
                }
              }
              break;
            case BIOMA:
              printf("Datos a ingresar ( nombre, region)\ningrese los datos separados por espacios");
              if (fgets(line, sizeof(line), stdin)) {
                
                char nombre[30], region[30];
                if (1 == sscanf(line, "%s %s", nombre, region)){
                  int id = administrador_biomas(administrador)+1;
                  Bioma* bioma = bioma_new(nombre, region, id);
                  printf("Bioma(%d, %s, %s)", id,  nombre, region);
                  administrador_agrega(administrador, bioma, BIOMA)                  
                }else {
                  printf("Error de input");
                  return 0;
                }
              }
              break;
            case VETERINARIO:
              printf("Datos a ingresar (nombre, especialidad, jornada (0:medio tiempo, 1:tiempo completo), correo, fecha_nacimiento)\ningrese los datos separados por espacios");
              if (fgets(line, sizeof(line), stdin)) {
                int jornada;
                char nombre[30], especialidad[30], correo[30], fecha[30];
                if (1 == sscanf(line, "%s %s %d %s %s", nombre, especialidad, jornada, correo, fecha)){
                  if (!(jornada == 0 || jornada == 1)) {
                    printf("Error de input");
                    return 0;
                  }
                  int id = administrador_biomas(administrador)+1;
                  Bioma* bioma = bioma_new(nombre, region, id);
                  printf("Bioma(%d, %s, %s)", id,  nombre, region);
                  administrador_agrega(administrador, bioma, BIOMA)                  
                }else {
                  printf("Error de input");
                  return 0;
                }
              break;
            default:
              
            }
            
                    
          }
        }
        break;
      case 2:
        break;
      case 3:
        break;
      default:
        
      }
    }else{
      printf("Error de input");
      return 0;
    }
  else {
    printf("Error de input");
    return 0;
  }

  

  Administrador* administrador = administrador_new(archivos,
                                                   NUMERO_ENTIDADES);

  Bioma* bioma = bioma_new("nombre", "region", 1);
  Veterinario* vet = veterinario_new(1, 0, "nombre", 0, "correo", "fecha");
  Animal* animal = animal_new(1, 1, "fecha", "nombre", "especie");
  //administrador_agrega(administrador, bioma, BIOMA);
  administrador_agrega(administrador, vet, VETERINARIO);
  administrador_agrega(administrador, animal, ANIMAL);
  
  
  Bioma* bioma1 = administrador_consulta(administrador, 5, BIOMA);
  if (bioma1)
    printf("%d,%s\n", bioma_id(bioma1), bioma_nombre(bioma1));
  bioma_free(bioma);
  if (bioma1)
    bioma_free(bioma1);
  administrador_free(administrador);

  return 0;
}
