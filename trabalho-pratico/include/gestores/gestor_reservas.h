#ifndef GESTOR_RESERVAS_H
#define GESTOR_RESERVAS_H

#include <glib.h>
#include "reservas.h"



/**
 * @brief Estrutura que representa um gestor de reservas utilizando uma tabela hash.
 * 
 * - hash: Tabela hash que mapeia IDs de reservas para listas de ponteiros para Reservas (GHashTable)
 */
typedef struct gestor_resHash HashReservas;


/**
 * @brief Cria uma nova tabela hash para gerir reservas.
 * 
 * @param void Não recebe parâmetros
 * 
 * @return Ponteiro para a tabela hash de reservas criado
 */
HashReservas* hash_reservas_create(void);


/**
 * @brief Obtém a tabela hash interna de reservas.
 * 
 * @param gr Ponteiro para a tabela hash de reservas
 * 
 * @return Ponteiro para a tabela hash interna de reservas 
 */
GHashTable* hash_reservas_get_hash(HashReservas *gr);


/**
 * @brief Adiciona uma reserva à tabela hash.
 * 
 * @param gr Ponteiro para a tabela hash de reservas
 * @param reserva Ponteiro para a reserva a ser adicionada
 * 
 * @return void
 */
void hash_reservas_add(HashReservas *gr, Reservas *reserva);


/**
 * @brief Remove uma reserva da tabela hash pelo seu ID.
 * 
 * @param gr Ponteiro para a tabela hash de reservas
 * @param id ID da reserva a ser removida
 * 
 * @return void
 */
void hash_reservas_remove(HashReservas *gr, const char *id);


/**
 * @brief Obtém uma lista de reservas da tabela hash pelo seu ID.
 * 
 * @param gr Ponteiro para a tabela hash de reservas
 * @param id ID da reserva a ser obtida
 * 
 * @return Lista de ponteiros para Reservas encontrados, ou NULL se não encontrado
 */
GList* hash_reservas_get(HashReservas *gr, const char *id);


/**
 * @brief Liberta a memória associada à tabela hash de reservas e todas as reservas.
 * 
 * @param gr Ponteiro para a tabela hash de reservas a ser libertada
 * 
 * @return void
 */
void hash_reservas_free(HashReservas *gr);


/**
 * @brief Obtém o número de entradas na tabela hash de reservas.
 * 
 * @param gr Ponteiro para a tabela hash de reservas
 * 
 * @return Número de entradas na tabela hash de reservas
 */
guint hash_reservas_get_length(HashReservas *gr);

#endif