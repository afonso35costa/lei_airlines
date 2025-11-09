#ifndef GESTOR_AERONAVES_H
#define GESTOR_AERONAVES_H

#include "aeronaves.h"

#define TABLE_SIZE_N 20000

typedef struct nodo_aeronave {
    char *key;
    Aeronaves *valor;
    struct nodo_aeronave *next;
} NodoAeronave;

typedef struct gestor_aeronaves {
    NodoAeronave **tabela;
} GestorAeronaves;

GestorAeronaves *criar_gestor_aeronaves();
int inserir_aeronave(GestorAeronaves *g, Aeronaves *a);
Aeronaves *procurar_aeronave(GestorAeronaves *g, const char *id);
int remover_aeronave(GestorAeronaves *g, const char *id);
void libertar_gestor_aeronaves(GestorAeronaves *g);
void print_todos_aeronaves(GestorAeronaves *g);

#endif
