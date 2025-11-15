#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "voos.h"
#include "datas.h"
#include <string.h>

typedef struct voo {
    char *flight_id;         // identificador único do voo
    DataHora *departure;     // data e hora de partida estimada
    DataHora *actual_departure;  // data e hora de partida real
    DataHora *arrival;       // data e hora de chegada estimada
    DataHora *actual_arrival;    // data e hora de chegada real
    char *gate;              // porta de embarque
    char *status;            // estado: On Time, Delayed, Cancelled
    char *origin;            // código IATA do aeroporto de origem
    char *destination;       // código IATA do aeroporto de destino
    char *aircraft;          // identificador único da aeronave
    char *airline;           // nome da companhia aérea
    char *tracking_url;      // URL para rastreamento do voo
} Voo;

// ===========================================
// FUNÇÕES DE GESTÃO DE MEMÓRIA
// ===========================================

// FUNÇÃO CONSTRUTORA - Criar novo voo e alocar memória
Voo* create_voo(void) {
    Voo *v = malloc(sizeof(Voo));
    if (v == NULL) {
        return NULL;
    }
    
    // Inicializa todos os campos
    v->flight_id = NULL;
    v->departure = NULL;
    v->actual_departure = NULL;
    v->arrival = NULL;
    v->actual_arrival = NULL;
    v->gate = NULL;
    v->status = NULL;
    v->origin = NULL;
    v->destination = NULL;
    v->aircraft = NULL;
    v->airline = NULL;
    v->tracking_url = NULL;
    
    return v;
}

// FUNÇÃO INICIALIZADORA - Inicializar voo com valores
Voo* init_voo(const char *flight_id, DataHora *departure, DataHora *actual_departure,
              DataHora *arrival, DataHora *actual_arrival, const char *gate,
              const char *status, const char *origin, const char *destination,
              const char *aircraft, const char *airline, const char *tracking_url) {
    Voo *v = create_voo();
    if (v == NULL) return NULL;
    
    // Aloca e copia strings
    v->flight_id = flight_id ? strdup(flight_id) : NULL;
    v->gate = gate ? strdup(gate) : NULL;
    v->status = status ? strdup(status) : NULL;
    v->origin = origin ? strdup(origin) : NULL;
    v->destination = destination ? strdup(destination) : NULL;
    v->aircraft = aircraft ? strdup(aircraft) : NULL;
    v->airline = airline ? strdup(airline) : NULL;
    v->tracking_url = tracking_url ? strdup(tracking_url) : NULL;
    
    // Copia estruturas DataHora (assumindo que têm função de cópia)
    /* Não existe função de cópia para DataHora: atribuir os ponteiros diretamente
       e assumir transferência de propriedade (quem chama não deve libertá-los). */
    v->departure = departure;
    v->actual_departure = actual_departure;
    v->arrival = arrival;
    v->actual_arrival = actual_arrival;
    
    return v;
}

// FUNÇÃO DE COMPARAÇÃO - Comparar voos por ID
int compare_voos(const Voo *v1, const Voo *v2) {
    if (v1 == NULL && v2 == NULL) return 0;
    if (v1 == NULL) return -1;
    if (v2 == NULL) return 1;
    
    // Compara pelo ID do voo (chave única)
    char *id1 = get_flight_id(v1);
    char *id2 = get_flight_id(v2);
    
    if (id1 == NULL && id2 == NULL) return 0;
    if (id1 == NULL) return -1;
    if (id2 == NULL) return 1;
    
    return strcmp(id1, id2);
}


// FUNÇÃO DESTRUTORA - Libertar toda a memória
void destroy_voo(Voo *v) {
    if (v == NULL) return;
    
    // Liberta strings
    free(v->flight_id);
    free(v->gate);
    free(v->status);
    free(v->origin);
    free(v->destination);
    free(v->aircraft);
    free(v->airline);
    free(v->tracking_url);
    
    // Liberta estruturas DataHora
    if (v->departure) destroy_data_hora(v->departure);
    if (v->actual_departure) destroy_data_hora(v->actual_departure);
    if (v->arrival) destroy_data_hora(v->arrival);
    if (v->actual_arrival) destroy_data_hora(v->actual_arrival);
    
    // Liberta a estrutura principal
    free(v);
}

// ===========================================
// GETTERS - Funções para obter valores
// ===========================================

char* get_flight_id(const Voo *v) {
    return (v != NULL) ? v->flight_id : NULL;
}

DataHora* get_departure(const Voo *v) {
    return (v != NULL) ? v->departure : NULL;
}

DataHora* get_departure_time(const Voo *v) {
    return (v != NULL && v->departure != NULL) ? v->departure : NULL;
}

