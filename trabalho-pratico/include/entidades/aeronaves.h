#ifndef AERONAVES_H
#define AERONAVES_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Estrutura que representa uma aeronave com seus atributos principais.
 * 
 * - identifier:    Identificador único da aeronave (tail number)
 * - manufacturer:  Fabricante da aeronave
 * - model:         Modelo da aeronave
 * - year:          Ano de fabrico da aeronave
 * - capacity:      Capacidade máxima de passageiros
 * - range:         Alcance máximo em km
 * - num_voos:      Número de voos realizados pela aeronave
 *
 */
typedef struct aeronaves Aeronaves;


/**
 * @brief Esta função é responsável por criar uma nova instância de aeronave,alocando dinamicamente a memória necessária para armazenar os dados da estrutura.
 * 
 * @param void Não recebe parâmetros
 * 
 * @return Ponteiro para a aeronave criada, ou NULL em caso de falha na alocação
 */
Aeronaves* criar_aeronave(void);


/**
 * @brief Esta função inicializa uma aeronave com os dados fornecidos como parâmetros, alocando memória para a estrutura e copia os valores dos parâmetros para os campos correspondentes.
 * 
 * @param identifier Identificador da aeronave
 * @param manufacturer Fabricante da aeronave
 * @param model Modelo da aeronave
 * @param year Ano de fabrico da aeronave
 * @param capacity Capacidade da aeronave
 * @param range Alcance da aeronave
 * 
 * @return Ponteiro para a aeronave inicializada, ou NULL em caso de erro
 */
Aeronaves* init_aeronave(const char *identifier, const char *manufacturer,
                         const char *model, const char *year, const char *capacity, const char *range);


/**
 * @brief Liberta a memória associada a uma aeronave.
 * 
 * @param a Ponteiro para a aeronave a ser libertada
 * 
 * @return void 
 */
void destroy_aeronave(Aeronaves *a);


// GETTERS - Funções para obter valores


/**
 * @brief Obtém o identificador da aeronave.
 * 
 * @param a Ponteiro para a aeronave
 * 
 * @return Identificador da aeronave
 */
const char* get_identifier_aeronave(const Aeronaves *a);


/**
 * @brief Obtém o fabricante da aeronave.
 * 
 * @param a Ponteiro para a aeronave
 * 
 * @return Fabricante da aeronave
 */
const char* get_manufacturer_aeronave(const Aeronaves *a);


/**
 * @brief Obtém o modelo da aeronave.
 * 
 * @param a Ponteiro para a aeronave
 * 
 * @return Modelo da aeronave
 */
const char* get_model_aeronave(const Aeronaves *a);


/**
 * @brief Obtém o ano de fabrico da aeronave.
 * 
 * @param a Ponteiro para a aeronave
 * 
 * @return Ano de fabrico da aeronave
 */
const char* get_year_aeronave(const Aeronaves *a);


/**
 * @brief Obtém a capacidade da aeronave.
 * 
 * @param a Ponteiro para a aeronave
 * 
 * @return Capacidade da aeronave
 */
const char* get_capacity_aeronave(const Aeronaves *a);


/**
 * @brief Obtém o alcance da aeronave.
 * 
 * @param a Ponteiro para a aeronave
 * 
 * @return Alcance da aeronave
 */
const char* get_range_aeronave(const Aeronaves *a);


/**
 * @brief Obtém o número de voos da aeronave.
 * 
 * @param a Ponteiro para a aeronave
 * 
 * @return Número de voos da aeronave
 */
int get_num_voos_aeronave(const Aeronaves *a);


// SETTERS - Funções para definir valores

/**
 * @brief Define o identificador da aeronave.
 * 
 * @param a Ponteiro para a aeronave
 * 
 * @param identifier Novo identificador da aeronave
 */
void set_identifier_aeronave(Aeronaves *a, const char *identifier);


/**
 * @brief Define o fabricante da aeronave.
 * 
 * @param a Ponteiro para a aeronave
 * 
 * @param manufacturer Novo fabricante da aeronave
 */
void set_manufacturer_aeronave(Aeronaves *a, const char *manufacturer);


/**
 * @brief Define o modelo da aeronave.
 * 
 * @param a Ponteiro para a aeronave
 * 
 * @param model Novo modelo da aeronave
 */
void set_model_aeronave(Aeronaves *a, const char *model);


/**
 * @brief Define o ano de fabrico da aeronave.
 * 
 * @param a Ponteiro para a aeronave
 * 
 * @param year Novo ano de fabrico da aeronave
 */
void set_year_aeronave(Aeronaves *a, const char *year);


/**
 * @brief Define a capacidade da aeronave.
 * 
 * @param a Ponteiro para a aeronave
 * 
 * @param capacity Nova capacidade da aeronave
 */
void set_capacity_aeronave(Aeronaves *a, const char *capacity);


/**
 * @brief Define o alcance da aeronave.
 * 
 * @param a Ponteiro para a aeronave
 * 
 * @param range Novo alcance da aeronave
 */
void set_range_aeronave(Aeronaves *a, const char *range);


/**
 * @brief Define o número de voos da aeronave.
 * 
 * @param a Ponteiro para a aeronave
 * 
 * @param num_voos Novo número de voos da aeronave
 */
void set_num_voos_aeronave(Aeronaves *a, int num_voos);


#endif 


