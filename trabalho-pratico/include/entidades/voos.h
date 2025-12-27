#ifndef VOOS_H
#define VOOS_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "datas.h"

/**
 * @brief Estrutura que representa um voo com seus atributos principais.
 * 
 * - flight_id:         Identificador único do voo
 * - departure:         Data e hora de partida programada
 * - actual_departure:  Data e hora de partida real
 * - arrival:           Data e hora de chegada programada
 * - actual_arrival:    Data e hora de chegada real
 * - gate:              Portão de embarque
 * - status:            Estado do voo (On Time, Delayed, Cancelled)
 * - origin:            Aeroporto de origem
 * - destination:       Aeroporto de destino
 * - aircraft:          Identificador da aeronave
 * - airline:           Companhia aérea
 * - tracking_url:      URL para rastreamento do voo
 * 
 *
 */
typedef struct voo Voo;


/**
 * @brief Esta função é responsável por criar uma nova instância de voo, alocando dinamicamente a memória necessária para armazenar os dados da estrutura.
 * 
 * @param void Não recebe parâmetros
 * 
 * @return Ponteiro para o voo criado, ou NULL em caso de falha na alocação
 */
Voo* create_voo(void);


/**
 * @brief Esta função inicializa um voo com os dados fornecidos como parâmetros, alocando memória para a estrutura e copia os valores dos parâmetros para os campos correspondentes.
 * 
 * @param flight_id Identificador do voo
 * @param departure Data e hora de partida programada
 * @param actual_departure Data e hora de partida real
 * @param arrival Data e hora de chegada programada
 * @param actual_arrival Data e hora de chegada real
 * @param gate Portão de embarque
 * @param status Estado do voo
 * @param origin Aeroporto de origem
 * @param destination Aeroporto de destino
 * @param aircraft Identificador da aeronave
 * @param airline Companhia aérea
 * 
 * @return Ponteiro para o voo inicializado, ou NULL em caso de erro
 */
Voo* init_voo(const char *flight_id, DataHora *departure, DataHora *actual_departure,
              DataHora *arrival, DataHora *actual_arrival, const char *gate,
              const char *status, const char *origin, const char *destination,
              const char *aircraft, const char *airline);


/**
 * @brief Compara dois voos.
 * 
 * @param v1 Ponteiro para o primeiro voo
 * @param v2 Ponteiro para o segundo voo
 * 
 * @return Resultado da comparação
 */
int compare_voos(const Voo *v1, const Voo *v2);


/**
 * @brief Liberta a memória associada a um voo.
 * 
 * @param v Ponteiro para o voo a ser libertado
 * 
 * @return void 
 */
void destroy_voo(Voo *v);


// GETTERS - Funções para obter valores


/**
 * @brief Obtém o identificador do voo.
 * 
 * @param v Ponteiro para o voo
 * 
 * @return Identificador do voo
 */
char* get_flight_id_voo(const Voo *v);


/**
 * @brief Obtém a data e hora de partida programada do voo.
 * 
 * @param v Ponteiro para o voo
 * 
 * @return Data e hora de partida programada do voo
 */
DataHora* get_departure_voo(const Voo *v);


/**
 * @brief Obtém a data e hora de partida real do voo.
 * 
 * @param v Ponteiro para o voo
 * 
 * @return Data e hora de partida real do voo
 */
DataHora* get_actual_departure_voo(const Voo *v);


/**
 * @brief Obtém a data e hora de chegada programada do voo.
 * 
 * @param v Ponteiro para o voo
 * 
 * @return Data e hora de chegada programada do voo
 */
DataHora* get_arrival_voo(const Voo *v);


/**
 * @brief Obtém a data e hora de chegada real do voo.
 * 
 * @param v Ponteiro para o voo
 * 
 * @return Data e hora de chegada real do voo
 */
DataHora* get_actual_arrival_voo(const Voo *v);


