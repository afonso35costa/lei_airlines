#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser_utils.h"
#include "aeroportos.h"

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
