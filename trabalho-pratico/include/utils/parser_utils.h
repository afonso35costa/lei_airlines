#ifndef PARSER_UTILS_H
#define PARSER_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Definição de tipos de funções para parsing e adição de gestores.
 * 
 * @param line Linha de dados a ser analisada
 * @param err_file Ponteiro para o arquivo de erros
 * 
 * @return Ponteiro genérico para o objeto criado a partir da linha
 */
typedef void *(*FuncaoParser)(const char *line, FILE *err_file);


/**
 * @brief Definição de tipo de função para adicionar gestores a um objeto.
 * 
 * @param objeto Ponteiro para o objeto ao qual os gestores serão adicionados
 * @param gestor1 Ponteiro para o primeiro gestor
 * @param gestor2 Ponteiro para o segundo gestor
 * @param gestor3 Ponteiro para o terceiro gestor
 */
typedef int (*FuncaoAddGestor)(void *objeto, void *gestor1, void *gestor2, void *gestor3, void *gestor4);


/**
 * @brief Função strip_quotes - remove aspas externas de uma string
 * 
 * @param str String de entrada possivelmente com aspas
 * 
 * @return Nova string sem aspas (alocada dinamicamente) 
 */

char* strip_quotes(const char *str);


/**
 * @brief Função ignorar_virgulas - lê um campo de uma string CSV, ignorando vírgulas dentro de aspas
 * 
 * @param str Ponteiro para a string de entrada (será atualizado para a próxima posição após o campo lido)
 * 
 * @return Nova string contendo o campo lido (alocada dinamicamente)
 */
char* ignorar_virgulas(char **str);

#endif