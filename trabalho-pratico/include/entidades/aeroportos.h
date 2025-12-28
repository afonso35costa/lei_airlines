#ifndef AEROPORTOS_H
#define AEROPORTOS_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Estrutura que representa um aeroporto com seus atributos principais.
 * 
 * - code:          Código IATA do aeroporto (3 letras)
 * - name:          Nome do aeroporto
 * - city:          Cidade onde se localiza o aeroporto
 * - country:       País onde se localiza o aeroporto
 * - latitude:      Latitude da localização do aeroporto
 * - longitude:     Longitude da localização do aeroporto
 * - icao:          Código ICAO do aeroporto
 * - type:          Tipo de aeroporto
 * - departures:    Número de partidas do aeroporto
 * - dep_count:     Contador de partidas
 * - arr_count:     Contador de chegadas
 *
 */
typedef struct aeroportos Aeroportos;


/**
 * @brief Esta função é responsável por criar uma nova instância de aeroporto, alocando dinamicamente a memória necessária para armazenar os dados da estrutura.
 * 
 * @param void Não recebe parâmetros
 * 
 * @return Ponteiro para o aeroporto criado, ou NULL em caso de falha na alocação
 */
Aeroportos* create_aeroporto(void);


/**
 * @brief Esta função inicializa um aeroporto com os dados fornecidos como parâmetros, alocando memória para a estrutura e copia os valores dos parâmetros para os campos correspondentes.
 * 
 * @param code Código IATA do aeroporto
 * @param name Nome do aeroporto
 * @param city Cidade do aeroporto
 * @param country País do aeroporto
 * @param latitude Latitude do aeroporto
 * @param longitude Longitude do aeroporto
 * @param icao Código ICAO do aeroporto
 * @param type Tipo do aeroporto
 * 
 * @return Ponteiro para o aeroporto inicializado, ou NULL em caso de erro
 */
Aeroportos* init_aeroporto(const char *code, const char *name, const char *city,
                           const char *country, double latitude, double longitude,
                           const char *icao, const char *type);


/**
 * @brief Liberta a memória associada a um aeroporto.
 * 
 * @param a Ponteiro para o aeroporto a ser libertado
 * 
 * @return void 
 */
void destroy_aeroporto(Aeroportos *a);


// GETTERS - Funções para obter valores


/**
 * @brief Obtém o código IATA do aeroporto.
 * 
 * @param a Ponteiro para o aeroporto
 * 
 * @return Código IATA do aeroporto
 */
const char* get_code_aeroporto(const Aeroportos *a);


/**
 * @brief Obtém o nome do aeroporto.
 * 
 * @param a Ponteiro para o aeroporto
 * 
 * @return Nome do aeroporto
 */
const char* get_name_aeroporto(const Aeroportos *a);


/**
 * @brief Obtém a cidade do aeroporto.
 * 
 * @param a Ponteiro para o aeroporto
 * 
 * @return Cidade do aeroporto
 */
const char* get_city_aeroporto(const Aeroportos *a);


/**
 * @brief Obtém o país do aeroporto.
 * 
 * @param a Ponteiro para o aeroporto
 * 
 * @return País do aeroporto
 */
const char* get_country_aeroporto(const Aeroportos *a);


/**
 * @brief Obtém a latitude do aeroporto.
 * 
 * @param a Ponteiro para o aeroporto
 * 
 * @return Latitude do aeroporto
 */
double get_latitude_aeroporto(const Aeroportos *a);


/**
 * @brief Obtém a longitude do aeroporto.
 * 
 * @param a Ponteiro para o aeroporto
 * 
 * @return Longitude do aeroporto
 */
double get_longitude_aeroporto(const Aeroportos *a);


/**
 * @brief Obtém o código ICAO do aeroporto.
 * 
 * @param a Ponteiro para o aeroporto
 * 
 * @return Código ICAO do aeroporto
 */
const char* get_icao_aeroporto(const Aeroportos *a);


