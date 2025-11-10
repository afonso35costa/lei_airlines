/*
#ifndef GESTOR_PASSAGEIROS_H
#define GESTOR_PASSAGEIROS_H

#include "passageiros.h"

#define TABLE_SIZE 20000

typedef struct nodo_p {
    char *key;               // document_number
    Passageiros *valor;      // struct Passageiros
    struct nodo_p *next;     // próximo no caso de colisão
} NodoPassageiros;

typedef struct gestor_passageiros {
    NodoPassageiros **tabela; // array de listas
} GestorPassageiros;

GestorPassageiros *criar_gestor_passageiros();
void libertar_gestor_passageiros(GestorPassageiros *g);


int inserir_passageiro(GestorPassageiros *g, Passageiros *p);
Passageiros *procurar_passageiro(GestorPassageiros *g, const char *doc);
int remover_passageiro(GestorPassageiros *g, const char *doc);


void print_todos_passageiros(GestorPassageiros *g);

#endif
*/