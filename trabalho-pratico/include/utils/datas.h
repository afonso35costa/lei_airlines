#ifndef DATAS_H
#define DATAS_H

#include <stdbool.h>
#include <stddef.h>

/**
 * @brief Estrutura que representa uma data e hora.
 * 
 * - data: Representa a data no formato AAAAMMDD (ano, mês, dia).
 * - hora: Representa a hora no formato HHMM (hora, minuto).
 */
typedef struct DataHora DataHora;


/**
 * @brief Lê uma string no formato "YYYY-MM-DD HH:MM" e retorna uma estrutura DataHora.
 * 
 * @param texto String contendo a data e hora no formato especificado
 * 
 * @return Ponteiro para a estrutura DataHora criada
 */
DataHora* ler_data_hora(const char *texto);


/**
 * @brief Lê uma string no formato "YYYY-MM-DD" e retorna uma estrutura DataHora com hora = 0.
 * 
 * @param texto String contendo a data no formato especificado
 * 
 * @return Ponteiro para a estrutura DataHora criada
 */
DataHora* ler_data(const char *texto);


/**
 * @brief Converte uma estrutura DataHora para uma string no formato "YYYY-MM-DD HH:MM".
 * 
 * @param dh Ponteiro para a estrutura DataHora a ser convertida
 * 
 * @return String formatada representando a data e hora
 */
char *data_hora_para_texto(DataHora *dh);


/**
 * @brief Converte apenas a data para uma string no formato "YYYY-MM-DD".
 * 
 * @param dh Ponteiro para a estrutura DataHora a ser convertida
 * 
 * @return String formatada representando a data
 */
char *data_para_texto(DataHora *dh);


/**
 * @brief Calcula a diferença aproximada em dias entre duas datas.
 * 
 * @param d1 Ponteiro para a primeira data
 * @param d2 Ponteiro para a segunda data
 * 
 * @return Diferença em dias entre as duas datas
 */
int diferenca_em_dias(DataHora *d1, DataHora *d2);


/**
 * @brief Calcula a diferença em minutos entre duas datas e horas.
 * 
 * @param d1 Ponteiro para a primeira data e hora
 * @param d2 Ponteiro para a segunda data e hora
 * 
 * @return Diferença em minutos entre as duas datas e horas
 */
int diferenca_em_minutos(DataHora *d1, DataHora *d2);


/**
 * @brief Calcula a diferença em anos entre duas datas completas.
 * 
 * @param data1 Primeira data no formato AAAAMMDD
 * @param data2 Segunda data no formato AAAAMMDD
 * 
 * @return Diferença em anos entre as duas datas
 */
int diferenca_em_anos(int data1, int data2);


/**
 * @brief Verifica se uma data está entre duas outras datas (inclusive).
 * 
 * @param alvo Ponteiro para a data alvo
 * @param inicio Ponteiro para a data de início
 * @param fim Ponteiro para a data de fim
 * 
 * @return 1 se a data alvo estiver entre as datas de início e fim, 0 caso contrário
 */
int esta_entre_datas(DataHora *alvo, DataHora *inicio, DataHora *fim);


/**
 * @brief Liberta a memória associada a uma estrutura DataHora.
 * 
 * @param dh Ponteiro para a estrutura DataHora a ser libertada
 * 
 * @return void
 */
void destroy_data_hora(DataHora *dh);


/**
 * @brief Cria uma cópia de uma estrutura DataHora.
 * 
 * @param src Ponteiro para a estrutura DataHora de origem
 * 
 * @return Ponteiro para a nova estrutura DataHora copiada
 */
DataHora* copy_data_hora (const DataHora *src);


/**
 * @brief Obtém a hora de uma estrutura DataHora.
 * 
 * @param dh Ponteiro para a estrutura DataHora
 * 
 * @return Hora no formato HHMM
 */
int get_hora(DataHora *dh);


/**
 * @brief Obtém a data de uma estrutura DataHora.
 * 
 * @param dh Ponteiro para a estrutura DataHora
 * 
 * @return Data no formato AAAAMMDD
 */
int get_data(DataHora *dh);

// falta documentar

void set_data(DataHora *dh, int data);

void set_hora(DataHora *dh, int hora);


/**
 * @brief Compara duas estruturas DataHora.
 * 
 * @param d1 Ponteiro para a primeira estrutura DataHora
 * @param d2 Ponteiro para a segunda estrutura DataHora
 * 
 * @return Valor negativo se d1 < d2, zero se d1 == d2, valor positivo se d1 > d2
 */
int comparar_data_hora(const DataHora *d1, const DataHora *d2);

#endif
