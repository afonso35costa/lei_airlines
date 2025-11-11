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
    ga->hash = g_hash_table_new_full(g_str_hash, g_str_equal, free, (GDestroyNotify)free_aeroporto);
    return ga;
}

// Adiciona aeroporto
void gestor_aeroportos_add(GestorAeroportos *ga, Aeroportos *aeroporto) {
    g_hash_table_insert(ga->hash, g_strdup(get_code(aeroporto)), aeroporto);
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
