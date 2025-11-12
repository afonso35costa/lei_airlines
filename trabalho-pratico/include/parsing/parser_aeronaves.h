#ifndef PARSER_AERONAVES_H
#define PARSER_AERONAVES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aeronaves.h"

Aeronaves *parse_aeronave_line(const char *line);
Aeronaves *parse_and_validate_aeronave_line(const char *line, FILE *ferr);

#endif