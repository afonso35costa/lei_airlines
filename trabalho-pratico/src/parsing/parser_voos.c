#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "voos.h"
#include "datas.h"
#include "validacao_voos.h"
#include "parser_voos.h"
#include "parser_utils.h"

#define ERRO_FILE "resultados/voos_errors.csv"

Voo *parse_voo_line(const char *line) {
    if (!line) return NULL;

    char *temp = strdup(line);
    if (!temp) return NULL;

    char *rest = temp;
    char *token = strsep(&rest, ",");
    char *campos[12] = {0};
    int i = 0;

    while ((token) != NULL && i < 12) {
        campos[i] = strip_quotes(token);
        i++;
        token = strsep(&rest, ",");
    }

    DataHora *dep = ler_data_hora(campos[1]);
    DataHora *act_dep = ler_data_hora(campos[2]);
    DataHora *arr = ler_data_hora(campos[3]);
    DataHora *act_arr = ler_data_hora(campos[4]);

    Voo *v = init_voo(campos[0], dep, act_dep, arr, act_arr,
                        campos[5], campos[6], campos[7], campos[8],
                        campos[9], campos[10], campos[11]);

    free(temp);
    return v;
}

Voo *parse_and_validate_voo_line(const char *line, FILE *ferr) {
    if (!line || strlen(line) == 0)
        return NULL;

    // Parsing sintático (sempre válido estruturalmente)
    Voo *v = parse_voo_line(line);

    // Validação semântica
     if (!validar_voo(v)) {
        if (ferr) {
            fprintf(ferr, "%s\n", line);  // só escreve a linha inválida
        }
        destroy_voo(v);
        return NULL;
    }

    return v;  // válido ✅
}
