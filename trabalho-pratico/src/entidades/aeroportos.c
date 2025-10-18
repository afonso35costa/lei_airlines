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