#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser_utils.h"
#include "passageiros.h"

Passageiros *parse_passageiro_line(const char *line) {
    if (!line) return NULL;

    char *temp = strdup(line);
    if (!temp) return NULL;

    char *token, *rest = temp;
    char *campos[10]; int i = 0;

    while ((token = strsep(&rest, ",")) != NULL && i < 10)
        campos[i++] = strip_quotes(token);

    if (i < 10) { free(temp); return NULL; }

    Passageiros *p = init_passageiro(campos[0], campos[1], campos[2], campos[3],
                                     campos[4], campos[5], campos[6], campos[7],
                                     campos[8], campos[9]);

    free(temp);
    return p;
}
