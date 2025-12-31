#ifndef RESERVAS_H
#define RESERVAS_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Estrutura que representa uma reserva com seus atributos principais.
 * 
 * - reservation_id:    Identificador único da reserva
 * - flight_ids:        Array de identificadores de voos
 * - document_number:   Número do documento do passageiro
 * - seat:              Lugar reservado
 * - price:             Preço da reserva
 * - extra_luggage:     Indica se tem bagagem extra (True se tiver, False caso contrário)
 * - priority_boarding: Indica se tem embarque prioritário (True se tiver, False caso contrário)
 *
 */
typedef struct reservas Reservas;


/**
 * @brief Esta função é responsável por criar uma nova instância de reserva, alocando dinamicamente a memória necessária para armazenar os dados da estrutura.
 * 
 * @param void Não recebe parâmetros
 * 
 * @return Ponteiro para a reserva criada, ou NULL em caso de falha na alocação
 */
Reservas* create_reserva(void);


/**
 * @brief Esta função inicializa uma reserva com os dados fornecidos como parâmetros, alocando memória para a estrutura e copia os valores dos parâmetros para os campos correspondentes.
 * 
 * @param reservation_id Identificador da reserva
 * @param flight_ids Array de identificadores de voos
 * @param document_number Número do documento do passageiro
 * @param seat Lugar reservado
 * @param price Preço da reserva
 * @param extra_luggage Indica se tem bagagem extra
 * @param priority_boarding Indica se tem embarque prioritário
 * 
 * @return Ponteiro para a reserva inicializada, ou NULL em caso de erro
 */
Reservas* init_reserva(const char *reservation_id, char **flight_ids, 
                      const char *document_number);


/**
 * @brief Compara duas reservas por ID.
 * 
 * @param r1 Ponteiro para a primeira reserva
 * @param r2 Ponteiro para a segunda reserva
 * 
 * @return Resultado da comparação
 */
int compare_reservas(const Reservas *r1, const Reservas *r2);


/**
 * @brief Liberta a memória associada a uma reserva.
 * 
 * @param r Ponteiro para a reserva a ser libertada
 * 
 * @return void 
 */
void destroy_reserva(Reservas *r);


// GETTERS - Funções para obter valores


/**
 * @brief Obtém o identificador da reserva.
 * 
 * @param r Ponteiro para a reserva
 * 
 * @return Identificador da reserva
 */
char* get_reservation_id_reservas(const Reservas *r);


/**
 * @brief Obtém os identificadores dos voos da reserva.
 * 
 * @param r Ponteiro para a reserva
 * 
 * @return Array de identificadores dos voos da reserva
 */
char** get_flight_ids_reservas(const Reservas *r);


/**
 * @brief Obtém o número de voos da reserva.
 * 
 * @param r Ponteiro para a reserva
 * 
 * @return Número de voos da reserva
 */
int get_num_flights_reserva(const Reservas *r);


/**
 * @brief Obtém o número do documento do passageiro da reserva.
 * 
 * @param r Ponteiro para a reserva
 * 
 * @return Número do documento do passageiro da reserva
 */
char* get_document_number_reservas(const Reservas *r);


/**
 * @brief Obtém o assento da reserva.
 * 
 * @param r Ponteiro para a reserva
 * 
 * @return Assento da reserva
 */
char* get_seat_reservas(const Reservas *r);


/**
 * @brief Obtém o preço da reserva.
 * 
 * @param r Ponteiro para a reserva
 * 
 * @return Preço da reserva
 */
double get_price_reservas(const Reservas *r);


/**
 * @brief Obtém o estado da bagagem extra da reserva.
 * 
 * @param r Ponteiro para a reserva
 * 
 * @return true se tem bagagem extra, false caso contrário
 */
bool get_extra_luggage_reservas(const Reservas *r);


/**
 * @brief Obtém o estado do embarque prioritário da reserva.
 * 
 * @param r Ponteiro para a reserva
 * 
 * @return true se tem embarque prioritário, false caso contrário
 */
bool get_priority_boarding_reservas(const Reservas *r);


// SETTERS - Funções para definir valores

/**
 * @brief Define o identificador da reserva.
 * 
 * @param r Ponteiro para a reserva
 * 
 * @param id Novo identificador da reserva
 */
void set_reservation_id_reservas(Reservas *r, const char *id);


/**
 * @brief Define os identificadores dos voos da reserva.
 * 
 * @param r Ponteiro para a reserva
 * 
 * @param flight_ids Novos identificadores dos voos da reserva
 */
void set_flight_ids_reservas(Reservas *r, char **flight_ids);


/**
 * @brief Define o número do documento do passageiro da reserva.
 * 
 * @param r Ponteiro para a reserva
 * 
 * @param doc Novo número do documento do passageiro da reserva
 */
void set_document_number_reservas(Reservas *r, const char *doc);


/**
 * @brief Define o assento da reserva.
 * 
 * @param r Ponteiro para a reserva
 * 
 * @param seat Novo assento da reserva
 */
void set_seat_reservas(Reservas *r, const char *seat);


/**
 * @brief Define o preço da reserva.
 * 
 * @param r Ponteiro para a reserva
 * 
 * @param price Novo preço da reserva
 */
void set_price_reservas(Reservas *r, double price);


/**
 * @brief Define o estado da bagagem extra da reserva.
 * 
 * @param r Ponteiro para a reserva
 * 
 * @param extra Novo estado da bagagem extra da reserva
 */
void set_extra_luggage_reservas(Reservas *r, bool extra);


/**
 * @brief Define o estado do embarque prioritário da reserva.
 * 
 * @param r Ponteiro para a reserva
 * 
 * @param priority Novo estado do embarque prioritário da reserva
 */
void set_priority_boarding(Reservas *r, bool priority);


#endif