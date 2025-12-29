#include "gestor_passageiros.h"
#include "passageiros.h"
#include <glib.h>
#include <stdlib.h>

struct gestor_passageiros {
    GHashTable *hash;  // chave = code (char*), valor = Passageiros*
};

// Cria gestor
HashPassageiros* hash_passageiros_create(void) {
    HashPassageiros *gp = malloc(sizeof(HashPassageiros));
    if (!gp) return NULL;
    gp->hash = g_hash_table_new_full(g_str_hash, g_str_equal, free, (GDestroyNotify)destroy_passageiro);
    return gp;
}

//Devolve hash table interna (para uso em queries)
GHashTable* hash_passageiros_get_hash(HashPassageiros *gp) {
    return gp->hash;
}

// Adiciona passageiro
void hash_passageiros_add(HashPassageiros *gp, Passageiros *passageiro) {
    g_hash_table_insert(gp->hash, g_strdup(get_document_number_passageiros(passageiro)), passageiro);
}

// Remove passageiro
void hash_passageiros_remove(HashPassageiros *gp, const char *code) {
    g_hash_table_remove(gp->hash, code);
}

// Retorna aeroporto
Passageiros* hash_passageiros_get(HashPassageiros *gp, const char *code) {
    return g_hash_table_lookup(gp->hash, code);
}

// Liberta gestor e todos os passageiros
void hash_passageiros_free(HashPassageiros *gp) {
    g_hash_table_destroy(gp->hash);
    free(gp);
}


// Funcao que devolve o numero de passageiros no gestor
guint hash_passageiros_get_length(HashPassageiros *gp) {
    return g_hash_table_size(gp->hash);
}
