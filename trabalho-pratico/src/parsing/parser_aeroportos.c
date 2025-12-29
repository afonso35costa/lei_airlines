#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aeroportos.h"
#include "validacao_aeroportos.h"
#include "parser_utils.h"
#include "parser_aeroportos.h"

#define ERRO_FILE "resultados/aeroportos_errors.csv"

Aeroportos *parse_aeroporto_line(const char *line) {
    if (!line) {
        return NULL;
    }

    size_t len = strlen(line) + 1;
    char *temp = malloc(len);
    if (!temp) { perror("malloc"); exit(1); }
    memcpy(temp, line, len);

    char *rest = temp;
    char *campos[8] = {0};
    int i = 0;

    while (rest && i < 8) {
        campos[i] = ignorar_virgulas(&rest);
        i++;
    }
    // ---------------------------------------------

    char *endptr_lat, *endptr_lon;
    double latitude  = strtod(campos[4], &endptr_lat);
    double longitude = strtod(campos[5], &endptr_lon);

    // Verifica se há caracteres inválidos
    if (*endptr_lat != '\0' || *endptr_lon != '\0') {
        for (int j = 0; j < 8; j++) free(campos[j]);
        free(temp);
        return NULL;  // Coordenadas inválidas
    }

    Aeroportos *a = init_aeroporto(campos[0], campos[1], campos[2], campos[3],
                                   latitude, longitude, campos[6], campos[7]);

    for (int j = 0; j < 8; j++) free(campos[j]);
    free(temp);

    return a;
}

// parse_and_validate_aeroporto_line com debug
Aeroportos *parse_and_validate_aeroporto_line(const char *line, FILE *ferr) {

    if (!line || strlen(line) == 0) {
        return NULL;
    }

    Aeroportos *a = parse_aeroporto_line(line);
    if (!a) {
        if (ferr) fprintf(ferr, "%s\n", line);
        return NULL;
    }

    if (!validar_aeroporto(a)) {
        if (ferr) fprintf(ferr, "%s\n", line);
        destroy_aeroporto(a);
        return NULL;
    } 
    return a;
}
