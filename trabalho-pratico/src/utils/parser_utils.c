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

