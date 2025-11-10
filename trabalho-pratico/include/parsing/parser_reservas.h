#ifndef PARSER_AERONAVES_H
#define PARSER_AERONAVES_H

#include <stdbool.h>
#include "reservas.h"

static char **parse_flight_ids(char *str);
Reservas *parse_reserva_line(const char *line);

#endif