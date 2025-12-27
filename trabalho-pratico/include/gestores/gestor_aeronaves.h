#ifndef GESTOR_AERONAVES_H
#define GESTOR_AERONAVES_H

#include <glib.h>
#include "aeronaves.h"
#include <stdlib.h>

/**
 * @brief Estrutura que representa um gestor de aeronaves, responsável por armazenar e gerenciar múltiplas aeronaves.
 * 
 * - hash: Tabela hash que mapeia identificadores de aeronaves para suas respectivas estruturas Aeronaves.
 * 
 */
typedef struct gestor_aeronaves GestorAeronaves;


/**
 * @brief Estrutura que representa um contador de voos associados a aeronaves.
 * 
 * - table: Tabela hash que mapeia identificadores de aeronaves para o número de voos realizados.
 * 
 */
typedef struct conta_voos ContaVoos;


/**
 * @brief Cria um novo gestor de aeronaves.
 * 
 * @param void Não recebe parâmetros
 * 
 * @return Ponteiro para o gestor de aeronaves criado, ou NULL em caso de falha na alocação
 * 
 */
GestorAeronaves* gestor_aeronaves_create(void);


/**
 * @brief Devolve a hash table interna do gestor de aeronaves (para uso em queries).
 * 
 * @param ga Ponteiro para o gestor de aeronaves
 * 
 * @return Ponteiro para a hash table interna
 */
GHashTable* gestor_aeronaves_get_hash(GestorAeronaves *ga);


/**
 * @brief Adiciona uma aeronave ao gestor de aeronaves.
 * 
 * @param ga Ponteiro para o gestor de aeronaves
 * @param aeronave Ponteiro para a aeronave a ser adicionada
 * 
 * @return void
 */
void gestor_aeronaves_add(GestorAeronaves *ga, Aeronaves *aeronave);



/**
 * @brief Remove uma aeronave do gestor de aeronaves pelo seu identificador.
 * 
 * @param ga Ponteiro para o gestor de aeronaves
 * @param identifier Identificador da aeronave a ser removida
 * 
 * @return void
 */  
void gestor_aeronaves_remove(GestorAeronaves *ga, const char *identifier);


/**
 * @brief Retorna uma aeronave do gestor pelo seu identificador.
 * 
 * @param ga Ponteiro para o gestor de aeronaves
 * @param identifier Identificador da aeronave a ser retornada
 * 
 * @return Ponteiro para a aeronave correspondente, ou NULL se não encontrada
 */
Aeronaves* gestor_aeronaves_get(GestorAeronaves *ga, const char *identifier);


/**
 * @brief Liberta a memória associada ao gestor de aeronaves e todas as aeronaves armazenadas.
 * 
 * @param ga Ponteiro para o gestor de aeronaves a ser libertado
 * 
 * @return void 
 */
void gestor_aeronaves_free(GestorAeronaves *ga);

#endif