#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reservas.h"
#include "validacao_reservas.h"  // contém validar_reserva()
#include "parser_utils.h"
#include "parser_reservas.h"

#define RESERVAS_ERRO_FILE "resultados/reservas_errors.csv"

// Converte string "true"/"false" para bool

bool str_to_bool(const char *str) {
    if (!str) return false;
    return (strcmp(str, "true") == 0) ? true : false;
}

// Função auxiliar para parsing do campo flight_ids ["id1","id2",...]

char **parse_flight_ids(char *str) {  // str = "['TI12433', 'TI12434']"

    if (!str) return NULL;  

    char *s_orig = strdup(str);
    if (!s_orig) return NULL;

    size_t len = strlen(s_orig);
    char *start = s_orig;  // ponteiro que percorre o buffer

    // Remove colchetes, sem mexer no ponteiro original
    if (len >= 2 && s_orig[0] == '[' && s_orig[len-1] == ']') {
        s_orig[len-1] = '\0';
        start++; // apenas start aponta para o início real do conteúdo
    }

    // Primeiro, conta o número de tokens
    int num_tokens = 1; // pelo menos 1 token
    for (char *p = s_orig; *p; p++) {
        if (*p == ',') num_tokens++;
    }

    char **arr = malloc((num_tokens + 1) * sizeof(char*));
    if (!arr) { free(s_orig); return NULL; }

    char *rest = start;
    int i = 0;
    char *token;
    
    while ((token = strsep(&rest, ",")) != NULL) {
        arr[i++] = strip_quotes(token); // malloc seguro
    }
    arr[i] = NULL; // terminador NULL

    free(s_orig);  // free seguro do buffer original
    return arr;
}

Reservas *parse_reserva_line(const char *line) {
    if (!line) return NULL;
    char *temp = strdup(line);
    if (!temp) return NULL;

    char *rest = temp;
    char *campos[7] = {0};
    int i = 0;

    while (rest && i < 7) {
        campos[i] = ignorar_virgulas(&rest);
        i++;
    }
    char **flight_ids = parse_flight_ids(campos[1]);
    double price = atof(campos[4]);
    bool extra = str_to_bool(campos[5]);
    bool priority = str_to_bool(campos[6]);

    Reservas *r = init_reserva(campos[0], flight_ids, campos[2], campos[3],
                               price, extra, priority);


    // Liberta array temporário de flight_ids
    if (flight_ids != NULL) {
        for (int j = 0; flight_ids[j] != NULL; j++) {
            free(flight_ids[j]);
        }
        free(flight_ids);
    }
                                   
    for (int j = 0; j < 7; j++) free(campos[j]);
    free(temp);
    return r;
}

Reservas *parse_and_validate_reserva_line(const char *line, FILE *ferr) {
    if (!line || strlen(line) == 0)
        return NULL;

    Reservas *r = parse_reserva_line(line);
    /*
    if (!validar_reserva(r)) {
        if (ferr) {
            fprintf(ferr, "%s\n", line);
        }
        destroy_reserva(r);
        return NULL;
    }
        */

    return r; // válido ✅
}
