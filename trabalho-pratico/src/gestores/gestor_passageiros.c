#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gestor_passageiros.h"

/* Função de hash djb2 */
static unsigned long hash(const char *str) {
    unsigned long h = 5381;
    int c;
    while ((c = *str++))
        h = ((h << 5) + h) + c; // h * 33 + c
    return h % TABLE_SIZE;
}

/* Criar gestor */
GestorPassageiros *criar_gestor_passageiros() {
    GestorPassageiros *g = malloc(sizeof(GestorPassageiros));
    if (!g) return NULL;

    g->tabela = calloc(TABLE_SIZE, sizeof(NodoPassageiros*));
    return g;
}

/* Inserir passageiro */
int inserir_passageiro(GestorPassageiros *g, Passageiros *p) {
    if (!g || !p) return 0;
    
    const char *key = get_document_number(p);
    unsigned long idx = hash(key);

    NodoPassageiros *novo = malloc(sizeof(NodoPassageiros));
    novo->key = strdup(key);
    novo->valor = p;
    novo->next = g->tabela[idx];
    g->tabela[idx] = novo;
    return 1;
}

/* Procurar por chave */
Passageiros *procurar_passageiro(GestorPassageiros *g, const char *doc) {
    if (!g || !doc) return NULL;
    unsigned long idx = hash(doc);

    NodoPassageiros *n = g->tabela[idx];
    while (n) {
        if (strcmp(n->key, doc) == 0)
            return n->valor;
        n = n->next;
    }
    return NULL;
}

/* Remover passageiro */
int remover_passageiro(GestorPassageiros *g, const char *doc) {
    if (!g || !doc) return 0;
    unsigned long idx = hash(doc);

    NodoPassageiros *n = g->tabela[idx];
    NodoPassageiros *prev = NULL;

    while (n) {
        if (strcmp(n->key, doc) == 0) {
            if (prev) prev->next = n->next;
            else g->tabela[idx] = n->next;

            free(n->key);
            destroy_passageiro(n->valor);
            free(n);
            return 1;
        }
        prev = n;
        n = n->next;
    }
    return 0;
}

/* Libertar tudo */
void libertar_gestor_passageiros(GestorPassageiros *g) {
    if (!g) return;

    for (int i = 0; i < TABLE_SIZE; i++) {
        NodoPassageiros *n = g->tabela[i];
        while (n) {
            NodoPassageiros *tmp = n->next;
            free(n->key);
            destroy_passageiro(n->valor);
            free(n);
            n = tmp;
        }
    }

    free(g->tabela);
    free(g);
}

/* Imprimir todos (debug) */
void print_todos_passageiros(GestorPassageiros *g) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        NodoPassageiros *n = g->tabela[i];
        while (n) {
            print_passageiro(n->valor);
            n = n->next;
        }
    }
}
