#ifndef AERONAVES_H
#define AERONAVES_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


typedef struct aeronaves Aeronaves;

// Cria uma nova aeronave e aloca memória
Aeronaves* create_aeronave(void);

// Inicializa uma aeronave com dados
Aeronaves* init_aeronave(const char *identifier, const char *manufacturer,
                         const char *model, int year, int capacity, int range);

// Liberta a memória associada a uma aeronave
void free_aeronave(Aeronaves *a);

// Imprime os dados da aeronave (para debug)
void print_aeronave(Aeronaves *a);



// FUNÇÕES DE VALIDAÇÃO

// Valida os dados da aeronave
bool validate_aeronave(const Aeronaves *a);

// Valida strings genéricas (não nulas, não vazias)
bool is_valid_string(const char *str);


// GETTERS - Funções para obter valores

const char* get_identifier_aeronave(const Aeronaves *a);
const char* get_manufacturer_aeronave(const Aeronaves *a);
const char* get_model_aeronave(const Aeronaves *a);
int get_year_aeronave(const Aeronaves *a);
int get_capacity_aeronave(const Aeronaves *a);
int get_range_aeronave(const Aeronaves *a);


// SETTERS - Funções para definir valores

void set_identifier_aeronave(Aeronaves *a, const char *identifier);
void set_manufacturer_aeronave(Aeronaves *a, const char *manufacturer);
void set_model_aeronave(Aeronaves *a, const char *model);
void set_year_aeronave(Aeronaves *a, int year);
void set_capacity_aeronave(Aeronaves *a, int capacity);
void set_range_aeronave(Aeronaves *a, int range);


//PARSER - Funções para leitura e carregamento

// Lê uma linha CSV e cria uma aeronave
Aeronaves* parse_aeronave_from_CSV(const char *linha);

// Carrega aeronaves de um ficheiro CSV
int load_aeronaves_from_file(const char *filename, Aeronaves ***aeronaves, int *count);

// Liberta o array de aeronaves
void free_aeronaves_array(Aeronaves **aeronaves, int count);

#endif
