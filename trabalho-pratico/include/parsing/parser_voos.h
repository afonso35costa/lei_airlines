#ifndef PARSER_VOOS_H
#define PARSER_VOOS_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "voos.h"

Voo *parse_voo_line(const char *line);
Voo *parse_and_validate_voo_line(const char *line, FILE *ferr);

#endif