#ifndef GESTOR_AERONAVES_H
#define GESTOR_AERONAVES_H

#include <glib.h>
#include "aeronaves.h"

typedef struct gestor_aeronaves GestorAeronaves;

// Cria gestor
GestorAeronaves* gestor_aeronaves_create(void);

// Adiciona aeronave
void gestor_aeronaves_add(GestorAeronaves *ga, Aeronaves *aero);

// Remove aeronave por identificador
void gestor_aeronaves_remove(GestorAeronaves *ga, const char *identifier);

// Retorna aeronave pelo índice
Aeronaves* gestor_aeronaves_get(GestorAeronaves *ga, int index);

// 🔧 NOVO: Retorna tamanho do array
guint gestor_aeronaves_get_length(GestorAeronaves *ga);

// 🔧 NOVO: Procura aeronave por identificador
Aeronaves* gestor_aeronaves_find_by_id(GestorAeronaves *ga, const char *identifier);

// Liberta gestor
void gestor_aeronaves_free(GestorAeronaves *ga);

#endif