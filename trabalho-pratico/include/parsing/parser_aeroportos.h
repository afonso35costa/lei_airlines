#ifndef PARSER_AERONAVES_H
#define PARSER_AERONAVES_H

#include <stdbool.h>
#include "aeroportos.h"

Aeroportos *parse_aeroporto_line(const char *line);

#endif