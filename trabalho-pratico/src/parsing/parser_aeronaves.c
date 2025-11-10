#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser_aeronaves.h"
#include "aeronaves.h"

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

    Aeronaves *a = criar_aeronave(campos[0], campos[1], campos[2], year, capacity, range);

    free(temp);
    return a;
}
