#ifndef VOOS_H
#define VOOS_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "datas.h"


/* O tipo Voo é opaco para o utilizador do header; a definição completa fica em voos.c */
typedef struct voo Voo;

/* Liberta todas as strings internas de um Voo (não liberta o struct) */
void voo_clear(Voo *v);

/* Liberta o struct e todo o seu conteúdo */
void voo_free(Voo *v);

/* Cria um novo Voo duplicando todas as strings passadas (cada parâmetro pode ser NULL).
   Retorna NULL em caso de falha de alocação. */
Voo* create_voo(void);

/* Inicializa um Voo com os valores fornecidos (cada parâmetro pode ser NULL).
   Retorna NULL em caso de falha de alocação. */
Voo* init_voo(const char *flight_id, DataHora *departure, DataHora *actual_departure,
              DataHora *arrival, DataHora *actual_arrival, const char *gate,
              const char *status, const char *origin, const char *destination,
              const char *aircraft, const char *airline, const char *tracking_url);

/* Compara voos */
int compare_voos(const Voo *v1, const Voo *v2);

/* Funcao que imprime voos */
void print_voo(const Voo *v);

/* Funcao que destroi voo */
void destroy_voo(Voo *v);

/* Getters: retornam ponteiro para string interna (ou NULL se não existir). */
char* get_flight_id(const Voo *v);
DataHora* get_departure(const Voo *v);
DataHora* get_actual_departure(const Voo *v);
DataHora* get_arrival(const Voo *v);
DataHora* get_actual_arrival(const Voo *v);
char* get_gate(const Voo *v);
char* get_status(const Voo *v);
char* get_origin(const Voo *v);
char* get_destination(const Voo *v);
char* get_aircraft(const Voo *v);
char* get_airline(const Voo *v);
char* get_tracking_url(const Voo *v);

/* Setters */
void set_flight_id(Voo *v, const char *flight_id);
void set_departure(Voo *v, DataHora *departure);
void set_actual_departure(Voo *v, DataHora *actual_departure);
void set_arrival(Voo *v, DataHora *arrival);
void set_actual_arrival(Voo *v, DataHora *actual_arrival);
void set_gate(Voo *v, const char *gate);
void set_status(Voo *v, const char *status);
void set_origin(Voo *v, const char *origin);
void set_destination(Voo *v, const char *destination);
void set_aircraft(Voo *v, const char *aircraft);
void set_airline(Voo *v, const char *airline);
void set_tracking_url(Voo *v, const char *tracking_url);



#endif