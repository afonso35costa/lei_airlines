#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reservas.h"
#include "validacao_reservas.h"  // contém validar_reserva()
#include "parser_utils.h"

#define RESERVAS_ERRO_FILE "resultados/reservas_errors.csv"

// Converte string "true"/"false" para bool
static bool str_to_bool(const char *str) {
    if (!str) return false;
    return (strcmp(str, "true") == 0) ? true : false;
}

// Função auxiliar para parsing do campo flight_ids ["id1","id2",...]
static char **parse_flight_ids(char *str) {
    if (!str) return NULL;

    char *s = strdup(str);
    if (!s) return NULL;

    // Remove colchetes
    size_t len = strlen(s);
    if (len >= 2 && s[0] == '[' && s[len-1] == ']') { s[len-1] = '\0'; s++; }

    char **arr = malloc(11 * sizeof(char*)); // máximo 10 ids + NULL
    if (!arr) { free(s); return NULL; }

    char *token, *rest = s;
    int i = 0;
    while ((token = strsep(&rest, ",")) != NULL && i < 10) {
        arr[i++] = strdup(strip_quotes(token));
    }
    arr[i] = NULL;
    return arr;
}

Reservas *parse_reserva_line(const char *line) {
    if (!line) return NULL;
    char *temp = strdup(line);
    if (!temp) return NULL;

    char *token, *rest = temp;
    char *campos[8]; int i = 0;

    while ((token = strsep(&rest, ",")) != NULL && i < 8)
        campos[i++] = strip_quotes(token);

    if (i < 8) { free(temp); return NULL; }

    char **flight_ids = parse_flight_ids(campos[1]);
    double price = atof(campos[4]);
    bool extra = str_to_bool(campos[5]);
    bool priority = str_to_bool(campos[6]);

    Reservas *r = init_reserva(campos[0], flight_ids, campos[2], campos[3],
                               price, extra, priority, campos[7]);

    if (flight_ids) { for (int j=0; flight_ids[j]; j++) free(flight_ids[j]); free(flight_ids); }
    free(temp);
    return r;
}

Reservas *parse_and_validate_reserva_line(const char *line, FILE *ferr) {
    if (!line || strlen(line) == 0)
        return NULL;

    Reservas *r = parse_reserva_line(line);

    if (!validar_reserva(r)) {
        if (ferr) {
            fprintf(ferr, "%s\n", line);
        }
        destroy_reserva(r);
        return NULL;
    }

    return r; // válido ✅
}
