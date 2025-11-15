#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "validacao_voos.h"
#include "voos.h"
#include "datas.h"
#include "validacao_aeroportos.h"

// Funções de validação individual

int validar_flight_id(const char *flight_id) {
    if (!flight_id || strlen(flight_id) != 7) return 0;
    for (int i = 0; i < 2; i++) {
        if (!isupper(flight_id[i])) return 0;
    }

    for (int i = 2; i < 7; i++) {
        if (!isdigit(flight_id[i])) return 0;
    }

    return 1;
}

int validar_departure(const char *departure_date, const char *departure_time) {
    if (!validar_data(departure_date)) return 0;
    if (!validar_hora(departure_time)) return 0;
    return 1;
}

int validar_actual_departure(const char *actual_departure_date, const char *actual_departure_time) {
    if (!validar_data(actual_departure_date)) return 0;
    if (!validar_hora(actual_departure_time)) return 0;
    return 1;
}

int validar_arrival(const char *arrival_date, const char *arrival_time) {
    if (!validar_data(arrival_date)) return 0;
    if (!validar_hora(arrival_time)) return 0;
    return 1;
}

int validar_actual_arrival(const char *actual_arrival_date, const char *actual_arrival_time) {
    if (!validar_data(actual_arrival_date)) return 0;
    if (!validar_hora(actual_arrival_time)) return 0;
    return 1;
}

int validar_gate(int gate) {
    return (gate > 0 && gate < 100);
}


int validar_status(const char *status) {
    if (!status) return 0;

    const char *validos[] = {
        "On Time",
        "Delayed",
        "Cancelled",
    };
    int n = sizeof(validos) / sizeof(validos[0]);

    for (int i = 0; i < n; i++) {
        if (strcmp(status, validos[i]) == 0) return 1;
    }
    return 0;
}

int validar_origin(const char *origin) {
    if (!origin || strlen(origin) != 3) return 0;
    for (int i = 0; i < 3; i++) {
        if (!isalpha(origin[i])) return 0;
    }
    return 1;
}   

int validar_destination(const char *destination, const char *origin) {
    if (!destination || strlen(destination) != 3 ) return 0;
    for (int i = 0; i < 3; i++) {
        if (!isalpha(destination[i])) return 0;
        if (strcmp(origin, destination) == 0) return 0;
    }
    return 1;
}

int validar_aircraft(const char *aircraft) {
    if (!aircraft || strlen(aircraft) != 8)
        return 0;

    for (int i = 0; i < 2; i++) {
        if (!isalnum(aircraft[i]))
            return 0;
    }

    if (aircraft[2] != '-')
        return 0;

    for (int i = 3; i < 8; i++) {
        if (!isalnum(aircraft[i]))
            return 0;
    }

    return 1;
}

// Funções auxiliares para validar data e hora


// Verifica formato de data AAAA-MM-DD
int validar_data(const char *data) {
    if (!data || strlen(data) != 10) return 0;
    if (data[4] != '-' || data[7] != '-') return 0;

    int ano, mes, dia;
    if (sscanf(data, "%d-%d-%d", &ano, &mes, &dia) != 3) return 0;
    if (ano < 1900 || ano > 2025) return 0;
    if (mes < 1 || mes > 12) return 0;
    if (dia < 1 || dia > 31) return 0;

    return 1;
}

// Verifica formato de hora HH:MM
int validar_hora(const char *hora) {
    if (!hora || strlen(hora) != 5) return 0;
    if (hora[2] != ':') return 0;

    int h, m;
    if (sscanf(hora, "%d:%d", &h, &m) != 2) return 0;
    if (h < 0 || h > 23) return 0;
    if (m < 0 || m > 59) return 0;

    return 1;
}

// ============================================================
// VALIDAÇÃO GERAL (com encapsulamento)
// ============================================================
int validar_voo(const Voo *v) {
    if (!v) return 0;

    return validar_flight_id(get_flight_id(v)) &&
           validar_departure(get_departure_date(v), get_departure_time(v)) &&
           validar_actual_departure(get_actual_departure_date(v), get_actual_departure_time(v) ) &&
           validar_arrival(get_arrival_date(v), get_arrival_time(v)) &&
           validar_actual_arrival(get_actual_arrival_date(v), get_actual_arrival_time(v)) &&
           validar_aircraft(get_aircraft(v)) &&
           validar_status(get_status(v)) &&
           validar_data(get_data(get_departure(v))) &&
           validar_hora(get_hora(get_departure(v))) &&
           validar_data(get_data(get_arrival(v))) &&
           validar_hora(get_hora(get_arrival(v)));
}

