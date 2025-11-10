#ifndef GESTOR_AERONAVES_H
#define GESTOR_AERONAVES_H

#include <glib.h>
#include "aeronaves.h"

typedef struct gestor_aeronaves GestorAeronaves;

// Cria um gestor de aeronaves vazio
GestorAeronaves* gestor_aeronaves_create(void);

// Adiciona uma aeronave ao gestor
void gestor_aeronaves_add(GestorAeronaves *ga, Aeronaves *aero);

// Remove aeronave pelo índice ou identificador
void gestor_aeronaves_remove(GestorAeronaves *ga, const char *identifier);

// Retorna ponteiro para aeronave pelo índice
Aeronaves* gestor_aeronaves_get(GestorAeronaves *ga, int index);

// Liberta toda a memória associada ao gestor e às aeronaves
void gestor_aeronaves_free(GestorAeronaves *ga);

#endif
