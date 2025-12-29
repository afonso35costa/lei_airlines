#ifndef VALIDACAO_AEROPORTOS_H
#define VALIDACAO_AEROPORTOS_H

#include "aeroportos.h"


/**
 * @brief Validação do tipo de aeroporto.
 * 
 * @param type Tipo do aeroporto
 * 
 * @return 1 se o tipo for válido, 0 caso contrário
 */
int validar_type_aeroporto (const char *type);


/**
 * @brief Validação da latitude do aeroporto.
 * 
 * @param latitude Latitude do aeroporto
 * 
 * @return 1 se a latitude for válida, 0 caso contrário
 */
int validar_latitude_aeroporto (double latitude);


/**
 * @brief Validação da longitude do aeroporto.
 * 
 * @param longitude Longitude do aeroporto
 * 
 * @return 1 se a longitude for válida, 0 caso contrário
 */
int validar_longitude_aeroporto (double longitude);


/**
 * @brief Validação do código IATA do aeroporto.
 * 
 * @param code Código IATA do aeroporto
 * 
 * @return 1 se o código for válido, 0 caso contrário
 */
int validar_code_aeroporto(const char *code);


/**
 * @brief Validação geral do aeroporto.
 * 
 * @param a Ponteiro para a estrutura Aeroportos
 * 
 * @return 1 se o aeroporto for válido, 0 caso contrário
 */
int validar_aeroporto(const Aeroportos *a);


/**
 * @brief Processa o ficheiro de aeroportos e gera um ficheiro de erros.
 * 
 * @param input_path Caminho do ficheiro de entrada
 * @param erros_path Caminho do ficheiro de erros a ser gerado
 */
void processar_ficheiro_aeroportos(const char *input_path, const char *erros_path);

#endif
