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

// FUNÇÃO DE IMPRESSÃO (para debug)

void print_aeroporto(const Aeroportos *a) {
    if (!a) return;

    printf("IATA: %s | ICAO: %s | Nome: %s | Cidade: %s | País: %s | Tipo: %s | "
           "Lat: %.4f | Lon: %.4f\n",
           a->code ? a->code : "(null)",
           a->icao ? a->icao : "(null)",
           a->name ? a->name : "(null)",
           a->city ? a->city : "(null)",
           a->country ? a->country : "(null)",
           a->type ? a->type : "(null)",
           a->latitude, a->longitude);
}

// FUNÇÃO DE LIBERTAÇÃO DE MEMÓRIA

void free_aeroporto(Aeroportos *a) {
    if (!a) return;

    free(a->code);
    free(a->name);
    free(a->city);
    free(a->country);
    free(a->icao);
    free(a->type);
    free(a);
}

/ GETTERS

const char* get_code(const Aeroportos *a) {
    return a ? a->code : NULL;
}

const char* get_name(const Aeroportos *a) {
    return a ? a->name : NULL;
}

const char* get_city(const Aeroportos *a) {
    return a ? a->city : NULL;
}

const char* get_country(const Aeroportos *a) {
    return a ? a->country : NULL;
}

double get_latitude(const Aeroportos *a) {
    return a ? a->latitude : 0.0;
}

double get_longitude(const Aeroportos *a) {
    return a ? a->longitude : 0.0;
}

const char* get_icao(const Aeroportos *a) {
    return a ? a->icao : NULL;
}

const char* get_type(const Aeroportos *a) {
    return a ? a->type : NULL;
}

// SETTERS

void set_code(Aeroportos *a, const char *code) {
    if (!a) return;
    free(a->code);
    a->code = code ? strdup(code) : NULL;
}

void set_name(Aeroportos *a, const char *name) {
    if (!a) return;
    free(a->name);
    a->name = name ? strdup(name) : NULL;
}

void set_city(Aeroportos *a, const char *city) {
    if (!a) return;
    free(a->city);
    a->city = city ? strdup(city) : NULL;
}

void set_country(Aeroportos *a, const char *country) {
    if (!a) return;
    free(a->country);
    a->country = country ? strdup(country) : NULL;
}

void set_latitude(Aeroportos *a, double latitude) {
    if (a) a->latitude = latitude;
}

void set_longitude(Aeroportos *a, double longitude) {
    if (a) a->longitude = longitude;
}

void set_icao(Aeroportos *a, const char *icao) {
    if (!a) return;
    free(a->icao);
    a->icao = icao ? strdup(icao) : NULL;
}

void set_type(Aeroportos *a, const char *type) {
    if (!a) return;
    free(a->type);
    a->type = type ? strdup(type) : NULL;
}
