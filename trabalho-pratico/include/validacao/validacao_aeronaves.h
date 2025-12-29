#ifndef VALIDACAO_AERONAVES_H
#define VALIDACAO_AERONAVES_H

#include "aeronaves.h"



/**
 * @brief Valida o ano de fabrico da aeronave.
 * 
 * @param anoA Ano de fabrico como string
 * 
 * @return 1 se o ano for válido, 0 caso contrário
 */
int validar_ano_aeronave(const char *anoA);


/**
 * @brief Validação geral da aeronave.
 * 
 * @param a Ponteiro para a estrutura Aeronaves
 * 
 * @return 1 se a aeronave for válida, 0 caso contrário
 */
int validar_aeronave(const Aeronaves *a);


/**
 * @brief Processa o ficheiro CSV de aeronaves e gera um ficheiro de erros.
 * 
 * @param input_path Caminho para o ficheiro de entrada
 * 
 * @param erros_path Caminho para o ficheiro de erros
 */
void processar_ficheiro_aeronaves(const char *input_path, const char *erros_path);

#endif
