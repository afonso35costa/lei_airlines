#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "voos.h"

typedef struct voos {
    char *flight_id;         // identificador único do voo
    char *departure;         // data e hora de partida estimada (aaaa-mm-dd hh:mm)
    char *actual_departure;  // data e hora de partida real
    char *arrival;           // data e hora de chegada estimada
    char *actual_arrival;    // data e hora de chegada real
    char *gate;              // porta de embarque
    char *status;            // estado: On Time, Delayed, Cancelled
    char *origin;            // código IATA do aeroporto de origem
    char *destination;       // código IATA do aeroporto de destino
    char *aircraft;          // identificador único da aeronave
    char *airline;           // nome da companhia aérea
    char *tracking_url;      // URL para rastreamento do voo
} Voos;