DataHora* get_departure_date(const Voo *v) {
    return (v != NULL && v->departure != NULL) ? v->departure : NULL;
}

DataHora* get_actual_departure(const Voo *v) {
    return (v != NULL) ? v->actual_departure : NULL;
}

DataHora* get_actual_departure_time(const Voo *v) {
    return (v != NULL && v->actual_departure != NULL) ? v->actual_departure : NULL;
}
DataHora* get_actual_departure_date(const Voo *v) {
    return (v != NULL && v->actual_departure != NULL) ? v->actual_departure : NULL;
}

DataHora* get_arrival(const Voo *v) {
    return (v != NULL) ? v->arrival : NULL;
}

DataHora* get_arrival_time(const Voo *v) {
    return (v != NULL && v->arrival != NULL) ? v->arrival : NULL;
}

DataHora* get_arrival_date(const Voo *v) {
    return (v != NULL && v->arrival != NULL) ? v->arrival : NULL;
}

DataHora* get_actual_arrival(const Voo *v) {
    return (v != NULL) ? v->actual_arrival : NULL;
}

DataHora* get_actual_arrival_time(const Voo *v) {
    return (v != NULL && v->actual_arrival != NULL) ? v->actual_arrival : NULL;
}

DataHora* get_actual_arrival_date(const Voo *v) {
    return (v != NULL && v->actual_arrival != NULL) ? v->actual_arrival : NULL;
}

char* get_gate(const Voo *v) {
    return (v != NULL) ? v->gate : NULL;
}

char* get_status(const Voo *v) {
    return (v != NULL) ? v->status : NULL;
}

char* get_origin(const Voo *v) {
    return (v != NULL) ? v->origin : NULL;
}

char* get_destination(const Voo *v) {
    return (v != NULL) ? v->destination : NULL;
}

char* get_aircraft(const Voo *v) {
    return (v != NULL) ? v->aircraft : NULL;
}

char* get_airline(const Voo *v) {
    return (v != NULL) ? v->airline : NULL;
}

char* get_tracking_url(const Voo *v) {
    return (v != NULL) ? v->tracking_url : NULL;
}

// ===========================================
// SETTERS - Funções para definir valores
// ===========================================

void set_flight_id(Voo *v, const char *flight_id) {
    if (v == NULL) return;
    free(v->flight_id);
    v->flight_id = flight_id ? strdup(flight_id) : NULL;
}

void set_departure(Voo *v, DataHora *departure) {
    if (v == NULL) return;
    if (v->departure) destroy_data_hora(v->departure);
    v->departure = departure ? copy_data_hora(departure) : NULL;
}

void set_actual_departure(Voo *v, DataHora *actual_departure) {
    if (v == NULL) return;
    if (v->actual_departure) destroy_data_hora(v->actual_departure);
    v->actual_departure = actual_departure ? copy_data_hora(actual_departure) : NULL;
}

void set_arrival(Voo *v, DataHora *arrival) {
    if (v == NULL) return;
    if (v->arrival) destroy_data_hora(v->arrival);
    v->arrival = arrival ? copy_data_hora(arrival) : NULL;
}

void set_actual_arrival(Voo *v, DataHora *actual_arrival) {
    if (v == NULL) return;
    if (v->actual_arrival) destroy_data_hora(v->actual_arrival);
    v->actual_arrival = actual_arrival ? copy_data_hora(actual_arrival) : NULL;
}

void set_gate(Voo *v, const char *gate) {
    if (v == NULL) return;
    free(v->gate);
    v->gate = gate ? strdup(gate) : NULL;
}

void set_status(Voo *v, const char *status) {
    if (v == NULL) return;
    free(v->status);
    v->status = status ? strdup(status) : NULL;
}

void set_origin(Voo *v, const char *origin) {
    if (v == NULL) return;
    free(v->origin);
    v->origin = origin ? strdup(origin) : NULL;
}

void set_destination(Voo *v, const char *destination) {
    if (v == NULL) return;
    free(v->destination);
    v->destination = destination ? strdup(destination) : NULL;
}

void set_aircraft(Voo *v, const char *aircraft) {
    if (v == NULL) return;
    free(v->aircraft);
    v->aircraft = aircraft ? strdup(aircraft) : NULL;
}

void set_airline(Voo *v, const char *airline) {
    if (v == NULL) return;
    free(v->airline);
    v->airline = airline ? strdup(airline) : NULL;
}

void set_tracking_url(Voo *v, const char *tracking_url) {
    if (v == NULL) return;
    free(v->tracking_url);
    v->tracking_url = tracking_url ? strdup(tracking_url) : NULL;
}