/**
 * @brief Obtém o tipo do aeroporto.
 * 
 * @param a Ponteiro para o aeroporto
 * 
 * @return Tipo do aeroporto
 */
const char* get_type_aeroporto(const Aeroportos *a);


/**
 * @brief Obtém o número de partidas do aeroporto.
 * 
 * @param a Ponteiro para o aeroporto
 * 
 * @return Número de partidas do aeroporto
 */
int get_departures_aeroporto(const Aeroportos *a);


/**
 * @brief Obtém o contador de partidas do aeroporto.
 * 
 * @param a Ponteiro para o aeroporto
 * 
 * @return Contador de partidas do aeroporto
 */
int get_dep_count_aeroporto(const Aeroportos *a);


/**
 * @brief Obtém o contador de chegadas do aeroporto.
 * 
 * @param a Ponteiro para o aeroporto
 * 
 * @return Contador de chegadas do aeroporto
 */
int get_arr_count_aeroporto(const Aeroportos *a);


// FALTA DOCUMENTAR


int get_nac_count_aeroporto(const Aeroportos *a);


// SETTERS - Funções para definir valores

/**
 * @brief Define o código IATA do aeroporto.
 * 
 * @param a Ponteiro para o aeroporto
 * 
 * @param code Novo código IATA do aeroporto
 */
void set_code_aeroporto(Aeroportos *a, const char *code);


/**
 * @brief Define o nome do aeroporto.
 * 
 * @param a Ponteiro para o aeroporto
 * 
 * @param name Novo nome do aeroporto
 */
void set_name_aeroporto(Aeroportos *a, const char *name);


/**
 * @brief Define a cidade do aeroporto.
 * 
 * @param a Ponteiro para o aeroporto
 * 
 * @param city Nova cidade do aeroporto
 */
void set_city_aeroporto(Aeroportos *a, const char *city);


/**
 * @brief Define o país do aeroporto.
 * 
 * @param a Ponteiro para o aeroporto
 * 
 * @param country Novo país do aeroporto
 */
void set_country_aeroporto(Aeroportos *a, const char *country);


/**
 * @brief Define a latitude do aeroporto.
 * 
 * @param a Ponteiro para o aeroporto
 * 
 * @param latitude Nova latitude do aeroporto
 */
void set_latitude_aeroporto(Aeroportos *a, double latitude);


/**
 * @brief Define a longitude do aeroporto.
 * 
 * @param a Ponteiro para o aeroporto
 * 
 * @param longitude Nova longitude do aeroporto
 */
void set_longitude_aeroporto(Aeroportos *a, double longitude);


/**
 * @brief Define o código ICAO do aeroporto.
 * 
 * @param a Ponteiro para o aeroporto
 * 
 * @param icao Novo código ICAO do aeroporto
 */
void set_icao_aeroporto(Aeroportos *a, const char *icao);


/**
 * @brief Define o tipo do aeroporto.
 * 
 * @param a Ponteiro para o aeroporto
 * 
 * @param type Novo tipo do aeroporto
 */
void set_type_aeroporto(Aeroportos *a, const char *type);


/**
 * @brief Define o número de partidas do aeroporto.
 * 
 * @param a Ponteiro para o aeroporto
 * 
 * @param departures Novo número de partidas do aeroporto
 */
void set_departures_aeroporto(Aeroportos *a, int departures);


/**
 * @brief Define o contador de partidas do aeroporto.
 * 
 * @param a Ponteiro para o aeroporto
 * 
 * @param dep_count Novo contador de partidas do aeroporto
 */
void set_dep_count_aeroporto(Aeroportos *a, int dep_count);


/**
 * @brief Define o contador de chegadas do aeroporto.
 * 
 * @param a Ponteiro para o aeroporto
 * 
 * @param arr_count Novo contador de chegadas do aeroporto
 */
void set_arr_count_aeroporto(Aeroportos *a, int arr_count);


// FALTA DOCUMENTAR

void set_nac_count_aeroporto(Aeroportos *a, int nac_count);


#endif