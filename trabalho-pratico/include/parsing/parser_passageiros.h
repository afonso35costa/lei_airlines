#ifndef PARSER_AERONAVES_H
#define PARSER_AERONAVES_H

#include <stdbool.h>
#include "passageiros.h"

Passageiros *parse_passageiro_line(const char *line);

#endif