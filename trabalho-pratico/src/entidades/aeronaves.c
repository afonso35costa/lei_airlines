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

Aeronaves* criar_aeronave(char *identifier, char *manufacturer,
                           char *model, int year,
                           int capacity, int range) {
    
    // Aloca memória para a estrutura 'Aeronaves'
    Aeronaves *aeronave = (Aeronaves *)malloc(sizeof(Aeronaves));
    
    // Inicializa os campos da estrutura com os valores fornecidos
    aeronave->identifier = identifier;
    aeronave->manufacturer = manufacturer;
    aeronave->model = model;
    aeronave->year = year;
    aeronave->capacity = capacity;
    aeronave->range = range;
    
    // Retorna o ponteiro para a estrutura criada
    return aeronave;
}

