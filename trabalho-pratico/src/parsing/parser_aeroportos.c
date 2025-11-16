#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aeroportos.h"
#include "validacao_aeroportos.h"
#include "parser_utils.h"
#include "parser_aeroportos.h"

#define ERRO_FILE "resultados/aeroportos_errors.csv"

// parse_aeroporto_line com debug
Aeroportos *parse_aeroporto_line(const char *line) {
    if (!line) {
        return NULL;
    }

    size_t len = strlen(line) + 1;
    char *temp = malloc(len);
    if (!temp) { perror("malloc"); exit(1); }
    memcpy(temp, line, len);
    if (!temp) {
        return NULL;
    }


    if (!temp) {
        return NULL;
    }

    char *rest = temp;
    char *token = strsep(&rest, ",");
    char *campos[8] = {0};
    int i = 0;

    while ((token) != NULL && i < 8) {
        campos[i] = strip_quotes(token);
        i++;
        token = strsep(&rest, ",");
    }
// Comentar esta parte
    if (i < 8) {
        for (int j = 0; j < i; j++) free(campos[j]);
        free(temp);
        return NULL;
    }

    double latitude = atof(campos[4]);
    double longitude = atof(campos[5]);

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
        free_aeroporto(a);
        return NULL;
    }
    return a;
}
