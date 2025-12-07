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

// Adiciona value a gestor
void gestor_aeronaves_add(GestorAeronaves *ga, Aeronaves *aeronave);

// Remove aeronave por identificador
void gestor_aeronaves_remove(GestorAeronaves *ga, const char *identifier);

// Retorna aeronave pelo identifier
Aeronaves* gestor_aeronaves_get(GestorAeronaves *ga, const char *identifier);

// Liberta gestor
void gestor_aeronaves_free(GestorAeronaves *ga);

#endif