#ifndef GESTOR_VOOS_H
#define GESTOR_VOOS_H

#include "voos.h"

#define TABLE_SIZE_V 20000

typedef struct nodo_voo {
    char *key;               // flight_id
    Voo *valor;
    struct nodo_voo *next;
} NodoVoo;

typedef struct gestor_voos {
    NodoVoo **tabela;
} GestorVoos;

/* CRUD */
GestorVoos *criar_gestor_voos();
int inserir_voo(GestorVoos *g, Voo *v);
Voo *procurar_voo(GestorVoos *g, const char *flight_id);
int remover_voo(GestorVoos *g, const char *flight_id);
void libertar_gestor_voos(GestorVoos *g);

/* Debug */
void print_todos_voos(GestorVoos *g);

#endif
