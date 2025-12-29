#include "gestor_aeroportos.h"
#include "aeroportos.h"
#include <glib.h>
#include <stdlib.h>

struct gestor_aeroportos {
    GHashTable *hash;  // chave = code (char*), valor = Aeroportos*
};

// Cria gestor
GestorAeroportos* gestor_aeroportos_create(void) {
    GestorAeroportos *ga = malloc(sizeof(GestorAeroportos));
    if (!ga) return NULL;
    ga->hash = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, (GDestroyNotify)destroy_aeroporto);
    return ga;
}

//Devolve hash table interna (para uso em queries)
GHashTable* gestor_aeroportos_get_hash(GestorAeroportos *ga) {
    return ga->hash;
}

// Adiciona aeroporto
void gestor_aeroportos_add(GestorAeroportos *ga, Aeroportos *aeroporto) {
    g_hash_table_insert(ga->hash, g_strdup(get_code_aeroporto(aeroporto)), aeroporto);
}

// Remove aeroporto
void gestor_aeroportos_remove(GestorAeroportos *ga, const char *code) {
    g_hash_table_remove(ga->hash, code);
}

// Retorna aeroporto
Aeroportos* gestor_aeroportos_get(GestorAeroportos *ga, const char *code) {
    return g_hash_table_lookup(ga->hash, code);
}

// Liberta gestor e todos os aeroportos
void gestor_aeroportos_free(GestorAeroportos *ga) {
    g_hash_table_destroy(ga->hash);
    free(ga);
}

void add_departures_aeroporto(GestorAeroportos *ga, const char *code) {
    Aeroportos *a = gestor_aeroportos_get(ga, code);
    if (a) {
        int current_departures = get_departures_aeroporto(a);
        set_departures_aeroporto(a, current_departures + 1);
    }
}

// Funcao que devolve o numero de aeroportos no gestor
guint gestor_aeroportos_get_length(GestorAeroportos *ga) {
    return g_hash_table_size(ga->hash);
}