/**
 * @brief Obtém o portão de embarque do voo.
 * 
 * @param v Ponteiro para o voo
 * 
 * @return Portão de embarque do voo
 */
char* get_gate_voo(const Voo *v);


/**
 * @brief Obtém o estado do voo.
 * 
 * @param v Ponteiro para o voo
 * 
 * @return Estado do voo
 */
char* get_status_voo(const Voo *v);


/**
 * @brief Obtém o aeroporto de origem do voo.
 * 
 * @param v Ponteiro para o voo
 * 
 * @return Aeroporto de origem do voo
 */
char* get_origin_voo(const Voo *v);


/**
 * @brief Obtém o aeroporto de destino do voo.
 * 
 * @param v Ponteiro para o voo
 * 
 * @return Aeroporto de destino do voo
 */
char* get_destination_voo(const Voo *v);


/**
 * @brief Obtém o identificador da aeronave do voo.
 * 
 * @param v Ponteiro para o voo
 * 
 * @return Identificador da aeronave do voo
 */
char* get_aircraft_voo(const Voo *v);


/**
 * @brief Obtém a companhia aérea do voo.
 * 
 * @param v Ponteiro para o voo
 * 
 * @return Companhia aérea do voo
 */
char* get_airline_voo(const Voo *v);


// SETTERS - Funções para definir valores

/**
 * @brief Define o identificador do voo.
 * 
 * @param v Ponteiro para o voo
 * 
 * @param flight_id Novo identificador do voo
 */
void set_flight_id_voo(Voo *v, const char *flight_id);


/**
 * @brief Define a data e hora de partida programada do voo.
 * 
 * @param v Ponteiro para o voo
 * 
 * @param departure Nova data e hora de partida programada do voo
 */
void set_departure_voo(Voo *v, DataHora *departure);


/**
 * @brief Define a data e hora de partida real do voo.
 * 
 * @param v Ponteiro para o voo
 * 
 * @param actual_departure Nova data e hora de partida real do voo
 */
void set_actual_departure_voo(Voo *v, DataHora *actual_departure);


/**
 * @brief Define a data e hora de chegada programada do voo.
 * 
 * @param v Ponteiro para o voo
 * 
 * @param arrival Nova data e hora de chegada programada do voo
 */
void set_arrival_voo(Voo *v, DataHora *arrival);


/**
 * @brief Define a data e hora de chegada real do voo.
 * 
 * @param v Ponteiro para o voo
 * 
 * @param actual_arrival Nova data e hora de chegada real do voo
 */
void set_actual_arrival_voo(Voo *v, DataHora *actual_arrival);


/**
 * @brief Define o portão de embarque do voo.
 * 
 * @param v Ponteiro para o voo
 * 
 * @param gate Novo portão de embarque do voo
 */
void set_gate_voo(Voo *v, const char *gate);


/**
 * @brief Define o estado do voo.
 * 
 * @param v Ponteiro para o voo
 * 
 * @param status Novo estado do voo
 */
void set_status_voo(Voo *v, const char *status);


/**
 * @brief Define o aeroporto de origem do voo.
 * 
 * @param v Ponteiro para o voo
 * 
 * @param origin Novo aeroporto de origem do voo
 */
void set_origin_voo(Voo *v, const char *origin);


/**
 * @brief Define o aeroporto de destino do voo.
 * 
 * @param v Ponteiro para o voo
 * 
 * @param destination Novo aeroporto de destino do voo
 */
void set_destination_voo(Voo *v, const char *destination);


/**
 * @brief Define o identificador da aeronave do voo.
 * 
 * @param v Ponteiro para o voo
 * 
 * @param aircraft Novo identificador da aeronave do voo
 */
void set_aircraft_voo(Voo *v, const char *aircraft);


/**
 * @brief Define a companhia aérea do voo.
 * 
 * @param v Ponteiro para o voo
 * 
 * @param airline Nova companhia aérea do voo
 */
void set_airline_voo(Voo *v, const char *airline);


#endif