#ifndef VALIDACAO_PASSAGEIROS_H
#define VALIDACAO_PASSAGEIROS_H
#include "passageiros.h"


/**
 * @brief Valida o número do documento do passageiro.
 * 
 * @param document_number Número do documento a validar
 * 
 * @return 1 se o número do documento for válido, 0 caso contrário 
 */
int validar_document_number_passageiro(const char *document_number);


/**
 * @brief Valida o email do passageiro.
 * 
 * @param email Email a validar
 * 
 * @return 1 se o email for válido, 0 caso contrário
 */
int validar_email_passageiro(const char *email);


/**
 * @brief Valida o género do passageiro.
 * 
 * @param genero Género a validar
 * 
 * @return 1 se o género for válido, 0 caso contrário
 */
int validar_genero_passageiro(const char *genero);


/**
 * @brief Valida a data de nascimento do passageiro.
 * 
 * @param dob Data de nascimento a validar
 * 
 * @return 1 se a data de nascimento for válida, 0 caso contrário
 */
int validar_dob_passageiro(const char *dob);


/**
 * @brief Validação geral do passageiro.
 * 
 * @param p Ponteiro para a estrutura Passageiros
 * 
 * @return 1 se o passageiro for válido, 0 caso contrário
 */
int validar_passageiro(const Passageiros *p);

#endif
