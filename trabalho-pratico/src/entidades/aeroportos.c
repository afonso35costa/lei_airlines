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

Aeroportos* criar_aeroporto(char *code, char *name, char *city,
                             char *country, double latitude,
                             double longitude, char *icao,
                             char *type) {
    // Aloca memória para a estrutura 'Aeroportos'
    Aeroportos *aeroporto = (Aeroportos *)malloc(sizeof(Aeroportos));
    
    // Inicializa os campos da estrutura com os valores fornecidos
    aeroporto->code = code;
    aeroporto->name = name;
    aeroporto->city = city;
    aeroporto->country = country;
    aeroporto->latitude = latitude;
    aeroporto->longitude = longitude;
    aeroporto->icao = icao;
    aeroporto->type = type;
    
    // Retorna o ponteiro para a estrutura criada
    return aeroporto;
}

