#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gestor_aeroportos.h"

static unsigned long hashA(const char *str) {
    unsigned long h = 5381;
    int c;
    while((c = *str++)) h = ((h << 5) + h) + c;
    return h % TABLE_SIZE_A;
}

GestorAeroportos *criar_gestor_aeroportos() {
    GestorAeroportos *g = malloc(sizeof(GestorAeroportos));
    g->tabela = calloc(TABLE_SIZE_A, sizeof(NodoAeroporto*));
    return g;
}

int inserir_aeroporto(GestorAeroportos *g, Aeroportos *a) {
    if(!g || !a) return 0;
    const char *key = get_code(a);
    unsigned long idx = hashA(key);

    NodoAeroporto *n = malloc(sizeof(NodoAeroporto));
    n->key = strdup(key);
    n->valor = a;
    n->next = g->tabela[idx];
    g->tabela[idx] = n;
    return 1;
}

Aeroportos *procurar_aeroporto(GestorAeroportos *g, const char *code) {
    unsigned long idx = hashA(code);
    NodoAeroporto *n = g->tabela[idx];
    while(n) {
        if(strcmp(n->key, code) == 0) return n->valor;
        n = n->next;
    }
    return NULL;
}

int remover_aeroporto(GestorAeroportos *g, const char *code) {
    unsigned long idx = hashA(code);
    NodoAeroporto *n = g->tabela[idx], *prev = NULL;
    while(n) {
        if(strcmp(n->key, code) == 0) {
            if(prev) prev->next = n->next;
            else g->tabela[idx] = n->next;

            free(n->key);
            libertar_aeroporto(n->valor);
            free(n);
            return 1;
        }
        prev = n;
        n = n->next;
    }
    return 0;
}

void libertar_gestor_aeroportos(GestorAeroportos *g) {
    for(int i=0;i<TABLE_SIZE_A;i++) {
        NodoAeroporto *n=g->tabela[i];
        while(n){
            NodoAeroporto *tmp=n->next;
            free(n->key);
            libertar_aeroporto(n->valor);
            free(n);
            n=tmp;
        }
    }
    free(g->tabela);
    free(g);
}

void print_todos_aeroportos(GestorAeroportos *g) {
    for(int i=0;i<TABLE_SIZE_A;i++) {
        NodoAeroporto *n = g->tabela[i];
        while(n) {
            print_aeroporto(n->valor);
            n = n->next;
        }
    }
}
