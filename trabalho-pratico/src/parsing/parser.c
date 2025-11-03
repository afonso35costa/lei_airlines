#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aeronaves.h"
#include "aeronaves.c"
#include "passageiros.h"
#include "passageiros.c"

/* Remove aspas no início e no fim de uma string, e converte "" em " */
static char* strip_quotes(char *s) {
    if (!s) return NULL;
    size_t len = strlen(s);
    if (len >= 2 && s[0] == '"' && s[len-1] == '"') {
        s[len-1] = '\0';
        s++;
        len -= 2;
    }
    /* substituir "" por " */
    char *p = s;
    char *dst = s;
    while (*p) {
        if (*p == '"' && *(p+1) == '"') {
            *dst++ = '"';
            p += 2;
        } else {
            *dst++ = *p++;
        }
    }
    *dst = '\0';
    return s;
}

/* Converte "['KS10150','KS10151']" -> char** {"KS10150","KS10151",NULL} */
static char** parse_flight_ids(char *raw) {
    if (!raw) return NULL;
    raw = strip_quotes(raw);

    // remover colchetes
    if (*raw == '[') raw++;
    size_t len = strlen(raw);
    if (len > 0 && raw[len - 1] == ']') raw[len - 1] = '\0';

    // contar quantos IDs há
    int count = 0;
    char *tmp = strdup(raw);
    char *p = tmp;
    while ((strsep(&p, ",")) != NULL) count++;
    free(tmp);

    char **ids = malloc((count + 1) * sizeof(char*));
    p = raw;
    char *token;
    int i = 0;
    while ((token = strsep(&p, ",")) != NULL) {
        // remover aspas simples e espaços
        while (*token == '\'' || *token == ' ') token++;
        size_t tlen = strlen(token);
        while (tlen > 0 && (token[tlen - 1] == '\'' || token[tlen - 1] == ' ')) {
            token[--tlen] = '\0';
        }
        ids[i++] = strdup(token);
    }
    ids[i] = NULL;
    return ids;
}

/* Converte "true"/"false" -> bool */
static bool str_to_bool(const char *s) {
    return (s && (strcmp(s, "true") == 0 || strcmp(s, "TRUE") == 0));
}

// PARSER 
/* Parser de aeronaves */
void parse_aeronaves_csv(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        perror(filename);
        return;
    }

    char *line = NULL;
    size_t len = 0;
    size_t read;
    int first_line = 1;

    while ((read = getline(&line, &len, f)) != -1) {
        if (first_line) { first_line = 0; continue; } // ignorar cabeçalho

        char *ptr = line;
        char *fields[6] = {0};
        int i = 0;

        while (ptr && i < 6) {
            fields[i++] = strip_quotes(strsep(&ptr, ","));
        }

        if (i < 6) {
            fprintf(stderr, "Linha incompleta: %s\n", line);
            continue;
        }

        char *identifier = strdup(fields[0]);
        char *manufacturer = strdup(fields[1]);
        char *model = strdup(fields[2]);
        int year = atoi(fields[3]);
        int capacity = atoi(fields[4]);
        int range = atoi(fields[5]);

        Aeronaves *a = criar_aeronave(identifier, manufacturer, model, year, capacity, range);

        /* Aqui podes adicionar a aeronave a um array ou lista existente */
        /* Exemplo: add_aeronave_to_catalog(a); */

    }

    free(line);
    fclose(f);
}

/* Parser do ficheiro passageiros.csv */
void parse_passageiros_csv(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        perror(filename);
        return;
    }

    char *line = NULL;
    size_t len = 0;
    size_t read;
    int first_line = 1;

    while ((read = getline(&line, &len, f)) != -1) {
        if (first_line) { first_line = 0; continue; } // ignora cabeçalho
        if (read <= 1) continue; // ignora linhas vazias

        char *ptr = line;
        char *fields[10] = {NULL};
        int i = 0;

        while (ptr && i < 10) {
            fields[i++] = strip_quotes(strsep(&ptr, ","));
        }

        if (i < 10) {
            fprintf(stderr, "Linha inválida: %s\n", line);
            continue;
        }

        Passageiros *p = init_passageiro(
            fields[0], fields[1], fields[2], fields[3], fields[4],
            fields[5], fields[6], fields[7], fields[8], fields[9]
        );

        if (!p) {
            fprintf(stderr, "Erro a criar passageiro: %s\n", fields[0]);
            continue;
        }

        /* TODO: adicionar à estrutura principal (ex: add_passageiro(p)); */
    }

    free(line);
    fclose(f);
}


/* Parser do ficheiro reservas.csv */
void parse_reservas_csv(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        perror(filename);
        return;
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int first_line = 1;

    while ((read = getline(&line, &len, f)) != -1) {
        if (first_line) { first_line = 0; continue; }
        if (read <= 1) continue;

        char *ptr = line;
        char *fields[8] = {NULL};
        int i = 0;

        while (ptr && i < 8)
            fields[i++] = strip_quotes(strsep(&ptr, ","));

        if (i < 8) {
            fprintf(stderr, "Linha inválida: %s\n", line);
            continue;
        }

        char **flight_ids = parse_flight_ids(fields[1]);
        double price = atof(fields[4]);
        bool extra_luggage = str_to_bool(fields[5]);
        bool priority_boarding = str_to_bool(fields[6]);

        Reservas *r = init_reserva(
            fields[0], flight_ids, fields[2], fields[3],
            price, extra_luggage, priority_boarding, fields[7]
        );

        if (!r) {
            fprintf(stderr, "Erro a criar reserva: %s\n", fields[0]);
            continue;
        }

        /* TODO: adicionar à tua estrutura de dados principal */
        /* Exemplo: add_reserva(r); */

        // libertar o array de flight_ids temporário
        if (flight_ids) {
            for (int j = 0; flight_ids[j]; j++) free(flight_ids[j]);
            free(flight_ids);
        }
    }

    free(line);
    fclose(f);
}



