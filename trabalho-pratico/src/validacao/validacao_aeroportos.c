#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "validacao_aeroportos.h"
#include "aeroportos.h"

/*
// VALIDAÇÕES INDIVIDUAIS

int validar_code(const char *code) {
    // Código IATA = 3 letras
    if (!code || strlen(code) != 3) return 0;
    for (int i = 0; i < 3; i++) {
        if (!isalpha(code[i])) return 0;
    }
    return 1;
}

int validar_name(const char *name) {
    return name && strlen(name) > 2;
}

int validar_city(const char *city) {
    return city && strlen(city) > 1;
}

int validar_country(const char *country) {
    if (!country || strlen(country) != 2) return 0;
    for (int i = 0; i < 2; i++) {
        if (!isalpha(country[i])) return 0;
    }
    return 1;
}

int validar_latitude(double latitude) {
    return (latitude >= -90.0 && latitude <= 90.0);
}


int validar_longitude(double longitude) {
    return longitude >= -180.0 && longitude <= 180.0;
}

int validar_icao(const char *icao) {
    if (!icao || strlen(icao) != 4) return 0;
    for (int i = 0; i < 4; i++) {
        if (!isalpha(icao[i])) return 0;
    }
    return 1;
}

int validar_type(const char *type) {
    if (!type) return 0; // Verifica se o ponteiro é nulo

    const char *tipos_validos[] = {
        "small_airport",
        "medium_airport",
        "large_airport",
        "heliport",
        "seaplane_base"
    };

    int num_tipos = sizeof(tipos_validos) / sizeof(tipos_validos[0]);

    for (int i = 0; i < num_tipos; i++) {
        if (strcmp(type, tipos_validos[i]) == 0) {
            return 1; 
        }
    }

    return 0;
}

*/

// VALIDAÇÕES INDIVIDUAIS

int validar_type_aeroporo (const char *type) {
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
    // Verifica se está no intervalo válido
    if (latitude < -90.0 || latitude > 90.0) return 0;
    
    // Verifica se tem no máximo 8 casas decimais
    // Multiplica por 10^8 e verifica se o resultado é um inteiro
    double scaled = latitude * 100000000.0; // 10^8
    return (scaled == (long long)scaled);
}

int validar_longitude_aeroporto (double longitude) {
    return longitude >= -180.0 && longitude <= 180.0;
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

    return validar_type_aeroporo(get_type_aeroporto(a)) &&
           validar_latitude_aeroporto(get_latitude_aeroporto(a)) &&
           validar_longitude_aeroporto(get_longitude_aeroporto(a)) &&
           validar_code_aeroporto(get_code_aeroporto(a));
}
