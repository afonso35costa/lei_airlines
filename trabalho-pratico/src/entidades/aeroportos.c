#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "aeroportos.h"

typedef struct aeroportos {
    char *code;        // código IATA do aeroporto (ex: "OPO")
    char *name;        // nome do aeroporto
    char *city;        // cidade
    char *country;     // país
    double latitude;   // latitude em graus decimais
    double longitude;  // longitude em graus decimais
    char *icao;        // código ICAO
    char *type;        // tipo do aeroporto (small_airport, large_airport, etc.)
} Aeroportos;

// FUNÇÃO CONSTRUTORA - Cria uma aeronave e aloca memória


Aeroportos* create_aeroporto(void) {
    Aeroportos *a = malloc(sizeof(Aeroportos));
    if (!a) return NULL;

    a->code = NULL;
    a->name = NULL;
    a->city = NULL;
    a->country = NULL;
    a->latitude = 0.0;
    a->longitude = 0.0;
    a->icao = NULL;
    a->type = NULL;

    return a;
}


// FUNÇÃO INICIALIZADORA


Aeroportos* init_aeroporto(const char *code, const char *name, const char *city,
                           const char *country, double latitude, double longitude,
                           const char *icao, const char *type) {
    Aeroportos *a = create_aeroporto();
    if (!a) return NULL;

    a->code = code ? strdup(code) : NULL;
    a->name = name ? strdup(name) : NULL;
    a->city = city ? strdup(city) : NULL;
    a->country = country ? strdup(country) : NULL;
    a->latitude = latitude;
    a->longitude = longitude;
    a->icao = icao ? strdup(icao) : NULL;
    a->type = type ? strdup(type) : NULL;

    return a;
}

// FUNÇÃO DE IMPRESSÃO 

void print_aeroporto_detalhado(const Aeroportos *a) {
    if (a == NULL) {
        printf("Aeroporto inválido\n");
        return;
    }
    
    printf("=== AEROPORTO ===\n");
    printf("Código IATA: %s\n", get_code_aeroporto(a) ? get_code_aeroporto(a) : "N/A");
    printf("Nome: %s\n", get_name_aeroporto(a) ? get_name_aeroporto(a) : "N/A");
    printf("Cidade: %s\n", get_city_aeroporto(a) ? get_city_aeroporto(a) : "N/A");
    printf("País: %s\n", get_country_aeroporto(a) ? get_country_aeroporto(a) : "N/A");
    printf("Latitude: %.6f\n", get_latitude_aeroporto(a));
    printf("Longitude: %.6f\n", get_longitude_aeroporto(a));
    printf("Código ICAO: %s\n", get_icao_aeroporto(a) ? get_icao_aeroporto(a) : "N/A");
    printf("Tipo: %s\n", get_type_aeroporto(a) ? get_type_aeroporto(a) : "N/A");
    printf("==================\n");
}
// FUNÇÃO DE LIBERTAÇÃO DE MEMÓRIA

void destroy_aeroporto(Aeroportos *a) {
    if (!a) return;

    free(a->code);
    free(a->name);
    free(a->city);
    free(a->country);
    free(a->icao);
    free(a->type);
    free(a);
}

// GETTERS

const char* get_code_aeroporto(const Aeroportos *a) {
    return a ? a->code : NULL;
}

const char* get_name_aeroporto(const Aeroportos *a) {
    return a ? a->name : NULL;
}

const char* get_city_aeroporto(const Aeroportos *a) {
    return a ? a->city : NULL;
}

const char* get_country_aeroporto(const Aeroportos *a) {
    return a ? a->country : NULL;
}

double get_latitude_aeroporto(const Aeroportos *a) {
    return a ? a->latitude : 0.0;
}

double get_longitude_aeroporto(const Aeroportos *a) {
    return a ? a->longitude : 0.0;
}

const char* get_icao_aeroporto(const Aeroportos *a) {
    return a ? a->icao : NULL;
}

const char* get_type_aeroporto(const Aeroportos *a) {
    return a ? a->type : NULL;
}

// SETTERS

void set_code_aeroporto(Aeroportos *a, const char *code) {
    if (!a) return;
    free(a->code);
    a->code = code ? strdup(code) : NULL;
}

void set_name_aeroporto(Aeroportos *a, const char *name) {
    if (!a) return;
    free(a->name);
    a->name = name ? strdup(name) : NULL;
}

void set_city_aeroporto(Aeroportos *a, const char *city) {
    if (!a) return;
    free(a->city);
    a->city = city ? strdup(city) : NULL;
}

void set_country_aeroporto(Aeroportos *a, const char *country) {
    if (!a) return;
    free(a->country);
    a->country = country ? strdup(country) : NULL;
}

void set_latitude_aeroporto(Aeroportos *a, double latitude) {
    if (a) a->latitude = latitude;
}

void set_longitude_aeroporto(Aeroportos *a, double longitude) {
    if (a) a->longitude = longitude;
}

void set_icao_aeroporto(Aeroportos *a, const char *icao) {
    if (!a) return;
    free(a->icao);
    a->icao = icao ? strdup(icao) : NULL;
}

void set_type_aeroporto(Aeroportos *a, const char *type) {
    if (!a) return;
    free(a->type);
    a->type = type ? strdup(type) : NULL;
}
