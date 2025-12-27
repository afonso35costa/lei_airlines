#ifndef PASSAGEIROS_H
#define PASSAGEIROS_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Estrutura que representa um passageiro com seus atributos principais.
 * 
 * - document_number:   Número do documento de identificação
 * - first_name:        Primeiro nome do passageiro
 * - last_name:         Último nome do passageiro
 * - dob:               Data de nascimento
 * - nationality:       Nacionalidade do passageiro
 * - gender:            Género do passageiro
 * - email:             Email do passageiro
 * - phone:             Telefone do passageiro
 * - address:           Morada do passageiro
 * - photo:             Caminho para a foto do passageiro
 *
 */
typedef struct passageiros Passageiros;


/**
 * @brief Esta função é responsável por criar uma nova instância de passageiro, alocando dinamicamente a memória necessária para armazenar os dados da estrutura.
 * 
 * @param void Não recebe parâmetros
 * 
 * @return Ponteiro para o passageiro criado, ou NULL em caso de falha na alocação
 */
Passageiros* create_passageiro(void);


/**
 * @brief Esta função inicializa um passageiro com os dados fornecidos como parâmetros, alocando memória para a estrutura e copia os valores dos parâmetros para os campos correspondentes.
 * 
 * @param document_number Número do documento de identificação
 * @param first_name Primeiro nome do passageiro
 * @param last_name Último nome do passageiro
 * @param dob Data de nascimento
 * @param nationality Nacionalidade do passageiro
 * @param gender Género do passageiro
 * @param email Email do passageiro
 * @param phone Telefone do passageiro
 * @param address Morada do passageiro
 * @param photo Caminho para a foto do passageiro
 * 
 * @return Ponteiro para o passageiro inicializado, ou NULL em caso de erro
 */
Passageiros *init_passageiro(const char *document_number, const char *first_name, const char *last_name,
                             const char *dob, const char *nationality, const char *gender,
                             const char *email, const char *phone, const char *address, const char *photo);


/**
 * @brief Compara dois passageiros.
 * 
 * @param p1 Ponteiro para o primeiro passageiro
 * @param p2 Ponteiro para o segundo passageiro
 * 
 * @return Resultado da comparação
 */
int compare_passageiros(const Passageiros *p1, const Passageiros *p2);


/**
 * @brief Liberta a memória associada a um passageiro.
 * 
 * @param p Ponteiro para o passageiro a ser libertado
 * 
 * @return void 
 */
void destroy_passageiro(Passageiros *p);


// GETTERS - Funções para obter valores


/**
 * @brief Obtém o número do documento do passageiro.
 * 
 * @param p Ponteiro para o passageiro
 * 
 * @return Número do documento do passageiro
 */
char* get_document_number_passageiros(const Passageiros *p);


/**
 * @brief Obtém o primeiro nome do passageiro.
 * 
 * @param p Ponteiro para o passageiro
 * 
 * @return Primeiro nome do passageiro
 */
char* get_first_name_passageiros(const Passageiros *p);


/**
 * @brief Obtém o último nome do passageiro.
 * 
 * @param p Ponteiro para o passageiro
 * 
 * @return Último nome do passageiro
 */
char* get_last_name_passageiros(const Passageiros *p);


/**
 * @brief Obtém a data de nascimento do passageiro.
 * 
 * @param p Ponteiro para o passageiro
 * 
 * @return Data de nascimento do passageiro
 */
char* get_dob_passageiros(const Passageiros *p);


/**
 * @brief Obtém a nacionalidade do passageiro.
 * 
 * @param p Ponteiro para o passageiro
 * 
 * @return Nacionalidade do passageiro
 */
char* get_nationality_passageiros(const Passageiros *p);


/**
 * @brief Obtém o género do passageiro.
 * 
 * @param p Ponteiro para o passageiro
 * 
 * @return Género do passageiro
 */
char* get_gender_passageiros(const Passageiros *p);


/**
 * @brief Obtém o email do passageiro.
 * 
 * @param p Ponteiro para o passageiro
 * 
 * @return Email do passageiro
 */
char* get_email_passageiros(const Passageiros *p);


/**
 * @brief Obtém o telefone do passageiro.
 * 
 * @param p Ponteiro para o passageiro
 * 
 * @return Telefone do passageiro
 */
char* get_phone_passageiros(const Passageiros *p);


/**
 * @brief Obtém a morada do passageiro.
 * 
 * @param p Ponteiro para o passageiro
 * 
 * @return Morada do passageiro
 */
char* get_address_passageiros(const Passageiros *p);


/**
 * @brief Obtém o caminho da foto do passageiro.
 * 
 * @param p Ponteiro para o passageiro
 * 
 * @return Caminho da foto do passageiro
 */
char* get_photo_passageiros(const Passageiros *p);


// SETTERS - Funções para definir valores

/**
 * @brief Define o número do documento do passageiro.
 * 
 * @param p Ponteiro para o passageiro
 * 
 * @param doc Novo número do documento do passageiro
 */
void set_document_number_passageiros(Passageiros *p, const char *doc);


/**
 * @brief Define o primeiro nome do passageiro.
 * 
 * @param p Ponteiro para o passageiro
 * 
 * @param name Novo primeiro nome do passageiro
 */
void set_first_name_passageiros(Passageiros *p, const char *name);


/**
 * @brief Define o último nome do passageiro.
 * 
 * @param p Ponteiro para o passageiro
 * 
 * @param name Novo último nome do passageiro
 */
void set_last_name_passageiros(Passageiros *p, const char *name);


/**
 * @brief Define a data de nascimento do passageiro.
 * 
 * @param p Ponteiro para o passageiro
 * 
 * @param birth Nova data de nascimento do passageiro
 */
void set_dob_passageiros(Passageiros *p, const char *birth);


/**
 * @brief Define a nacionalidade do passageiro.
 * 
 * @param p Ponteiro para o passageiro
 * 
 * @param nat Nova nacionalidade do passageiro
 */
void set_nationality_passageiros(Passageiros *p, const char *nat);


/**
 * @brief Define o género do passageiro.
 * 
 * @param p Ponteiro para o passageiro
 * 
 * @param gen Novo género do passageiro
 */
void set_gender_passageiros(Passageiros *p, const char *gen);


/**
 * @brief Define o email do passageiro.
 * 
 * @param p Ponteiro para o passageiro
 * 
 * @param mail Novo email do passageiro
 */
void set_email_passageiros(Passageiros *p, const char *mail);


/**
 * @brief Define o telefone do passageiro.
 * 
 * @param p Ponteiro para o passageiro
 * 
 * @param tel Novo telefone do passageiro
 */
void set_phone_passageiros(Passageiros *p, const char *tel);


/**
 * @brief Define a morada do passageiro.
 * 
 * @param p Ponteiro para o passageiro
 * 
 * @param addr Nova morada do passageiro
 */
void set_address_passageiros(Passageiros *p, const char *addr);


/**
 * @brief Define o caminho da foto do passageiro.
 * 
 * @param p Ponteiro para o passageiro
 * 
 * @param pic Novo caminho da foto do passageiro
 */
void set_photo_passageiros(Passageiros *p, const char *pic);


#endif