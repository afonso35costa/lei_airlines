#ifndef GESTOR_AEROPORTOS_H
#define GESTOR_AEROPORTOS_H

#include "aeroportos.h"

#define TABLE_SIZE_A 20000

typedef struct nodo_aeroporto {
    char *key;                   // código IATA
    Aeroportos *valor;
    struct nodo_aeroporto *next;
} NodoAeroporto;

typedef struct gestor_aeroportos {
    NodoAeroporto **tabela;
} GestorAeroportos;

/* CRUD */
GestorAeroportos *criar_gestor_aeroportos();
int inserir_aeroporto(GestorAeroportos *g, Aeroportos *a);
Aeroportos *procurar_aeroporto(GestorAeroportos *g, const char *code);
int remover_aeroporto(GestorAeroportos *g, const char *code);
void libertar_gestor_aeroportos(GestorAeroportos *g);

/* Debug */
void print_todos_aeroportos(GestorAeroportos *g);

#endif