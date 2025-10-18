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
