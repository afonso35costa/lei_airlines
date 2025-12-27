#ifndef PARSER_UTILS_H
#define PARSER_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Typedefs para parser geral
typedef void *(*FuncaoParser)(const char *line, FILE *err_file);
typedef void (*FuncaoAddGestor)(void *objeto, void *gestor1, void *gestor2, void *gestor3);

// Funcao strip_quotes - remove aspas de string
char* strip_quotes(const char *str);
// Funcao ignorar_virgulas - ignora virgulas dentro de aspas
char* ignorar_virgulas(char **str);

#endif