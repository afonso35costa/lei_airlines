#ifndef VALIDACAO_RESERVAS_H
#define VALIDACAO_RESERVAS_H

#include "reservas.h"


/**
 * @brief Funções de validação individuais
 * 
 * @param reservation_id Identificador da reserva a validar 
 * 
 * @return int
 */
int validar_reservation_id_reservas(const char *reservation_id);


/**
 * @brief Valida se o número de documento do passageiro existe no sistema. 
 * 
 * @param document_number Número de documento do passageiro a validar 
 * 
 * @return 1 se o número de documento existir, 0 caso contrário
 */
int validar_document_number_passageiro_exists(const char *document_number);


/**
 * @brief Valida se todos os IDs de voo na lista existem no sistema.
 * 
 * @param flight_ids Lista de IDs de voo a validar
 * 
 * @return 1 se todos os IDs existirem, 0 caso contrário
 */
int validar_flight_ids_exist(char **flight_ids);


/**
 * @brief Valida o número de documento da reserva.
 * 
 * @param document_number Número de documento da reserva a validar
 * 
 * @return 1 se o número de documento for válido, 0 caso contrário
 */
int validar_document_number_reserva(const char *document_number);


/**
 * @brief Valida a lista de IDs de voo na reserva.
 * 
 * @param flight_ids Lista de IDs de voo a validar
 * 
 * @return 1 se todos os IDs forem válidos, 0 caso contrário
 */
int validar_listas_reservas(char **flight_ids);


/**
 * @brief Validação geral da reserva.
 * 
 * @param r Ponteiro para a estrutura Reservas
 * 
 * @return 1 se a reserva for válida, 0 caso contrário
 */
int validar_reserva(const Reservas *r);


/**
 * @brief Processa o ficheiro CSV de reservas e gera um ficheiro de erros.
 * 
 * @param ficheiro_entrada Caminho para o ficheiro de entrada
 * @param ficheiro_erros Caminho para o ficheiro de erros
 * 
 * @return void
 */
void processar_ficheiro_reservas(const char *ficheiro_entrada, const char *ficheiro_erros);

#endif
