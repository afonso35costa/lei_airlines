#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "reservas.h"

typedef struct reservas {
    int reservation_id;             // número da reserva
    int flight_ids[10];             // identificadores de voo (assumindo máximo 10 voos)
    char document_number[20];       // documento de identificação do passageiro
    char seat[10];                  // número do assento (ex: "12A")
    double price;                   // preço da reserva
    bool extra_luggage;             // bagagem extra incluída
    bool priority_boarding;         // embarque prioritário incluído
    char qr_code[50];              // string do código QR
} Reservas;

