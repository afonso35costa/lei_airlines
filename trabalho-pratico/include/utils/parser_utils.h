#ifndef PARSER_UTILS_H
#define PARSER_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Funcao strip_quotes - remove aspas de string
char* strip_quotes(const char *str);
// Funcao ignorar_virgulas - ignora virgulas dentro de aspas
char* ignorar_virgulas(char **str);

#endif