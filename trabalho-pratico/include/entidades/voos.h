#ifndef VOOS_H
#define VOOS_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "datas.h"


/* O tipo Voo é opaco para o utilizador do header; a definição completa fica em voos.c */
typedef struct voo Voo;

/* Cria um novo Voo duplicando todas as strings passadas (cada parâmetro pode ser NULL).
   Retorna NULL em caso de falha de alocação. */
Voo* create_voo(void);

/* Inicializa um Voo com os valores fornecidos (cada parâmetro pode ser NULL).
   Retorna NULL em caso de falha de alocação. */
Voo* init_voo(const char *flight_id, DataHora *departure, DataHora *actual_departure,
              DataHora *arrival, DataHora *actual_arrival, const char *gate,
              const char *status, const char *origin, const char *destination,
              const char *aircraft, const char *airline);

/* Compara voos */
int compare_voos(const Voo *v1, const Voo *v2);

/* Funcao que destroi voo */
void destroy_voo(Voo *v);

/* Getters: retornam ponteiro para string interna (ou NULL se não existir). */
char* get_flight_id_voo(const Voo *v);
DataHora* get_departure_voo(const Voo *v);
DataHora* get_actual_departure_voo(const Voo *v);
DataHora* get_arrival_voo(const Voo *v);
DataHora* get_actual_arrival_voo(const Voo *v);

char* get_gate_voo(const Voo *v);
char* get_status_voo(const Voo *v);
char* get_origin_voo(const Voo *v);
char* get_destination_voo(const Voo *v);
char* get_aircraft_voo(const Voo *v);
char* get_airline_voo(const Voo *v);

/* Setters */
void set_flight_id_voo(Voo *v, const char *flight_id);
void set_departure_voo(Voo *v, DataHora *departure);
void set_actual_departure_voo(Voo *v, DataHora *actual_departure);
void set_arrival_voo(Voo *v, DataHora *arrival);
void set_actual_arrival_voo(Voo *v, DataHora *actual_arrival);
void set_gate_voo(Voo *v, const char *gate);
void set_status_voo(Voo *v, const char *status);
void set_origin_voo(Voo *v, const char *origin);
void set_destination_voo(Voo *v, const char *destination);
void set_aircraft_voo(Voo *v, const char *aircraft);
void set_airline_voo(Voo *v, const char *airline);



#endif