#ifndef GESTOR_RESERVAS_H
#define GESTOR_RESERVAS_H

#include <glib.h>
#include "reservas.h"

typedef struct gestor_reservas GestorReservas;

// Cria um gestor de reservas vazio
GestorReservas* gestor_reservas_create(void);

// Adiciona uma reserva ao gestor
void gestor_reservas_add(GestorReservas *gr, Reservas *r);

// Remove reserva pelo identificador
void gestor_reservas_remove(GestorReservas *gr, const char *reservation_id);

// Retorna ponteiro para reserva pelo índice
Reservas* gestor_reservas_get(GestorReservas *gr, int index);

// Retorna o array de reservas
GPtrArray* gestor_reservas_get_array(GestorReservas *gr);

// Retorna o número de reservas no gestor
guint gestor_reservas_get_length(GestorReservas *gr);

// Liberta toda a memória associada ao gestor e às reservas
void gestor_reservas_free(GestorReservas *gr);

#endif