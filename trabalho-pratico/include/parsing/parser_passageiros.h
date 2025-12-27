#ifndef PARSER_PASSAGEIROS_H
#define PARSER_PASSAGEIROS_H


#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "passageiros.h"

/**
 * @brief Função para analisar uma linha de dados de passageiro e criar uma estrutura Passageiros correspondente.
 * 
 * @param line Linha de dados do passageiro em formato CSV
 * 
 * @return Ponteiro para a estrutura Passageiros criada, ou NULL em caso de erro
 */
Passageiros *parse_passageiro_line(const char *line);


/**
 * @brief Função para analisar e validar uma linha de dados de passageiro.
 * 
 * @param line Linha de dados do passageiro em formato CSV
 * @param ferr Ponteiro para o arquivo de erros onde linhas inválidas serão registradas
 * 
 * @return Ponteiro para a estrutura Passageiros válida, ou NULL se a linha for inválida
 */
Passageiros *parse_and_validate_passageiro_line(const char *line, FILE *ferr);

#endif