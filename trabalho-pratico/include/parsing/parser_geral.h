#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser_aeronaves.h"
#include "parser_aeroportos.h"
#include "parser_voos.h"
#include "parser_reservas.h"
#include "parser_passageiros.h"
#include "parser_utils.h"
#include "gestor_aeroportos.h"
#include "gestor_aeronaves.h"
#include "gestor_voos.h"


/**
 * @brief Função genérica para processar ficheiros CSV, utilizando funções de parsing e adição específicas.
 * 
 * @param f Ponteiro para o ficheiro a ser processado
 * @param funcao_parser Função de parsing específica para o tipo de dados
 * @param funcao_add Função de adição específica para o gestor correspondente
 * @param gestor1 Ponteiro para o primeiro gestor (ex: gestor de aeroportos)
 * @param gestor2 Ponteiro para o segundo gestor (ex: gestor de aeronaves)
 * @param gestor3 Ponteiro para o terceiro gestor (ex: gestor de voos)
 * @param err_file Ponteiro para o ficheiro de erros onde linhas inválidas serão registradas
 * 
 * @return void
 */
void processar_ficheiro(FILE *f, FuncaoParser funcao_parser, FuncaoAddGestor funcao_add, void *gestor1, void *gestor2, void *gestor3, FILE *err_file);


/**
 * @brief Função de ação para adicionar um aeroporto ao gestor de aeroportos.
 * 
 * @param ptr Ponteiro para o aeroporto a ser adicionado
 * @param g_aero Ponteiro para o gestor de aeroportos
 * @param unused1 Ponteiro não utilizado
 * @param unused2 Ponteiro não utilizado
 * 
 * @return void
 */
void action_add_aeroporto(void *ptr, void* g_aero, void* unused1, void* unused2);


/**
 * @brief Função de ação para adicionar uma aeronave ao gestor de aeronaves.
 * 
 * @param ptr Ponteiro para a aeronave a ser adicionada
 * @param g_aeroN Ponteiro para o gestor de aeronaves
 * @param unused1 Ponteiro não utilizado
 * @param unused2 Ponteiro não utilizado
 * 
 * @return void
 */
void action_add_aeronave(void *ptr, void* g_aeroN, void* unused1, void* unused2);


/**
 * @brief Função de ação para adicionar um voo ao gestor de voos.
 * 
 * @param ptr Ponteiro para o voo a ser adicionado
 * @param array_voos Ponteiro para o gestor de voos baseado em array
 * @param hash_voos Ponteiro para o gestor de voos baseado em hash
 * @param unused Ponteiro não utilizado
 * 
 * @return void
 */
void action_add_voo(void *ptr, void* array_voos, void* hash_voos, void*unused);


/**
 * @brief Função de ação para adicionar um passageiro ao gestor de passageiros.
 * 
 * @param ptr Ponteiro para o passageiro a ser adicionado
 * @param unused1 Ponteiro não utilizado
 * @param unused2 Ponteiro não utilizado
 * @param unused3 Ponteiro não utilizado
 * 
 * @return void
 */
void action_add_passageiro(void *ptr, void* unused1, void* unused2, void* unused3);


/**
 * @brief Função de ação para adicionar uma reserva ao gestor de reservas.
 * 
 * @param ptr Ponteiro para a reserva a ser adicionada
 * @param g_res Ponteiro para o gestor de reservas
 * @param hash_voos Ponteiro para o gestor de voos baseado em hash
 * @param ga Ponteiro para o gestor de aeroportos
 *
 * @return void
 */
void action_add_reserva(void *ptr, void* g_res, void* hash_voos, void *ga);