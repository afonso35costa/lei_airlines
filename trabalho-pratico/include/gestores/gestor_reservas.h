#ifndef GESTOR_RESERVAS_H
#define GESTOR_RESERVAS_H

#include <glib.h>
#include "reservas.h"

/**
 * @brief Estrutura que representa um gestor de reservas utilizando um array dinâmico.
 * 
 * - array: Array dinâmico de ponteiros para Reservas (GPtrArray)
 */
typedef struct gestor_reservas GestorReservas;


/**
 * @brief Cria um novo gestor de reservas.
 * 
 * @param void Não recebe parâmetros
 * 
 * @return Ponteiro para o gestor de reservas criado
 */
GestorReservas* gestor_reservas_create(void);

/**
 * @brief Adiciona uma reserva ao gestor.
 * 
 * @param gr Ponteiro para o gestor de reservas
 * @param r Ponteiro para a reserva a ser adicionada
 * 
 * @return void
 */
void gestor_reservas_add(GestorReservas *gr, Reservas *r);


/**
 * @brief Remove uma reserva do gestor pelo seu ID.
 * 
 * @param gr Ponteiro para o gestor de reservas
 * @param reservation_id ID da reserva a ser removida
 * 
 * @return void
 */
void gestor_reservas_remove(GestorReservas *gr, const char *reservation_id);


/**
 * @brief Retorna uma reserva do gestor pelo índice.
 * 
 * @param gr Ponteiro para o gestor de reservas
 * @param index Índice da reserva a ser retornada
 * 
 * @return Ponteiro para a reserva correspondente ao índice
 */
Reservas* gestor_reservas_get(GestorReservas *gr, int index);


/**
 * @brief Retorna o array de reservas do gestor.
 * 
 * @param gr Ponteiro para o gestor de reservas
 * 
 * @return Ponteiro para o array de reservas
 */
GPtrArray* gestor_reservas_get_array(GestorReservas *gr);


/**
 * @brief Retorna o número de reservas no gestor.
 * 
 * @param gr Ponteiro para o gestor de reservas
 * 
 * @return Número de reservas no gestor
 */
guint gestor_reservas_get_length(GestorReservas *gr);


/**
 * @brief Liberta a memória associada ao gestor de reservas e todas as reservas nele contidas.
 * 
 * @param gr Ponteiro para o gestor de reservas a ser libertado
 * 
 * @return void
 */
void gestor_reservas_free(GestorReservas *gr);

// FALTA DOCUMENTAR

typedef struct gestor_resHash HashReservas;

HashReservas* hash_reservas_create(void);

GHashTable* hash_reservas_get_hash(HashReservas *gr);

void hash_reservas_add(HashReservas *gr, Reservas *reserva);

void hash_reservas_remove(HashReservas *gr, const char *id);

Reservas* hash_reservas_get(HashReservas *gr, const char *id);

void hash_reservas_free(HashReservas *gr);

guint hash_reservas_get_length(HashReservas *gr);

#endif