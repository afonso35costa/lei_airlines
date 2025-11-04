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
    a->identifier   = identifier   ? strdup(identifier)   : NULL;
    a->manufacturer = manufacturer ? strdup(manufacturer) : NULL;
    a->model        = model        ? strdup(model)        : NULL;

    a->year = year;
    a->capacity = capacity;
    a->range = range;

    return a;
}


// FUNÇÃO DE IMPRESSÃO (para debug)

void print_aeronave(Aeronaves *a) {
    if (a == NULL) {
        printf("Aeronave inválida.\n");
        return;
    }

    printf("Identificador: %s | Fabricante: %s | Modelo: %s | Ano: %d | Capacidade: %d | Alcance: %d km\n",
           a->identifier ? a->identifier : "(null)",
           a->manufacturer ? a->manufacturer : "(null)",
           a->model ? a->model : "(null)",
           a->year,
           a->capacity,
           a->range);
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

const char* get_identifier(const Aeronaves *a) {
    return a ? a->identifier : NULL;
}

const char* get_manufacturer(const Aeronaves *a) {
    return a ? a->manufacturer : NULL;
}

const char* get_model(const Aeronaves *a) {
    return a ? a->model : NULL;
}

int get_year(const Aeronaves *a) {
    return a ? a->year : 0;
}

int get_capacity(const Aeronaves *a) {
    return a ? a->capacity : 0;
}

int get_range(const Aeronaves *a) {
    return a ? a->range : 0;
}


// SETTERS

void set_identifier(Aeronaves *a, const char *identifier) {
    if (!a) return;
    free(a->identifier);
    a->identifier = identifier ? strdup(identifier) : NULL;
}

void set_manufacturer(Aeronaves *a, const char *manufacturer) {
    if (!a) return;
    free(a->manufacturer);
    a->manufacturer = manufacturer ? strdup(manufacturer) : NULL;
}

void set_model(Aeronaves *a, const char *model) {
    if (!a) return;
    free(a->model);
    a->model = model ? strdup(model) : NULL;
}

void set_year(Aeronaves *a, int year) {
    if (a) a->year = year;
}

void set_capacity(Aeronaves *a, int capacity) {
    if (a) a->capacity = capacity;
}

void set_range(Aeronaves *a, int range) {
    if (a) a->range = range;
}