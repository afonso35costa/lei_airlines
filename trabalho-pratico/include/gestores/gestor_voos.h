#ifndef GESTOR_VOOS_H
#define GESTOR_VOOS_H

#include <glib.h>
#include "voos.h"

typedef struct gestor_voosArray ArrayVoos;

// Cria um gestor de voos vazio
ArrayVoos* array_voos_create(void);

// Adiciona um voo ao gestor
void array_voos_add(ArrayVoos *gv, Voo *v);

// Remove voo pelo índice ou identificador
void array_voos_remove(ArrayVoos *gv, const char *flight_id);

// Retorna ponteiro para voo pelo índice
Voo* array_voos_get(ArrayVoos *gv, int index);

// Retorna o array de voos
GPtrArray* array_voos_get_array(ArrayVoos *gv);

// Retorna o número de voos no gestor
guint array_voos_get_length(ArrayVoos *gv);

// Liberta toda a memória associada ao gestor e aos voos
void array_voos_free(ArrayVoos *gv);

typedef struct gestor_voosHash HashVoos;

// Cria um gestor de voos vazio
HashVoos* hash_voos_create(void);

//Devevolver a hash table interna (para uso em queries)
GHashTable* hash_voos_get_hash(HashVoos *gv);

// Adiciona um voo ao gestor
void hash_voos_add(HashVoos *gv, Voo *v);

// Remove voo pelo identificador
void hash_voos_remove(HashVoos *gv, const char *flight_id);

// Retorna ponteiro para voo pelo identificador
Voo* hash_voos_get(HashVoos *gv, const char *flight_id);

// Liberta toda a memória associada ao gestor e aos voos
void hash_voos_free(HashVoos *gv);

// Função que devolve o número de voos no gestor
guint hash_voos_get_length(HashVoos *gv);

#endif
