#include <stdlib.h>
#include <string.h>
#include "gestor_aeronaves.h"

static unsigned long hashN(const char *str) {
    unsigned long h = 5381, c;
    while((c = *str++)) h = ((h<<5)+h)+c;
    return h % TABLE_SIZE_N;
}

GestorAeronaves *criar_gestor_aeronaves(){
    GestorAeronaves *g = malloc(sizeof(GestorAeronaves));
    g->tabela = calloc(TABLE_SIZE_N,sizeof(NodoAeronave*));
    return g;
}

int inserir_aeronave(GestorAeronaves *g, Aeronaves *a){
    const char *key = get_identifier(a);
    unsigned long idx = hashN(key);
    NodoAeronave *n = malloc(sizeof(NodoAeronave));
    n->key = strdup(key);
    n->valor = a;
    n->next = g->tabela[idx];
    g->tabela[idx] = n;
    return 1;
}

Aeronaves *procurar_aeronave(GestorAeronaves *g, const char *id){
    unsigned long idx = hashN(id);
    NodoAeronave *n=g->tabela[idx];
    while(n){
        if(strcmp(n->key,id)==0) return n->valor;
        n=n->next;
    }
    return NULL;
}

int remover_aeronave(GestorAeronaves *g,const char *id){
    unsigned long idx = hashN(id);
    NodoAeronave *n=g->tabela[idx], *prev=NULL;
    while(n){
        if(strcmp(n->key,id)==0){
            if(prev) prev->next=n->next;
            else g->tabela[idx]=n->next;
            free(n->key);
            libertar_aeronave(n->valor);
            free(n);
            return 1;
        }
        prev=n;
        n=n->next;
    }
    return 0;
}

void libertar_gestor_aeronaves(GestorAeronaves *g){
    for(int i=0;i<TABLE_SIZE_N;i++){
        NodoAeronave *n=g->tabela[i];
        while(n){
            NodoAeronave *t=n->next;
            free(n->key);
            libertar_aeronave(n->valor);
            free(n);
            n=t;
        }
    }
    free(g->tabela);
    free(g);
}

void print_todos_aeronaves(GestorAeronaves *g){
    for(int i=0;i<TABLE_SIZE_N;i++){
        NodoAeronave *n=g->tabela[i];
        while(n){
            print_aeronave(n->valor);
            n=n->next;
        }
    }
}
