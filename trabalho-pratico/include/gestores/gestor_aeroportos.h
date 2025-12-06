#ifndef GESTOR_AEROPORTOS_H
#define GESTOR_AEROPORTOS_H

#include <glib.h>
#include "aeroportos.h"

typedef struct gestor_aeroportos GestorAeroportos;

// Cria um gestor de aeroportos vazio
GestorAeroportos* gestor_aeroportos_create(void);

//Devolve hash table interna (para uso em queries)
GHashTable* gestor_aeroportos_get_hash(GestorAeroportos *ga);

// Adiciona um aeroporto ao gestor
void gestor_aeroportos_add(GestorAeroportos *ga, Aeroportos *aeroporto);

// Remove um aeroporto pelo código IATA
void gestor_aeroportos_remove(GestorAeroportos *ga, const char *code);

// Retorna ponteiro para aeroporto pelo código IATA (NULL se não existir)
Aeroportos* gestor_aeroportos_get(GestorAeroportos *ga, const char *code);

// Liberta toda a memória associada ao gestor e aos aeroportos
void gestor_aeroportos_free(GestorAeroportos *ga);

// Incrementa o número de partidas de um aeroporto pelo código IATA
void add_departures_aeroporto(GestorAeroportos *ga, const char *code);

// Funcao que devolve o numero de aeroportos no gestor
guint gestor_aeroportos_get_length(GestorAeroportos *ga);

#endif