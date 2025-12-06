#ifndef GESTOR_AERONAVES_H
#define GESTOR_AERONAVES_H

#include <glib.h>
#include "aeronaves.h"

typedef struct gestor_aeronaves GestorAeronaves;

typedef struct hash_value HashValue;

// Cria gestor
GestorAeronaves* gestor_aeronaves_create(void);

//Devolve hash table interna (para uso em queries)
GHashTable* gestor_aeronaves_get_hash(GestorAeronaves *ga);

// Cria value para hash table
HashValue* hash_value_create(void);

// Adiciona aeronave a value
void add_aeronave_value (HashValue *hv, Aeronaves *aeronave);

// Adiciona voo ao contador na value
void add_voo_value (HashValue *hv);

// Adiciona value a gestor
void gestor_aeronaves_add(GestorAeronaves *ga, HashValue *hv);

// Remove aeronave por identificador
void gestor_aeronaves_remove(GestorAeronaves *ga, const char *identifier);

// Retorna value pelo identifier
HashValue* gestor_aeronaves_get(GestorAeronaves *ga, const char *identifier);

// Retorna aeronave em value
Aeronaves* get_aeronave_value(HashValue *hv);

// Retorna numero de voos
int get_num_voos_aeronave(HashValue *hv);

// Liberta gestor
void gestor_aeronaves_free(GestorAeronaves *ga);

// Liberta value
void hash_value_free(HashValue *hv);

#endif