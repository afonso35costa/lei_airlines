#ifndef PARSER_PASSAGEIROS_H
#define PARSER_PASSAGEIROS_H


#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "passageiros.h"

Passageiros *parse_passageiro_line(const char *line);
Passageiros *parse_and_validate_passageiro_line(const char *line, FILE *ferr);

#endif