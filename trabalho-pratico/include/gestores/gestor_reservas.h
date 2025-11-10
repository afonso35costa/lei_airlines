/* 
#ifndef GESTOR_RESERVAS_H
#define GESTOR_RESERVAS_H

#include "reservas.h"

#define TABLE_SIZE_R 20000

typedef struct nodo_reserva {
    char *key;               // reservation_id
    Reservas *valor;
    struct nodo_reserva *next;
} NodoReserva;

typedef struct gestor_reservas {
    NodoReserva **tabela;
} GestorReservas;


GestorReservas *criar_gestor_reservas();
int inserir_reserva(GestorReservas *g, Reservas *r);
Reservas *procurar_reserva(GestorReservas *g, const char *reservation_id);
int remover_reserva(GestorReservas *g, const char *reservation_id);
void libertar_gestor_reservas(GestorReservas *g);


void print_todas_reservas(GestorReservas *g);

#endif
*/