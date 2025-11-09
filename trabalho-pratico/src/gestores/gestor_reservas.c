#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gestor_reservas.h"

static unsigned long hashR(const char *str) {
    unsigned long h = 5381;
    int c;
    while((c = *str++))
        h = ((h << 5) + h) + c;
    return h % TABLE_SIZE_R;
}

GestorReservas *criar_gestor_reservas() {
    GestorReservas *g = malloc(sizeof(GestorReservas));
    g->tabela = calloc(TABLE_SIZE_R, sizeof(NodoReserva *));
    return g;
}

int inserir_reserva(GestorReservas *g, Reservas *r) {
    if (!g || !r) return 0;

    const char *key = get_reservation_id(r);
    unsigned long idx = hashR(key);

    NodoReserva *novo = malloc(sizeof(NodoReserva));
    novo->key = strdup(key);
    novo->valor = r;
    novo->next = g->tabela[idx];
    g->tabela[idx] = novo;

    return 1;
}

Reservas *procurar_reserva(GestorReservas *g, const char *reservation_id) {
    unsigned long idx = hashR(reservation_id);
    NodoReserva *n = g->tabela[idx];

    while (n) {
        if (strcmp(n->key, reservation_id) == 0)
            return n->valor;
        n = n->next;
    }
    return NULL;
}

int remover_reserva(GestorReservas *g, const char *reservation_id) {
    unsigned long idx = hashR(reservation_id);
    NodoReserva *n = g->tabela[idx], *prev = NULL;

    while (n) {
        if (strcmp(n->key, reservation_id) == 0) {
            if (prev) prev->next = n->next;
            else g->tabela[idx] = n->next;

            free(n->key);
            libertar_reserva(n->valor);
            free(n);
            return 1;
        }
        prev = n;
        n = n->next;
    }
    return 0;
}

void libertar_gestor_reservas(GestorReservas *g) {
    for (int i = 0; i < TABLE_SIZE_R; i++) {
        NodoReserva *n = g->tabela[i];
        while (n) {
            NodoReserva *tmp = n->next;
            free(n->key);
            libertar_reserva(n->valor);
            free(n);
            n = tmp;
        }
    }
    free(g->tabela);
    free(g);
}

void print_todas_reservas(GestorReservas *g) {
    for (int i = 0; i < TABLE_SIZE_R; i++) {
        NodoReserva *n = g->tabela[i];
        while (n) {
            print_reserva(n->valor);
            n = n->next;
        }
    }
}
