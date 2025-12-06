#include <glib.h>
#include <stdlib.h>
#include <string.h>
#include "aeronaves.h"
#include "gestor_aeronaves.h"

struct gestor_aeronaves {
    GHashTable *hash;  // hash table de Aeronaves*
};

struct conta_voos {
    GHashTable *table; // hash table de contadores
};

// Cria gestor
GestorAeronaves* gestor_aeronaves_create(void) {
    GestorAeronaves *ga = malloc(sizeof(GestorAeronaves));
    if (!ga) return NULL;
    ga->hash = g_hash_table_new_full(g_str_hash, g_str_equal, free, free);
    return ga;
}

//Devolve hash table interna (para uso em queries)
GHashTable* gestor_aeronaves_get_hash(GestorAeronaves *ga) {
    return ga->hash;
}

// Struct value para hash table

struct hash_value {
    int count;
    Aeronaves *aeronave;
};

// Cria value para hash table
HashValue* hash_value_create(void) {
    HashValue *hv = malloc(sizeof(HashValue));
    if (!hv) return NULL;
    hv->count = 0;
    hv->aeronave = NULL;
    return hv;
}

// Adiciona aeronave a value
void add_aeronave_value (HashValue *hv, Aeronaves *aeronave) {
    hv->aeronave = aeronave;
}

// Adiciona voo
void add_voo_value (HashValue *hv) {
    hv->count++;
}

// Adiciona value a gestor
void gestor_aeronaves_add(GestorAeronaves *ga, HashValue *value) {
    g_hash_table_insert(ga->hash, strdup(get_identifier_aeronave(value->aeronave)), value);
}

// Remove aeronave por aircraft identifier
void gestor_aeronaves_remove(GestorAeronaves *ga, const char *identifier) {
    g_hash_table_remove(ga->hash, identifier);
}

// Retorna value pelo identifier
HashValue* gestor_aeronaves_get(GestorAeronaves *ga, const char *identifier) {
    return g_hash_table_lookup(ga->hash, identifier);
}

// Retorna aeronave em value
Aeronaves* get_aeronave_value(HashValue *hv) {
    return hv->aeronave;
}

//Retorna numero de voos
int get_num_voos_aeronave(HashValue *hv) {
    return hv->count;
}

// Liberta gestor e todas as aeronaves
void gestor_aeronaves_free(GestorAeronaves *ga) {
    g_hash_table_destroy(ga->hash);
    free(ga);
}

// Liberta value
void hash_value_free(HashValue *hv) {
    if (hv) {
        free_aeronave(hv->aeronave);
        free(hv);
    }
}