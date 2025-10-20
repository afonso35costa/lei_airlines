#ifndef VOOS_H
#define VOOS_H

#include <stddef.h>

/* O tipo Voo é opaco para o utilizador do header; a definição completa fica em voos.c */
typedef struct voo Voo;

/* Liberta todas as strings internas de um Voo (não liberta o struct) */
void voo_clear(Voo *v);

/* Liberta o struct e todo o seu conteúdo */
void voo_free(Voo *v);

/* Cria um novo Voo duplicando todas as strings passadas (cada parâmetro pode ser NULL).
   Retorna NULL em caso de falha de alocação. */
Voo *voo_create(const char *flight_id,
                const char *departure,
                const char *actual_departure,
                const char *arrival,
                const char *actual_arrival,
                const char *gate,
                const char *status,
                const char *origin,
                const char *destination,
                const char *aircraft,
                const char *airline,
                const char *tracking_url);

/* Clona (cópia profunda) um Voo. Retorna NULL em caso de falha. */
Voo *voo_clone(const Voo *src);

/* Setters: retornam 0 em sucesso, -1 em falha de alocação. */
int voo_set_flight_id(Voo *v, const char *s);
int voo_set_departure(Voo *v, const char *s);
int voo_set_actual_departure(Voo *v, const char *s);
int voo_set_arrival(Voo *v, const char *s);
int voo_set_actual_arrival(Voo *v, const char *s);
int voo_set_gate(Voo *v, const char *s);
int voo_set_status(Voo *v, const char *s);
int voo_set_origin(Voo *v, const char *s);
int voo_set_destination(Voo *v, const char *s);
int voo_set_aircraft(Voo *v, const char *s);
int voo_set_airline(Voo *v, const char *s);
int voo_set_tracking_url(Voo *v, const char *s);

/* Getters: retornam ponteiro para string interna (ou NULL se não existir).
   O caller não deve free() o ponteiro retornado; permanece propriedade do Voo. */
const char *voo_get_flight_id(const Voo *v);
const char *voo_get_departure(const Voo *v);
const char *voo_get_actual_departure(const Voo *v);
const char *voo_get_arrival(const Voo *v);
const char *voo_get_actual_arrival(const Voo *v);
const char *voo_get_gate(const Voo *v);
const char *voo_get_status(const Voo *v);
const char *voo_get_origin(const Voo *v);
const char *voo_get_destination(const Voo *v);
const char *voo_get_aircraft(const Voo *v);
const char *voo_get_airline(const Voo *v);
const char *voo_get_tracking_url(const Voo *v);


#endif