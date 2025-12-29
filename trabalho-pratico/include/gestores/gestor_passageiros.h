#ifndef GESTOR_PASSAGEIROS_H
#define GESTOR_PASSAGEIROS_H

#include "passageiros.h"
#include <glib.h>

typedef struct gestor_passageiros HashPassageiros;

/**
 * @brief Cria uma nova tabela hash para gerir passageiros.
 * 
 * @param void Não recebe parâmetros
 * 
 * @return Ponteiro para a tabela hash de passageiros criado
 */

HashPassageiros* hash_passageiros_create(void);

/**
 * @brief Obtém a tabela hash interna de passageiros.
 * 
 * @param gp Ponteiro para a tabela hash de passageiros
 * 
 * @return Ponteiro para a tabela hash interna de passageiros 
 */

GHashTable* hash_passageiros_get_hash(HashPassageiros *gp);


/**
 * @brief Adiciona um passageiro à tabela hash.
 * 
 * @param gp Ponteiro para a tabela hash de passageiros
 * @param passageiro Ponteiro para o passageiro a ser adicionado
 * 
 * @return void
 */
void hash_passageiros_add(HashPassageiros *gp, Passageiros *passageiro);


/**
 * @brief Remove um passageiro da tabela hash pelo seu código.
 * 
 * @param gp Ponteiro para a tabela hash de passageiros
 * @param code Código do passageiro a ser removido
 * 
 * @return void
 */
void hash_passageiros_remove(HashPassageiros *gp, const char *code);


/**
 * @brief Obtém um passageiro da tabela hash pelo seu código.
 * 
 * @param gp Ponteiro para a tabela hash de passageiros
 * @param code Código do passageiro a ser obtido
 * 
 * @return Ponteiro para o passageiro encontrado, ou NULL se não encontrado
 */
Passageiros* hash_passageiros_get(HashPassageiros *gp, const char *code);


/**
 * @brief Liberta a memória associada à tabela hash de passageiros.
 * 
 * @param gp Ponteiro para a tabela hash de passageiros
 * 
 * @return void
 */
void hash_passageiros_free(HashPassageiros *gp);


/**
 * @brief Obtém o número de passageiros na tabela hash.
 * 
 * @param gp Ponteiro para a tabela hash de passageiros
 * 
 * @return Número de passageiros na tabela hash
 */
guint hash_passageiros_get_length(HashPassageiros *gp);


#endif
