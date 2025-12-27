#ifndef QUERIES_H
#define QUERIES_H

#include <stdio.h>
#include "gestor_aeroportos.h"
#include "gestor_aeronaves.h"
#include "gestor_voos.h"
#include "gestor_reservas.h"
#include "datas.h"  // Para DataHora

/**
 * @brief Função que percorre as reservas e atualiza as contagens de chegadas e partidas nos aeroportos correspondentes.
 * 
 * @param r Ponteiro para a reserva a ser verificada
 * @param hash_voos Ponteiro para o gestor de voos (hash table)
 * @param ga Ponteiro para o gestor de aeroportos
 * 
 * @return void 
 */
void checka_reservas(Reservas *r, HashVoos *hash_voos, GestorAeroportos *ga);


/**
 * @brief Q1: Informação de um aeroporto dado o seu código IATA, ou NULL se não existir. 
 * 
 * @param ga Ponteiro para o gestor de aeroportos
 * @param code Código IATA do aeroporto a ser consultado
 * 
 * @return Ponteiro para o aeroporto correspondente ao código, ou NULL se não existir
 */
Aeroportos *query1(GestorAeroportos *ga, const char *code);

/**
 * @brief Estrutura auxiliar para estatísticas de aeronaves.
 * 
 * - identifier:    Identificador da aeronave
 * - manufacturer:  Fabricante da aeronave
 * - model:         Modelo da aeronave
 * - flight_count:  Número de voos realizados pela aeronave
 */
typedef struct aircraft_stats AircraftStats;


/**
 * @brief Função que percorre todos os voos e conta voos por aeronave
 * 
 * @param gv Ponteiro para o gestor de voos (array)
 * @param ga Ponteiro para o gestor de aeronaves
 * 
 * @return void 
 */
void percorre_voos_aeronaves(ArrayVoos *gv, GestorAeronaves *ga);


/**
 * @brief Função de comparação para ordenar aeronaves por número de voos realizados (decrescente) e por identificador (crescente) em caso de empate.
 * 
 * @param a Ponteiro para a primeira aeronave, 
 * @param b Ponteiro para a segunda aeronave
 * 
 * @return Resultado da comparação: negativo se a < b, zero se a == b, positivo se a > b
 */
gint compare_aeronaves(gconstpointer a, gconstpointer b);


/**
 * @brief Função que ordena as aeronaves com base no número de voos realizados.
 * 
 * @param ga Ponteiro para o gestor de aeronaves
 * 
 * @return Lista ordenada de aeronaves
 */
GList* ordena_aeronaves (GestorAeronaves *ga);


/**
 * @brief Q2: Top N aeronaves com mais voos realizados, opcionalmente filtrado por fabricante.
 * 
 * @param stats_list Lista de estatísticas de aeronaves
 * @param N Número de aeronaves a retornar
 * @param manufacturer_filter Filtro opcional por fabricante (pode ser NULL ou string vazia para não filtrar)
 * 
 * @return Array de ponteiros para as N aeronaves com mais voos realizados
 */
Aeronaves **query2(GList *stats_list, int N, const char *manufacturer_filter);


/**
 * @brief Função que percorre todos os voos e conta partidas por aeroporto entre duas datas.
 * 
 * @param gv Ponteiro para o gestor de voos (array)
 * @param ga Ponteiro para o gestor de aeroportos
 * @param start_date Data de início do intervalo (formato "YYYY-MM-DD")
 * @param end_date Data de fim do intervalo (formato "YYYY-MM-DD")
 * 
 * @return void 
 */
void percorre_voos_aeroportos(ArrayVoos *gv, GestorAeroportos *ga, char* start_date, char* end_date);


/**
 * @brief Q3: Aeroporto com mais partidas entre duas datas.
 * 
 * @param ga Ponteiro para o gestor de aeroportos
 * 
 * @return Ponteiro para o aeroporto com mais partidas
 */
Aeroportos *query3(GestorAeroportos *ga);


/** 
 * @brief Estrutura auxiliar para armazenar informações de tempo de atraso por companhia aérea.
 * 
 * - hash: Hash table que mapeia companhias aéreas para ponteiros de Time
 */
typedef struct hash_time HashTime;


/**
 * @brief Estrutura que representa o tempo total de atraso e o número de voos atrasados para uma companhia aérea.
 * 
 * - delayed_count: Número de voos atrasados
 * - time: Tempo total de atraso em minutos
 * - airline: Identificador da companhia aérea
 */
typedef struct time Time;


/**
 * @brief Obtém o número de voos atrasados para uma companhia aérea.
 * 
 * @param t Ponteiro para a estrutura Time
 * 
 * @return Número de voos atrasados
 */
int get_time_delayed_count(Time *t);


/**
 * @brief Obtém o tempo total de atraso para uma companhia aérea.
 * 
 * @param t Ponteiro para a estrutura Time
 * 
 * @return Tempo total de atraso em minutos
 */
int get_time_total(Time *t);

/**
 * @brief Obtém o identificador da companhia aérea.
 * 
 * @param t Ponteiro para a estrutura Time
 * 
 * @return Identificador da companhia aérea
 */
char *get_time_airline(Time *t);


/**
 * @brief Liberta a memória associada a uma estrutura Time.
 * 
 * @param t Ponteiro para a estrutura Time a ser libertada
 * 
 * @return void
 */
void free_time(Time *t);


/**
 * @brief Cria uma nova instância de HashTime.
 * 
 * @param void Não recebe parâmetros
 * 
 * @return Ponteiro para a nova instância de HashTime
 */
HashTime *hash_time_create(void);


/**
 * @brief Função que percorre todos os voos e conta o tempo total de atraso e o número de voos atrasados por companhia aérea.
 * 
 * @param voos Ponteiro para o array de voos
 * 
 * @return Ponteiro para a estrutura HashTime com os resultados
 */
HashTime *conta_tempo(ArrayVoos *voos);


/**
 * @brief Função que arredonda um número para três casas decimais.
 * 
 * @param x Número a ser arredondado
 * 
 * @return Número arredondado para três casas decimais
 */
double round3(double x);


/**
 * @brief Função de comparação para ordenar companhias aéreas por tempo médio de atraso (decrescente) e por identificador (crescente) em caso de empate.
 * 
 * @param a Ponteiro para a primeira estrutura Time
 * @param b Ponteiro para a segunda estrutura Time
 * 
 * @return Resultado da comparação: negativo se a < b, zero se a == b, positivo se a > b
 */
gint compara_tempos(gconstpointer a, gconstpointer b);


/**
 * @brief Função que converte a HashTime em uma lista ordenada por tempo médio de atraso.
 * 
 * @param hash Ponteiro para a estrutura HashTime
 * 
 * @return Lista ordenada de ponteiros para Time
 */
GList *ordena_tempo_medio (HashTime *hash);

/**
 * @brief Q5: Top N companhias aéreas com maior tempo médio de atraso.
 * 
 * @param tempo_medio Lista de tempos médios de atraso por companhia aérea
 * @param N Número de companhias aéreas a retornar
 * 
 * @return Ponteiro para a estrutura
 */
Time **query5(GList *tempo_medio, int N);

#endif