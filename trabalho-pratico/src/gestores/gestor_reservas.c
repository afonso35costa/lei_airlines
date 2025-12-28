#include "gestor_reservas.h"
#include <glib.h>
#include <stdlib.h>

/*
struct gestor_reservas {
    GPtrArray *array;  // array de Reservas*
};

// Cria gestor
GestorReservas* gestor_reservas_create(void) {
    GestorReservas *gr = malloc(sizeof(GestorReservas));
    if (!gr) return NULL;
    gr->array = g_ptr_array_new_with_free_func((GDestroyNotify)destroy_reserva);
    return gr;
}

// Adiciona reserva
void gestor_reservas_add(GestorReservas *gr, Reservas *r) {
    g_ptr_array_add(gr->array, r);
}

// Remove reserva por reservation_id
void gestor_reservas_remove(GestorReservas *gr, const char *reservation_id) {
    for (guint i = 0; i < gr->array->len; i++) {
        Reservas *r = g_ptr_array_index(gr->array, i);
        if (g_strcmp0(get_reservation_id_reservas(r), reservation_id) == 0) {
            g_ptr_array_remove_index(gr->array, i);
            return;
        }
    }
}

// Retorna reserva pelo índice
Reservas* gestor_reservas_get(GestorReservas *gr, int index) {
    if (index < 0 || index >= (int)gr->array->len) return NULL;
    return g_ptr_array_index(gr->array, index);
}

// Retorna o array de reservas  
GPtrArray* gestor_reservas_get_array(GestorReservas *gr) {
    return gr ? gr->array : NULL;
}

//Length do array de reservas
guint gestor_reservas_get_length(GestorReservas *gr) {
    return gr ? gr->array->len : 0;
}

// Liberta gestor e todas as reservas
void gestor_reservas_free(GestorReservas *gr) {
    g_ptr_array_free(gr->array, TRUE);
    free(gr);
}


*/

// Implementação do gestor de reservas baseado em hash table

struct gestor_resHash {
    GHashTable *hash;  // hash table de flight_id -> Voo*
};

// Cria gestor
HashReservas* hash_reservas_create(void) {
    HashReservas *gr = malloc(sizeof(HashReservas));
    if (!gr) return NULL;
    gr->hash = g_hash_table_new_full(g_str_hash, g_str_equal, free, NULL);
    return gr;
}

//Devolve hash table interna (para uso em queries)
GHashTable* hash_reservas_get_hash(HashReservas *gr) {
    return gr->hash;
}

// Adiciona reserva
void hash_reservas_add(HashReservas *gr, Reservas *reserva) {
    g_hash_table_insert(gr->hash, strdup(get_document_number_reservas(reserva)), reserva);
}

// Remove reserva
void hash_reservas_remove(HashReservas *gr, const char *id) {
    g_hash_table_remove(gr->hash, id);
}

// Retorna reserva
Reservas* hash_reservas_get(HashReservas *gr, const char *id) {
    return g_hash_table_lookup(gr->hash, id);
}

// Liberta gestor e todas as reservas
void hash_reservas_free(HashReservas *gr) {
    g_hash_table_destroy(gr->hash);
    free(gr);
}

// Funcao que devolve o numero de reservas no gestor
guint hash_reservas_get_length(HashReservas *gr) {
    return g_hash_table_size(gr->hash);
}