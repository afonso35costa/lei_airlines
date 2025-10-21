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

Reservas* criar_reserva(char *reservation_id, char **flight_ids, char *document_number,
                        char *seat, double price, bool extra_luggage,
                        bool priority_boarding, char *qr_code) {
    Reservas *reserva = (Reservas *)malloc(sizeof(Reservas));
    reserva->reservation_id = reservation_id;
    reserva->flight_ids = flight_ids;
    reserva->document_number = document_number;
    reserva->seat = seat;
    reserva->price = price;
    reserva->extra_luggage = extra_luggage;
    reserva->priority_boarding = priority_boarding;
    reserva->qr_code = qr_code;
    return reserva;
}

