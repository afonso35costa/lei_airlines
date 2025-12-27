#ifndef PARSER_VOOS_H
#define PARSER_VOOS_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "voos.h"

/**
 * @brief Função para fazer o parsing de uma linha de texto representando um voo.
 * 
 * @param line Linha de texto contendo os dados do voo
 * 
 * @return Ponteiro para a estrutura Voo criada a partir da linha, ou NULL em caso de erro
 */
Voo *parse_voo_line(const char *line);


/**
 * @brief Função para fazer o parsing e validação de uma linha de texto representando um voo.
 * 
 * @param line Linha de texto contendo os dados do voo
 * @param ferr Ponteiro para o arquivo de erros onde linhas inválidas serão registradas
 * 
 * @return Ponteiro para a estrutura Voo válida, ou NULL se a linha for inválida
 */
Voo *parse_and_validate_voo_line(const char *line, FILE *ferr);

#endif