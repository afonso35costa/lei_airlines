#ifndef PARSER_AEROPORTOS_H
#define PARSER_AEROPORTOS_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aeroportos.h"

Aeroportos *parse_aeroporto_line(const char *line);
Aeroportos *parse_and_validate_aeroporto_line(const char *line, FILE *ferr);

#endif