#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser_voos.h"
#include "voos.h"
#include "datas.h"

Voo *parse_voo_line(const char *line) {
    if (!line) return NULL;

    char *temp = strdup(line);
    if (!temp) return NULL;

    char *token, *rest = temp;
    char *campos[12]; int i = 0;

    while ((token = strsep(&rest, ",")) != NULL && i < 12)
        campos[i++] = strip_quotes(token);

    if (i < 12) { free(temp); return NULL; }

    DataHora dep = ler_data_hora(campos[1]);
    DataHora act_dep = ler_data_hora(campos[2]);
    DataHora arr = ler_data_hora(campos[3]);
    DataHora act_arr = ler_data_hora(campos[4]);

    Voo *v = voo_create(campos[0], &dep, &act_dep, &arr, &act_arr,
                        campos[5], campos[6], campos[7], campos[8],
                        campos[9], campos[10], campos[11]);

    free(temp);
    return v;
}
