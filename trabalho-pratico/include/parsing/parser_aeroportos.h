#ifndef PARSER_AEROPORTOS_H
#define PARSER_AEROPORTOS_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aeroportos.h"

/**
 * @brief Função para fazer o parsing de uma linha de aeroporto em formato CSV.
 * 
 * @param line Linha de texto representando os dados do aeroporto
 * 
 * @return Ponteiro para a estrutura Aeroportos preenchida com os dados da linha
 */
Aeroportos *parse_aeroporto_line(const char *line);


/**
 * @brief Função para fazer o parsing e validação de uma linha de aeroporto em formato CSV.
 * 
 * @param line Linha de texto representando os dados do aeroporto
 * @param ferr Ponteiro para o ficheiro de erros onde serão registadas linhas inválidas
 * 
 * @return Ponteiro para a estrutura Aeroportos válida, ou NULL se a linha for inválida
 */
Aeroportos *parse_and_validate_aeroporto_line(const char *line, FILE *ferr);

#endif