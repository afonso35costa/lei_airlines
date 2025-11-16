#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser_utils.h"

char* strip_quotes(const char *str) {
    if (!str) return NULL;
    size_t len = strlen(str);

    if (len >= 2 && str[0] == '\"' && str[len - 1] == '\"') {
        // Proteção contra len < 2
        char *result = malloc(len - 1);
        if (!result) return NULL;
        if (len > 2)
            strncpy(result, str + 1, len - 2);
        result[len - 2] = '\0';
        return result;
    } else {
        return strdup(str);
    }
}

// Ignora virgulas dentro de aspas
char* ignorar_virgulas(char **str) {
    char *src = *str;
    if (!src) return NULL;

    char *out = malloc(strlen(src) + 1);
    char *o = out;
    int in_quotes = 0;

    while (*src) {
        if (*src == '"') {
            in_quotes = !in_quotes; // alterna dentro/fora de aspas
        }
        else if (*src == ',' && !in_quotes) {
            src++;  // consumir vírgula separadora real
            break;
        }
        *o++ = *src++;
    }

    *o = '\0';
    *str = src;

    return strip_quotes(out); // já removemos aspas como antes
}
