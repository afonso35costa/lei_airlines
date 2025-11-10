#ifndef PARSER_AERONAVES_H
#define PARSER_AERONAVES_H

#include <stdbool.h>
#include "voos.h"

Voo *parse_voo_line(const char *line);

#endif