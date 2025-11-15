#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "validacao_aeronaves.h"
#include "aeronaves.h"

// VALIDAÇÕES INDIVIDUAIS

/*
int validar_identifier(const char *identifier) {

    if (!identifier || strlen(identifier) != 8)
        return 0;

    for (int i = 0; i < 2; i++) {
        if (!isalnum(identifier[i]))
            return 0;
    }

    if (identifier[2] != '-')
        return 0;

    for (int i = 3; i < 8; i++) {
        if (!isalnum(identifier[i]))
            return 0;
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
    return (year >= 1900 && year <= 2025);
}

int validar_capacity(int capacity) {
    return (capacity > 0 && capacity <= 1000);
}

int validar_range(int range) {
    return (range > 100 && range <= 20000);
}
*/

int validar_ano_aeronave(const char *anoA) {
    if (!anoA || strlen(anoA) != 4) return 0;  // Verifica se tem 4 caracteres
    
    for (int i = 0; i < 4; i++) {
        if (!isdigit(anoA[i])) return 0;     // Verifica se todos são números, se encontrar algum digito retorna 0
    }
    
    int year;
    if (sscanf(anoA, "%d", &year) != 1) return 0;
    if (year < 1900 || year > 2025) return 0;
    
    return 1;
}

// VALIDAÇÃO GERAL 

int validar_aeronave(const Aeronaves *a) {
    if (!a) return 0;

    return validar_ano_aeronave(get_year_aeronave(a));
}
