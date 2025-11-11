#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "validacao_aeronaves.h"
#include "aeronaves.h"

// VALIDAÇÕES INDIVIDUAIS


int validar_identifier(const char *identifier) {
    // Exemplo simples: matrícula não pode ser vazia e deve ter letras/números
    if (!identifier || strlen(identifier) < 3) return 0;
    for (int i = 0; identifier[i]; i++) {
        if (!isalnum(identifier[i]) && identifier[i] != '-') return 0;
    }
    return 1;
}

int validar_manufacturer(const char *manufacturer) {
    return manufacturer && strlen(manufacturer) > 1;
}

int validar_model(const char *model) {
    return model && strlen(model) > 0;
}

int validar_year(int year) {
    return (year >= 1950 && year <= 2025);
}

int validar_capacity(int capacity) {
    return (capacity > 0 && capacity <= 1000);
}

int validar_range(int range) {
    return (range > 100 && range <= 20000);
}


// VALIDAÇÃO GERAL 

int validar_aeronave(const Aeronaves *a) {
    if (!a) return 0;

    return validar_identifier(get_identifier(a)) &&
           validar_manufacturer(get_manufacturer(a)) &&
           validar_model(get_model(a)) &&
           validar_year(get_year(a)) &&
           validar_capacity(get_capacity(a)) &&
           validar_range(get_range(a));
}

