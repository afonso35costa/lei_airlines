#ifndef GESTOR_PASSAGEIROS_H
#define GESTOR_PASSAGEIROS_H

#include "passageiros.h"
#include <glib.h>

typedef struct gestor_passageiros HashPassageiros;

// FALTA DOCUMENTAÇÃO

HashPassageiros* hash_passageiros_create(void);

GHashTable* hash_passageiros_get_hash(HashPassageiros *gp);

void hash_passageiros_add(HashPassageiros *gp, Passageiros *passageiro);
void hash_passageiros_remove(HashPassageiros *gp, const char *code);
Passageiros* hash_passageiros_get(HashPassageiros *gp, const char *code);
void hash_passageiros_free(HashPassageiros *gp);
guint hash_passageiros_get_length(HashPassageiros *gp);

#endif
