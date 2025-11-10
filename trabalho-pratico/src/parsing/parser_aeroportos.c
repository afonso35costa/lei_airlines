#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aeroportos.h"
#include "validacao_aeroportos.h"

#define ERRO_FILE "resultados/aeroportos_errors.csv"

Aeroportos *parse_aeroporto_line(const char *line) {
    if (!line) return NULL;
    char *temp = strdup(line);
    if (!temp) return NULL;

    char *token, *rest = temp;
    char *campos[8]; int i = 0;

    while ((token = strsep(&rest, ",")) != NULL && i < 8)
        campos[i++] = strip_quotes(token);

    if (i < 8) { free(temp); return NULL; }

    double latitude = atof(campos[4]);
    double longitude = atof(campos[5]);

    Aeroportos *a = criar_aeroporto(campos[0], campos[1], campos[2], campos[3],
                                    latitude, longitude, campos[6], campos[7]);

    free(temp);
    return a;
}

Aeroportos *parse_and_validate_aeroporto_line(const char *line, int is_header) {
    if (!line || strlen(line) == 0)
        return NULL;

    // Se for a primeira linha (header), cria ficheiro e escreve o header
    if (is_header) {
        FILE *ferr = fopen(ERRO_FILE, "w");
        if (ferr) {
            fprintf(ferr, "%s\n", line);
            fclose(ferr);
        }
        return NULL;
    }

    // Faz o parsing (sintaticamente, sabemos que não falha)
    Aeroportos *a = parse_aeroporto_line(line);

    // Validação de conteúdo
    if (!validar_aeroporto(a)) {
        FILE *ferr = fopen(ERRO_FILE, "a");
        if (ferr) {
            fprintf(ferr, "%s\n", line);  // escreve linha original no ficheiro de erros
            fclose(ferr);
        }

        // Liberta memória da estrutura inválida
        free(a);
        return NULL;
    }

    return a;  // válido ✅
}
