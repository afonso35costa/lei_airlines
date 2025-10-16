#include <stdio.h>
#include <stdlib.h>

#include "voos.h"

typedef struct voos{
    int flight_id;                 // identificador único do voo
    char departure[20];            // data e hora de partida estimada do voo
    char actual_departure[20];     // data e hora de partida real do voo
    char arrival[20];              // data e hora de chegada estimada do voo
    char actual_arrival[20];       // data e hora de chegada real do voo
    char gate[10];                 // porta de embarque do voo
    char status[10];               // estado do voo, i.e., On Time, Delayed ou Cancelled
    char origin[4];                // código IATA do aeroporto de origem
    char destination[4];           // código IATA do aeroporto de destino
    char aircraft[10];             // identificador único da aeronave utilizada no voo, i.e., tail number
    char airline[50];              // nome da companhia aérea responsável pelo voo
    char tracking_url[100];        // URL para o rastreamento do voo
} Voos;



