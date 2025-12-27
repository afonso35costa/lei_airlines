#ifndef PARSER_RESERVAS_H
#define PARSER_RESERVAS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "reservas.h"

/**
 * @brief Converte uma string "true"/"false" para um valor booleano.
 * 
 * @param str A string a ser convertida.
 * 
 * @return true se a string for "true", false caso contrário.
 */
bool str_to_bool(const char *str);


/**
 * @brief Realiza o parsing de uma string contendo IDs de voos no formato de lista.
 * 
 * @param str A string contendo os IDs de voos, por exemplo: "['TI12433', 'TI12434']".
 * 
 * @return Um array de strings (char **) contendo os IDs de voos. O array é terminado por um ponteiro NULL.
 */
char **parse_flight_ids(char *str);


/**
 * @brief Realiza o parsing de uma linha de reserva e cria uma estrutura Reservas.
 * 
 * @param line A linha de texto contendo os dados da reserva.
 * 
 * @return Ponteiro para a estrutura Reservas criada.
 */
Reservas *parse_reserva_line(const char *line);


/**
 * @brief Realiza o parsing e validação de uma linha de reserva.
 * 
 * @param line A linha de texto contendo os dados da reserva.
 * @param ferr Ponteiro para o arquivo de erros onde linhas inválidas serão registradas.
 * 
 * @return Ponteiro para a estrutura Reservas válida, ou NULL se a linha for inválida.
 */
Reservas *parse_and_validate_reserva_line(const char *line, FILE *ferr);

#endif