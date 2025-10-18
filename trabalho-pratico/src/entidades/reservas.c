#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "reservas.h"

typedef struct reservas {
    char *reservation_id;             // número da reserva
    char **flight_ids;                // identificadores de voo (assumindo máximo 10 voos)
    char *document_number;        // documento de identificação do passageiro
    char *seat;                   // número do assento (ex: "12A")
    double price;                     // preço da reserva
    bool extra_luggage;               // bagagem extra incluída
    bool priority_boarding;           // embarque prioritário incluído
    char *qr_code;                // string do código QR
} Reservas;

