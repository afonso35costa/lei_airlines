#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gestor_voos.h"

static unsigned long hashV(const char *str) {
    unsigned long h = 5381;
    int c;
    while ((c = *str++))
        h = ((h << 5) + h) + c;
    return h % TABLE_SIZE_V;
}

GestorVoos *criar_gestor_voos() {
    GestorVoos *g = malloc(sizeof(GestorVoos));
    g->tabela = calloc(TABLE_SIZE_V, sizeof(NodoVoo *));
    return g;
}

int inserir_voo(GestorVoos *g, Voo *v) {
    if (!g || !v) return 0;

    const char *key = get_flight_id(v);
    unsigned long idx = hashV(key);

    NodoVoo *novo = malloc(sizeof(NodoVoo));
    novo->key = strdup(key);
    novo->valor = v;
    novo->next = g->tabela[idx];
    g->tabela[idx] = novo;

    return 1;
}

Voo *procurar_voo(GestorVoos *g, const char *flight_id) {
    unsigned long idx = hashV(flight_id);
    NodoVoo *n = g->tabela[idx];

    while (n) {
        if (strcmp(n->key, flight_id) == 0)
            return n->valor;
        n = n->next;
    }
    return NULL;
}

int remover_voo(GestorVoos *g, const char *flight_id) {
    unsigned long idx = hashV(flight_id);
    NodoVoo *n = g->tabela[idx], *prev = NULL;

    while (n) {
        if (strcmp(n->key, flight_id) == 0) {
            if (prev) prev->next = n->next;
            else g->tabela[idx] = n->next;

            free(n->key);
            libertar_voo(n->valor);
            free(n);
            return 1;
        }
        prev = n;
        n = n->next;
    }
    return 0;
}

void libertar_gestor_voos(GestorVoos *g) {
    for (int i = 0; i < TABLE_SIZE_V; i++) {
        NodoVoo *n = g->tabela[i];
        while (n) {
            NodoVoo *tmp = n->next;
            free(n->key);
            libertar_voo(n->valor);
            free(n);
            n = tmp;
        }
    }
    free(g->tabela);
    free(g);
}

void print_todos_voos(GestorVoos *g) {
    for (int i = 0; i < TABLE_SIZE_V; i++) {
        NodoVoo *n = g->tabela[i];
        while (n) {
            print_voo(n->valor);
            n = n->next;
        }
    }
}
