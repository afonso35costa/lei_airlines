#include <glib.h>
#include <stdlib.h>
#include <string.h>
#include "aeronaves.h"
#include "gestor_aeronaves.h"

struct gestor_aeronaves {
    GHashTable *hash;  // hash table de Aeronaves*
};

// Cria gestor
GestorAeronaves* gestor_aeronaves_create(void) {
    GestorAeronaves *ga = malloc(sizeof(GestorAeronaves));
    if (!ga) return NULL;
    ga->hash = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, (GDestroyNotify)destroy_aeronave);
    return ga;
}

//Devolve hash table interna (para uso em queries)
GHashTable* gestor_aeronaves_get_hash(GestorAeronaves *ga) {
    return ga->hash;
}

// Adiciona aeronave a gestor
void gestor_aeronaves_add(GestorAeronaves *ga, Aeronaves *aeronave) {
    g_hash_table_insert(ga->hash, (gpointer)get_identifier_aeronave(aeronave), aeronave);
}

// Remove aeronave por aircraft identifier
void gestor_aeronaves_remove(GestorAeronaves *ga, const char *identifier) {
    g_hash_table_remove(ga->hash, identifier);
}

// Retorna aeronave pelo identifier
Aeronaves* gestor_aeronaves_get(GestorAeronaves *ga, const char *identifier) {
    return g_hash_table_lookup(ga->hash, identifier);
}

// Liberta gestor e todas as aeronaves
void gestor_aeronaves_free(GestorAeronaves *ga) {
    g_hash_table_destroy(ga->hash);
    free(ga);
}
