#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "aeronaves.h"

typedef struct aeronaves {
    char *identifier;     // identificador único (tail number) 
    char *manufacturer;   // fabricante
    char *model;          // modelo
    char *year;             // ano de fabrico
    char *capacity;         // capacidade máxima de passageiros
    char *range;            // alcance máximo em km
    int num_voos;           // Numero de voos
} Aeronaves;


// FUNÇÃO CONSTRUTORA - Cria uma aeronave e aloca memória

Aeronaves* criar_aeronave(void) {
    Aeronaves *a = malloc(sizeof(Aeronaves));
    if (a == NULL) {
        return NULL;
    }

    // Inicializa todos os ponteiros como NULL
    a->identifier   = NULL;
    a->manufacturer = NULL;
    a->model        = NULL;
    a->year        = NULL;
    a->capacity        = NULL;
    a->range        = NULL;

    return a;
}


// FUNÇÃO INICIALIZADORA - Inicializa uma aeronave com valores
Aeronaves* init_aeronave(const char *identifier, const char *manufacturer, const char *model, const char *year, const char *capacity, const char *range) {
    Aeronaves *a = criar_aeronave();
    if (a == NULL) return NULL;

    a->identifier   = identifier  ? strdup(identifier)  : NULL;
    a->manufacturer = manufacturer ? strdup(manufacturer) : NULL;
    a->model = model ? strdup(model) : NULL;
    a->year = year ? strdup(year) : NULL;
    a->capacity = capacity ? strdup(capacity) : NULL;
    a->range = range ? strdup(range) : NULL;
    a->num_voos     = 0;

    return a;
}


// FUNÇÃO DE LIBERTAÇÃO DE MEMÓRIA

void destroy_aeronave(Aeronaves *a) {
    if (a == NULL) return;

    free(a->identifier);
    free(a->manufacturer);
    free(a->model);
    free(a);
}

void free_unused(Aeronaves *a) {
    if (!a) return;
    free(a->year);
    free(a->capacity);
    free(a->range);
}

// GETTERS

const char* get_identifier_aeronave(const Aeronaves *a) {
    return a ? a->identifier : NULL;
}

const char* get_manufacturer_aeronave(const Aeronaves *a) {
    return a ? a->manufacturer : NULL;
}

const char* get_model_aeronave(const Aeronaves *a) {
    return a ? a->model : NULL;
}

const char* get_year_aeronave(const Aeronaves *a) {
    return a ? a->year : NULL;
}

const char* get_capacity_aeronave(const Aeronaves *a) {
    return a ? a->capacity : NULL;
}

const char* get_range_aeronave(const Aeronaves *a) {
    return a ? a->range : NULL;
}

int get_num_voos_aeronave(const Aeronaves *a) {
    return a ? a->num_voos : -1;
}

// SETTERS

void set_identifier_aeronave(Aeronaves *a, const char *identifier) {
    if (!a) return;
    free(a->identifier);
    a->identifier = identifier ? strdup(identifier):NULL;
}

void set_manufacturer_aeronave(Aeronaves *a, const char *manufacturer) {
    if (!a) return;
    free(a->manufacturer);
    a->manufacturer = manufacturer ? strdup(manufacturer):NULL ;
}

void set_model_aeronave(Aeronaves *a, const char *model) {
    if (!a) return;
    free(a->model);
    a->model = model ? strdup(model) : NULL;
}

void set_year_aeronave(Aeronaves *a, const char *year) {
    if (!a) return;
    free(a->year);
    a->year = year ? strdup(year) : NULL;
}

void set_capacity_aeronave(Aeronaves *a, const char *capacity) {
    if (!a) return;
    free(a->capacity);
    a->capacity = capacity ? strdup(capacity) : NULL;
}

void set_range_aeronave(Aeronaves *a, const char *range) {
    if (!a) return;
    free(a->range);
    a->range = range ? strdup(range) : NULL;
}

void set_num_voos_aeronave(Aeronaves *a, int num_voos) {
    if (!a) return;
    a->num_voos = num_voos;
}