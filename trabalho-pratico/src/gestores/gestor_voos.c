#include "gestor_voos.h"
#include <glib.h>
#include <stdlib.h>
#include <stdio.h>

// Implementação do gestor de voos baseado em array

struct gestor_voosArray {
    GPtrArray *array;  // array de Voo*
};

// Cria gestor
ArrayVoos* array_voos_create(void) {
    ArrayVoos *gv = malloc(sizeof(ArrayVoos));
    if (!gv) return NULL;
    gv->array = g_ptr_array_new_with_free_func((GDestroyNotify)destroy_voo);
    return gv;
}

// Adiciona voo
void array_voos_add(ArrayVoos *gv, Voo *v) {
    g_ptr_array_add(gv->array, v);
}

// Remove voo por flight_id
void array_voos_remove(ArrayVoos *gv, const char *flight_id) {
    for (guint i = 0; i < gv->array->len; i++) {
        Voo *v = g_ptr_array_index(gv->array, i);
        if (g_strcmp0(get_flight_id_voo(v), flight_id) == 0) {
            g_ptr_array_remove_index(gv->array, i);
            return;
        }
    }
}

// Retorna voo pelo índice
Voo* array_voos_get(ArrayVoos *gv, int index) {
    if (index < 0 || index >= (int)gv->array->len) return NULL;
    return g_ptr_array_index(gv->array, index);
}

// Retorna o array de voos
GPtrArray* array_voos_get_array(ArrayVoos *gv) {
    return gv ? gv->array : NULL;
}

//Length do array de voos
guint array_voos_get_length(ArrayVoos *gv) {
    return gv->array->len;
}

// Liberta gestor e todos os voos
void array_voos_free(ArrayVoos *gv) {
    g_ptr_array_free(gv->array, TRUE);
    free(gv);
}

// Implementação do gestor de voos baseado em hash table

struct gestor_voosHash {
    GHashTable *hash;  // hash table de flight_id -> Voo*
};

// Cria gestor
HashVoos* hash_voos_create(void) {
    HashVoos *ga = malloc(sizeof(HashVoos));
    if (!ga) return NULL;
    ga->hash = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, NULL);
    return ga;
}

//Devolve hash table interna (para uso em queries)
GHashTable* hash_voos_get_hash(HashVoos *ga) {
    return ga->hash;
}

// Adiciona voo
void hash_voos_add(HashVoos *ga, Voo *voo) {
    g_hash_table_insert(ga->hash, g_strdup(get_flight_id_voo(voo)), voo);
}

// Remove voo
void hash_voos_remove(HashVoos *ga, const char *code) {
    g_hash_table_remove(ga->hash, code);
}

// Retorna voo
Voo* hash_voos_get(HashVoos *ga, const char *code) {
    return g_hash_table_lookup(ga->hash, code);
}

// Liberta gestor e todos os voos
void hash_voos_free(HashVoos *ga) {
    g_hash_table_destroy(ga->hash);
    free(ga);
}

// Funcao que devolve o numero de voos no gestor
guint hash_voos_get_length(HashVoos *ga) {
    return g_hash_table_size(ga->hash);
}


