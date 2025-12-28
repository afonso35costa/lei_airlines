#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "validacao_reservas.h"
#include "validacao_voos.h"
#include "reservas.h"



int validar_reservation_id_reservas(const char *reservation_id) {
    if (!reservation_id || strlen(reservation_id) != 10) return 0;

    if (reservation_id[0] != 'R') {
        return 0;
    }

    for (int i = 1; i < 10; i++) {
        if (!isdigit(reservation_id[i])) {
           return 0;
        }
    }

    return 1;
}


int validar_document_number_reserva(const char *document_number) {
    if (!document_number || strlen(document_number) != 9 ) return 0;
    for (int i = 0; i < 9; i++) {
        if (!isdigit(document_number[i])) {
            return 0;
        }
    }
    return 1;
}


int validar_listas_reservas(char **flight_ids) {
    if (!flight_ids) {
        return 0;
    }
    for (int i = 0; flight_ids[i] != NULL; i++) {
        if (!validar_flight_id_voos(flight_ids[i])) {
            return 0;
        }
    }
    return 1;
}
// ============================================================
// FUNÇÃO DE VALIDAÇÃO GERAL (COM ENCAPSULAMENTO)
// ============================================================

int validar_reserva(const Reservas *r) {
    if (!r) return 0;

    return validar_reservation_id_reservas(get_reservation_id_reservas(r)) &&
           validar_document_number_reserva(get_document_number_reservas(r)) &&
           validar_listas_reservas(get_flight_ids_reservas(r));
}
