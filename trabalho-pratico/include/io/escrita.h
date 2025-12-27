#ifndef ESCRITA_H
#define ESCRITA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queries.h"
#include "aeroportos.h"
#include "aeronaves.h"

/**
 * @brief Define um tipo de função para escrever objetos em ficheiros.
 * 
 * @param objeto Ponteiro para o objeto a ser escrito
 * @param out Ponteiro para o ficheiro de saída
 * 
 * @return void
 */
typedef void (*FuncaoEscreve)(void *objeto, FILE *out);  


/**
 * @brief Função que abre ficheiros para escrita
 * 
 * @param path_filename Caminho e nome do ficheiro a ser aberto
 * 
 * @return Ponteiro para o ficheiro aberto
 */
FILE* abrir_ficheiro_escrita(const char* path_filename);


/**
 * @brief Função que escreve aeroporto em ficheiro
 * 
 * @param a Ponteiro para o aeroporto a ser escrito
 * @param out Ponteiro para o ficheiro de saída
 * @param qtype Tipo de query (formato de saída)
 * 
 * @return void
 */
void escreve_aeroporto1 (Aeroportos *a, FILE *out, char* qtype);


/**
 * @brief Função que escreve array de aeronaves em ficheiro
 * 
 * @param a Array de ponteiros para aeronaves
 * @param num_aeronaves Número de aeronaves no array
 * @param out Ponteiro para o ficheiro de saída
 * @param qtype Tipo de query (formato de saída)
 * 
 * @return void
 */
void escreve_aeronaves (Aeronaves **a, int num_aeronaves, FILE *out, char* qtype);


/**
 * @brief Função que escreve aeroporto e num_departures em ficheiro
 * 
 * @param a Ponteiro para o aeroporto a ser escrito
 * @param out Ponteiro para o ficheiro de saída
 * @param qtype Tipo de query (formato de saída)
 * 
 * @return void 
 */
void escreve_aeroporto3 (Aeroportos *a, FILE *out, char* qtype);


/**
 * @brief Função que escreve tempos médios de atraso por companhia aérea em ficheiro
 * 
 * @param time Array de ponteiros para estruturas Time
 * @param num_companhias Número de companhias aéreas
 * @param out Ponteiro para o ficheiro de saída
 * @param q_type Tipo de query (formato de saída)
 * 
 * @return void
 */
void escreve_tempos5 (Time **time, int num_companhias, FILE *out, char *q_type);

#endif