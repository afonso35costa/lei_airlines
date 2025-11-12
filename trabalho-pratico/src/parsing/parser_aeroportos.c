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
    printf("[DEBUG] Entrou em parse_aeroporto_line\n");
    if (!line) {
        printf("[DEBUG] line é NULL\n");
        return NULL;
    }

    fprintf(stderr, "[DEBUG] line antes de strdup: '%s'\n", line);
    size_t len = strlen(line) + 1;
    char *temp = malloc(len);
    if (!temp) { perror("malloc"); exit(1); }
    memcpy(temp, line, len);
    if (!temp) {
        fprintf(stderr, "[ERRO] Falha ao duplicar line\n");
        return NULL;
    }


    if (!temp) {
        printf("[DEBUG] Falha ao duplicar line\n");
        return NULL;
    }

    printf("[DEBUG] Linha duplicada: '%s'\n", temp);

    char *token, *rest = temp;
    char *campos[8] = {0};
    int i = 0;

    while ((token = strsep(&rest, ",")) != NULL && i < 8) {
        campos[i] = strip_quotes(token);
        printf("[DEBUG] campo[%d]='%s'\n", i, campos[i]);
        i++;
    }

    if (i < 8) {
        printf("[DEBUG] Menos de 8 campos lidos: %d\n", i);
        for (int j = 0; j < i; j++) free(campos[j]);
        free(temp);
        return NULL;
    }

    double latitude = atof(campos[4]);
    double longitude = atof(campos[5]);
    printf("[DEBUG] latitude=%f, longitude=%f\n", latitude, longitude);

    Aeroportos *a = init_aeroporto(campos[0], campos[1], campos[2], campos[3],
                                   latitude, longitude, campos[6], campos[7]);

    for (int j = 0; j < 8; j++) free(campos[j]);
    free(temp);

    printf("[DEBUG] parse_aeroporto_line retornando struct\n");
    return a;
}

// parse_and_validate_aeroporto_line com debug
Aeroportos *parse_and_validate_aeroporto_line(const char *line, FILE *ferr) {
    printf("[DEBUG] Entrou em parse_and_validate_aeroporto_line\n");

    if (!line || strlen(line) == 0) {
        printf("[DEBUG] Linha vazia ou NULL\n");
        return NULL;
    }

    Aeroportos *a = parse_aeroporto_line(line);
    if (!a) {
        printf("[DEBUG] parse_aeroporto_line retornou NULL\n");
        if (ferr) fprintf(ferr, "%s\n", line);
        return NULL;
    }

    printf("[DEBUG] Aeroporto criado, validando...\n");

    if (!validar_aeroporto(a)) {
        printf("[DEBUG] Aeroporto inválido\n");
        if (ferr) fprintf(ferr, "%s\n", line);
        free_aeroporto(a);
        return NULL;
    }

    printf("[DEBUG] Aeroporto válido retornando\n");
    return a;
}
