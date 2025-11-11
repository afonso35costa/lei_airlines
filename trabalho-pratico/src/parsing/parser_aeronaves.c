#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aeronaves.h"
#include "validacao_aeronaves.h"

#define ERRO_FILE "resultados/aeronaves_errors.csv"

Aeronaves *parse_aeronave_line(const char *line) {
    if (!line) return NULL;

    char *temp = strdup(line);
    if (!temp) return NULL;

    char *token, *rest = temp;
    char *campos[6]; int i = 0;

    while ((token = strsep(&rest, ",")) != NULL && i < 6)
        campos[i++] = strip_quotes(token);

    if (i < 6) { free(temp); return NULL; }

    int year = atoi(campos[3]);
    int capacity = atoi(campos[4]);
    int range = atoi(campos[5]);

    Aeronaves *a = init_aeronave(campos[0], campos[1], campos[2], year, capacity, range);

    free(temp);
    return a;
}

Aeronaves *parse_and_validate_aeronave_line(const char *line, FILE *ferr) {
    if (!line || strlen(line) == 0)
        return NULL;

    // Parsing sintático (sempre válido estruturalmente)
    Aeronaves *a = parse_aeronave_line(line);

    // Validação semântica
     if (!validar_aeronave(a)) {
        if (ferr) {
            fprintf(ferr, "%s\n", line);  // só escreve a linha inválida
        }
        aeronave_free(a);
        return NULL;
    }

    return a;  // válido ✅
}
