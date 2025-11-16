#ifndef AERONAVES_H
#define AERONAVES_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


typedef struct aeronaves Aeronaves;

// Cria uma nova aeronave e aloca memória
Aeronaves* criar_aeronave(void);

// Inicializa uma aeronave com dados
Aeronaves* init_aeronave(const char *identifier, const char *manufacturer,
                         const char *model, const char *year, const char *capacity, const char *range);

// Liberta a memória associada a uma aeronave
void free_aeronave(Aeronaves *a);

void print_aeronave_formatada(const Aeronaves *a);

// GETTERS - Funções para obter valores

const char* get_identifier_aeronave(const Aeronaves *a);
const char* get_manufacturer_aeronave(const Aeronaves *a);
const char* get_model_aeronave(const Aeronaves *a);
const char* get_year_aeronave(const Aeronaves *a);
const char* get_capacity_aeronave(const Aeronaves *a);
const char* get_range_aeronave(const Aeronaves *a);


// SETTERS - Funções para definir valores

void set_identifier_aeronave(Aeronaves *a, const char *identifier);
void set_manufacturer_aeronave(Aeronaves *a, const char *manufacturer);
void set_model_aeronave(Aeronaves *a, const char *model);
void set_year_aeronave(Aeronaves *a, const char *year);
void set_capacity_aeronave(Aeronaves *a, const char *capacity);
void set_range_aeronave(Aeronaves *a, const char *range);


#endif
