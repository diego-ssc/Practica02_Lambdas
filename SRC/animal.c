#include "animal.h"

/* La estructura Animal. */
struct Animal_ {
  /* El identificador. */
  int id;
  /* El bioma al que pertenece. */
  int bioma;
  /* La fecha de nacimiento. */
  char* fecha_nacimiento;
  /* El nombre común del animal. */
  char* nombre;
  /* La especie. */
  char* especie;
  /*El peso.*/
  float peso;
  /*La altura.*/
  float altura;
  /*El sexo.*/
  char* sexo;
  /*El numero de jaula.*/
  int n_jaula;
  /*El tipo de alimentación.*/
  char* t_alim;
  /*Las indicaciones medicas.*/
  char* ind_med;
};

/* Constructor para la estructura Animal */
Animal* animal_new(int id, int bioma , char* fecha, char* nombre, char* especie, float peso,
  float altura, char* sexo, int n_jaula, char* t_alim, char* ind_med){
  Animal* nuevo_animal = malloc((sizeof(Animal)));
  nuevo_animal->id = id;
  nuevo_animal->bioma = bioma;
  nuevo_animal->fecha_nacimiento = malloc(sizeof(char)*(strnlen(fecha, TAMANO_NOMBRE)+1));
  strcpy(nuevo_animal->fecha_nacimiento, fecha);
  nuevo_animal->nombre = malloc(sizeof(char)*(strnlen(nombre, TAMANO_NOMBRE)+1));
  strcpy(nuevo_animal->nombre, nombre);
  nuevo_animal->especie = malloc(sizeof(char)*(strnlen(especie, TAMANO_NOMBRE)+1));
  strcpy(nuevo_animal->especie, especie);
  nuevo_animal->peso = peso;
  nuevo_animal->altura = altura;
  nuevo_animal->sexo = malloc(sizeof(char)*(strnlen(sexo, TAMANO_NOMBRE)+1));
  strcpy(nuevo_animal->sexo, sexo);
  nuevo_animal->n_jaula = n_jaula;
  nuevo_animal->t_alim = malloc(sizeof(char)*(strnlen(t_alim, TAMANO_NOMBRE)+1));
  strcpy(nuevo_animal->t_alim, t_alim);
  nuevo_animal->ind_med = malloc(sizeof(char)*(strnlen(ind_med, TAMANO_NOMBRE)+1));
  strcpy(nuevo_animal->ind_med, ind_med);
  return nuevo_animal;
}

/* Libera animal */
void animal_free(Animal* animal){
  if(animal->fecha_nacimiento)
    free(animal->fecha_nacimiento);
  if(animal->nombre)
    free(animal->nombre);
  if(animal->especie)
    free(animal->especie);
  free(animal);
}

/* Setter para el atributo fecha de nacimiento  */
void animal_set_fecha_nacimiento(Animal* animal, char* nueva_fecha){
  if(animal->fecha_nacimiento)
    free(animal->fecha_nacimiento);
  animal->fecha_nacimiento = malloc(sizeof(char)*(strnlen(nueva_fecha, TAMANO_NOMBRE)+1));
  strcpy(animal->fecha_nacimiento, nueva_fecha);
}

/*  Regresa la fecha de nacimiento del animal */
char* animal_fecha_nacimiento(Animal* animal) {
  return animal->fecha_nacimiento;
}

/* Setter para el atributo nombre */
void animal_set_nombre(Animal* animal, char* nuevo_nombre) {
  if(animal->nombre)
    free(animal->nombre);
  animal->nombre = malloc(sizeof(char)*(strnlen(nuevo_nombre, TAMANO_NOMBRE)+1));
  strcpy(animal->nombre, nuevo_nombre);
}

/* Regresa el nombre del animal */
char* animal_nombre(Animal* animal) {
  return animal->nombre;
}

/*  Setter para el atributo especie */
void animal_set_especie(Animal* animal, char* nueva_especie) {
  if(animal->especie)
    free(animal->especie);
  animal->especie = malloc(sizeof(char)*(strnlen(nueva_especie, TAMANO_NOMBRE)+1));
  strcpy(animal->especie, nueva_especie);
}

/* Regresa la especie del animal */
char* animal_especie(Animal* animal) {
  return animal->especie;
}


/* Regresa el id del animal */
int animal_id(Animal* animal) {
  return animal->id;
}

/* Regresa el bioma del animal */
int animal_bioma(Animal* animal) {
  return animal->bioma;
}

void animal_set_peso(Animal* animal, float peso){
  animal->peso = peso;
}

void animal_set_altura(Animal* animal, float altura ){
  animal->altura = altura;
}

void animal_set_sexo(Animal* animal, char* n_sexo){
  if(animal->sexo)
    free(animal->sexo);
  animal->sexo = malloc(sizeof(char)*(strnlen(n_sexo, TAMANO_NOMBRE)+1));
  strcpy(animal->sexo, n_sexo);
}

void animal_set_n_jaula(Animal* animal, int n_jaula ){
  animal->n_jaula = n_jaula;
}

void animal_set_t_alim(Animal* animal, char* n_t_alim){
  if(animal->t_alim)
    free(animal->t_alim);
  animal->t_alim = malloc(sizeof(char)*(strnlen(n_t_alim, TAMANO_NOMBRE)+1));
  strcpy(animal->t_alim, n_t_alim);
}

void animal_set_ind_med(Animal* animal, char* n_ind_med){
  if(animal->ind_med)
    free(animal->ind_med);
  animal->ind_med = malloc(sizeof(char)*(strnlen(n_ind_med, TAMANO_NOMBRE)+1));
  strcpy(animal->ind_med, n_ind_med);
}

float animal_peso(Animal* animal){
  return animal->peso;
}

float animal_altura(Animal* animal){
  return animal->altura;
}

char* animal_sexo(Animal* animal){
  return animal->sexo;
}

int animal_n_jaula(Animal* animal){
  return animal->n_jaula;
}

char* animal_t_alim(Animal* animal){
  return animal->t_alim;
}

char* animal_ind_med(Animal* animal){
  return animal->ind_med;
}
