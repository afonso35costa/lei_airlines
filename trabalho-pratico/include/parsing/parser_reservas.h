#ifndef PARSER_RESERVAS_H
#define PARSER_RESERVAS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "reservas.h"

bool str_to_bool(const char *str);
char **parse_flight_ids(char *str);
Reservas *parse_reserva_line(const char *line);
Reservas *parse_and_validate_reserva_line(const char *line, FILE *ferr);

#endif