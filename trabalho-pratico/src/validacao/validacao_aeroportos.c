#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "validacao_aeroportos.h"
#include "aeroportos.h"


// VALIDAÇÕES INDIVIDUAIS

int validar_type_aeroporto (const char *type) {
    if (!type) return 0; // Verifica se o ponteiro é nulo
    if (strcmp(type, "small_airport") == 0 ||
        strcmp(type, "medium_airport") == 0 ||
        strcmp(type, "large_airport") == 0 ||
        strcmp(type, "heliport") == 0 ||
        strcmp(type, "seaplane_base") == 0) {
        return 1; 
    }
    return 0;
}



int validar_latitude_aeroporto (double latitude) {
    if (isnan(latitude)) return 0;
    return (latitude >= -90.0 && latitude <= 90.0);
}


int validar_longitude_aeroporto (double longitude) {
    if (isnan(longitude)) return 0;
    return (longitude >= -180.0 && longitude <= 180.0);
}

int validar_code_aeroporto(const char *code) {
    // Código IATA = 3 letras
    if (!code || strlen(code) != 3) return 0;
    for (int i = 0; i < 3; i++) {
        if (!isalpha(code[i])) return 0;  // verifica se são letras maisculas no intervalo de A-Z
    }
    return 1;
}


// VALIDAÇÃO GERAL (com encapsulamento)

int validar_aeroporto(const Aeroportos *a) {
    if (!a) return 0;

    return validar_type_aeroporto(get_type_aeroporto(a)) &&
           validar_latitude_aeroporto(get_latitude_aeroporto(a)) &&
           validar_longitude_aeroporto(get_longitude_aeroporto(a)) &&
           validar_code_aeroporto(get_code_aeroporto(a));
}
