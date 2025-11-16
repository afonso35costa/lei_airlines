#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "aeronaves.h"

typedef struct aeronaves {
    char *identifier;     // identificador único (tail number)
    char *manufacturer;   // fabricante
    char *model;          // modelo
    int year;             // ano de fabrico
    int capacity;         // capacidade máxima de passageiros
    int range;            // alcance máximo em km
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
    a->year         = 0;
    a->capacity     = 0;
    a->range        = 0;

    return a;
}


// FUNÇÃO INICIALIZADORA - Inicializa uma aeronave com valores

Aeronaves* init_aeronave(const char *identifier, const char *manufacturer,
                         const char *model, int year, int capacity, int range) {
    Aeronaves *a = criar_aeronave();
    if (a == NULL) return NULL;

    // Copia cada string (duplica para evitar dangling pointers)
    set_identifier_aeronave(a, identifier);
    set_manufacturer_aeronave(a, manufacturer);
    set_model_aeronave(a, model);
    set_year_aeronave(a, year);
    set_capacity_aeronave(a, capacity);
    set_range_aeronave(a, range);

    return a;
}


// FUNÇÃO DE IMPRESSÃO 

void print_aeronave_formatada(const Aeronaves *a) {
    if (a == NULL) {
        printf("Aeronave inválida\n");
        return;
    }
    
    printf("=== AERONAVE ===\n");
    printf("Identificador: %s\n", get_identifier_aeronave(a) ? get_identifier_aeronave(a) : "N/A");
    printf("Fabricante: %s\n", get_manufacturer_aeronave(a) ? get_manufacturer_aeronave(a) : "N/A");
    printf("Modelo: %s\n", get_model_aeronave(a) ? get_model_aeronave(a) : "N/A");
    printf("Ano: %d\n", get_year_aeronave(a));
    printf("Capacidade: %d\n", get_capacity_aeronave(a));
    printf("Alcance: %d km\n", get_range_aeronave(a));
    printf("=================\n");
}


// FUNÇÃO DE LIBERTAÇÃO DE MEMÓRIA

void free_aeronave(Aeronaves *a) {
    if (a == NULL) return;

    free(a->identifier);
    free(a->manufacturer);
    free(a->model);
    free(a);
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

int get_year_aeronave(const Aeronaves *a) {
    return a ? a->year : 0;
}

int get_capacity_aeronave(const Aeronaves *a) {
    return a ? a->capacity : 0;
}

int get_range_aeronave(const Aeronaves *a) {
    return a ? a->range : 0;
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

void set_year_aeronave(Aeronaves *a, const int year) {
    if (!a) return;
    a->year = year;
}

void set_capacity_aeronave(Aeronaves *a, const int capacity) {
    if (!a) return;
    a->capacity = capacity;
}

void set_range_aeronave(Aeronaves *a, const int range) {
    if (!a) return;
    a->range = range;
}