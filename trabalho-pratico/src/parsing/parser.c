#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aeronaves.h"

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

/* Parser de aeronaves */
void parse_aeronaves_csv(const char *filename) {
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

