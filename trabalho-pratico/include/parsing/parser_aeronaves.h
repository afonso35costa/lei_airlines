#ifndef PARSER_AERONAVES_H
#define PARSER_AERONAVES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aeronaves.h"

/**
 * @brief Função para fazer o parsing de uma linha de texto representando uma aeronave em formato CSV.
 * 
 * @param line Linha de texto contendo os dados da aeronave
 * 
 * @return Ponteiro para a estrutura Aeronaves criada a partir da linha, ou NULL em caso de erro
 */
Aeronaves *parse_aeronave_line(const char *line);


/**
 * @brief Função para fazer o parsing e validação de uma linha de texto representando uma aeronave em formato CSV.
 * 
 * @param line Linha de texto contendo os dados da aeronave
 * @param ferr Ponteiro para o ficheiro de erros onde serão registadas as linhas inválidas
 * 
 * @return Ponteiro para a estrutura Aeronaves criada e validada, ou NULL em caso de erro
 */
Aeronaves *parse_and_validate_aeronave_line(const char *line, FILE *ferr);

#endif