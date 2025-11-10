#ifndef GESTOR_VOOS_H
#define GESTOR_VOOS_H

#include <glib.h>
#include "voos.h"

typedef struct gestor_voos GestorVoos;

// Cria um gestor de voos vazio
GestorVoos* gestor_voos_create(void);

// Adiciona um voo ao gestor
void gestor_voos_add(GestorVoos *gv, Voo *v);

// Remove voo pelo índice ou identificador
void gestor_voos_remove(GestorVoos *gv, const char *flight_id);

// Retorna ponteiro para voo pelo índice
Voo* gestor_voos_get(GestorVoos *gv, int index);

// Liberta toda a memória associada ao gestor e aos voos
void gestor_voos_free(GestorVoos *gv);

#endif
