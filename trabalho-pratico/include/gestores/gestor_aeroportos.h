#ifndef GESTOR_AEROPORTOS_H
#define GESTOR_AEROPORTOS_H

#include <glib.h>
#include "aeroportos.h"

/**
 * @brief Estrutura que representa um gestor de aeroportos utilizando uma hash table.
 * 
 * - hash: Tabela hash onde a chave é o código IATA (char*) e o valor é um ponteiro para Aeroportos*
 */
typedef struct gestor_aeroportos GestorAeroportos;


/**
 * @brief Cria um novo gestor de aeroportos.
 * 
 * @param void Não recebe parâmetros
 * 
 * @return Ponteiro para o gestor de aeroportos criado, ou NULL em caso de falha na alocação
 */
GestorAeroportos* gestor_aeroportos_create(void);


/**
 * @brief Devolve a hash table interna do gestor de aeroportos (para uso em queries).
 * 
 * @param ga Ponteiro para o gestor de aeroportos
 * 
 * @return Ponteiro para a hash table interna
 */
GHashTable* gestor_aeroportos_get_hash(GestorAeroportos *ga);


/**
 * @brief Adiciona um aeroporto ao gestor.
 * 
 * @param ga Ponteiro para o gestor de aeroportos
 * @param aeroporto Ponteiro para o aeroporto a ser adicionado
 * 
 * @return void
 */
void gestor_aeroportos_add(GestorAeroportos *ga, Aeroportos *aeroporto);


/**
 * @brief Remove um aeroporto do gestor pelo código IATA.
 * 
 * @param ga Ponteiro para o gestor de aeroportos
 * @param code Código IATA do aeroporto a ser removido
 * 
 * @return void
 */
void gestor_aeroportos_remove(GestorAeroportos *ga, const char *code);


/**
 * @brief Retorna um aeroporto do gestor pelo código IATA.
 * 
 * @param ga Ponteiro para o gestor de aeroportos
 * @param code Código IATA do aeroporto a ser retornado
 * 
 * @return Ponteiro para o aeroporto encontrado, ou NULL se não existir
 */
Aeroportos* gestor_aeroportos_get(GestorAeroportos *ga, const char *code);


/**
 * @brief Liberta o gestor de aeroportos e todos os aeroportos associados.
 * 
 * @param ga Ponteiro para o gestor de aeroportos a ser libertado
 * 
 * @return void
 */
void gestor_aeroportos_free(GestorAeroportos *ga);


/**
 * @brief Incrementa o número de partidas de um aeroporto no gestor.
 * 
 * @param ga Ponteiro para o gestor de aeroportos
 * @param code Código IATA do aeroporto cuja contagem de partidas será incrementada
 * 
 * @return void
 */
void add_departures_aeroporto(GestorAeroportos *ga, const char *code);


/**
 * @brief Obtém o número de aeroportos no gestor.
 * 
 * @param ga Ponteiro para o gestor de aeroportos
 * 
 * @return Número de aeroportos no gestor
 */
guint gestor_aeroportos_get_length(GestorAeroportos *ga);

#endif