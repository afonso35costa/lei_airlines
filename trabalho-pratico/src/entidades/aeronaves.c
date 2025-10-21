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
    Aeronaves *aeronave = (Aeronaves *)malloc(sizeof(Aeronaves));
    aeronave->identifier = identifier;
    aeronave->manufacturer = manufacturer;
    aeronave->model = model;
    aeronave->year = year;
    aeronave->capacity = capacity;
    aeronave->range = range;
    return aeronave;
}
