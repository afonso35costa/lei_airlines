#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Funcao strip_quotes - remove aspas de string
char* strip_quotes(const char *str) {
    if (!str) return NULL;  
    size_t len = strlen(str);
    if (len < 2 || str[0] != '\"' || str[len - 1] != '\"') return NULL;

    char *result = malloc(len - 1);
    if (!result) return NULL;
    strncpy(result, str + 1, len - 2);
    result[len - 2] = '\0';
    return result;
}