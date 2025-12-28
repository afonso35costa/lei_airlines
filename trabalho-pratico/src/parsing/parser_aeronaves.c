#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aeronaves.h"
#include "validacao_aeronaves.h"
#include "parser_utils.h"
#include "parser_aeronaves.h"

#define ERRO_FILE "resultados/aeronaves_errors.csv"

Aeronaves *parse_aeronave_line(const char *line) {
    if (!line) return NULL;

    char *temp = strdup(line);
    if (!temp) return NULL;

    char *rest = temp;
    char *token = strsep(&rest, ",");
    char *campos[6] = {0};
    int i = 0;

    while ((token) != NULL && i < 6) {
        campos[i] = strip_quotes(token);
        i++;
        token = strsep(&rest, ",");
    }

    Aeronaves *a = init_aeronave(campos[0], campos[1], campos[2], campos[3], campos[4], campos[5]);

    for (int j = 0; j < 6; j++) free(campos[j]);
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
        destroy_aeronave(a);
        return NULL;
    } 

    return a;  // válido ✅
}
