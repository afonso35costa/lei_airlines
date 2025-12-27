#ifndef GESTOR_VOOS_H
#define GESTOR_VOOS_H

#include <glib.h>
#include "voos.h"

/**
 * @brief Estrutura que representa um gestor de voos baseado em array.
 * 
 * - array: Array dinâmico de ponteiros para voos (GPtrArray)
 */
typedef struct gestor_voosArray ArrayVoos;


/**
 * @brief Cria um gestor de voos vazio
 * 
 * @param void Não recebe parâmetros
 * 
 * @return Ponteiro para o gestor de voos criado
 */
ArrayVoos* array_voos_create(void);


/**
 * @brief Adiciona um voo ao gestor
 * 
 * @param gv Ponteiro para o gestor de voos
 * @param v Ponteiro para o voo a ser adicionado
 * 
 * @return void
 */
void array_voos_add(ArrayVoos *gv, Voo *v);


/**
 * @brief Remove um voo do gestor pelo seu identificador
 * 
 * @param gv Ponteiro para o gestor de voos
 * @param flight_id Identificador do voo a ser removido
 * 
 * @return void
 */
void array_voos_remove(ArrayVoos *gv, const char *flight_id);


/**
 * @brief Retorna um voo do gestor pelo índice
 * 
 * @param gv Ponteiro para o gestor de voos
 * @param index Índice do voo a ser retornado
 * 
 * @return Ponteiro para o voo correspondente ao índice
 */
Voo* array_voos_get(ArrayVoos *gv, int index);


/**
 * @brief Retorna o array de voos do gestor
 * 
 * @param gv Ponteiro para o gestor de voos
 * 
 * @return Ponteiro para o array de voos (GPtrArray)
 */
GPtrArray* array_voos_get_array(ArrayVoos *gv);


/**
 * @brief Retorna o número de voos no gestor
 * 
 * @param gv Ponteiro para o gestor de voos
 * 
 * @return Número de voos no gestor
 */
guint array_voos_get_length(ArrayVoos *gv);


/**
 * @brief Liberta toda a memória associada ao gestor e aos voos
 * 
 * @param gv Ponteiro para o gestor de voos
 * 
 * @return void
 */
void array_voos_free(ArrayVoos *gv);

/**
 * @brief Estrutura que representa um gestor de voos baseado em hash table.
 * 
 * - hash: Hash table que mapeia identificadores de voos (flight_id) para ponteiros de voos (Voo*)
 */
typedef struct gestor_voosHash HashVoos;


/**
 * @brief Cria um gestor de voos vazio
 * 
 * @param void Não recebe parâmetros
 * 
 * @return Ponteiro para o gestor de voos criado
 */
HashVoos* hash_voos_create(void);


/**
 * @brief Retorna a hash table de voos do gestor
 * 
 * @param gv Ponteiro para o gestor de voos
 * 
 * @return Ponteiro para a hash table (GHashTable)
 */
GHashTable* hash_voos_get_hash(HashVoos *gv);


/**
 * @brief Adiciona um voo ao gestor
 * 
 * @param gv Ponteiro para o gestor de voos
 * @param v Ponteiro para o voo a ser adicionado
 * 
 * @return void
 */
void hash_voos_add(HashVoos *gv, Voo *v);


/**
 * @brief Remove um voo do gestor pelo seu identificador
 * 
 * @param gv Ponteiro para o gestor de voos
 * @param flight_id Identificador do voo a ser removido
 * 
 * @return void
 */
void hash_voos_remove(HashVoos *gv, const char *flight_id);


/**
 * @brief Retorna um voo do gestor pelo seu identificador
 * 
 * @param gv Ponteiro para o gestor de voos
 * @param flight_id Identificador do voo a ser retornado
 * 
 * @return Ponteiro para o voo correspondente ao identificador
 */
Voo* hash_voos_get(HashVoos *gv, const char *flight_id);


/**
 * @brief Liberta toda a memória associada ao gestor e aos voos
 * 
 * @param gv Ponteiro para o gestor de voos
 * 
 * @return void
 */
void hash_voos_free(HashVoos *gv);


/**
 * @brief Retorna o número de voos no gestor
 * 
 * @param gv Ponteiro para o gestor de voos
 * 
 * @return Número de voos no gestor
 */
guint hash_voos_get_length(HashVoos *gv);

#endif
