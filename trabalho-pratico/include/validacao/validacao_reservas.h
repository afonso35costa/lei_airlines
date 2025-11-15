#ifndef VALIDACAO_RESERVAS_H
#define VALIDACAO_RESERVAS_H

#include "reservas.h"

// ============================================================
// FUNÇÕES DE VALIDAÇÃO INDIVIDUAIS
// ============================================================

int validar_reservation_id(const char *id);
int validar_flight_ids(const char *flight_ids);
int validar_document_number_reserva(const char *doc);
int validar_seat(const char *seat);
int validar_price(double price);
int validar_extra_luggage(bool extra_luggage);
int validar_priority_boarding(bool priority_boarding);
int validar_qr_code(const char *qr);

// ============================================================
// FUNÇÃO DE VALIDAÇÃO GERAL (COM ENCAPSULAMENTO)
// ============================================================

int validar_reserva(const Reservas *r);

// ============================================================
// LEITURA DE FICHEIRO E GERAÇÃO DE FICHEIRO DE ERROS
// ============================================================

void processar_ficheiro_reservas(const char *ficheiro_entrada, const char *ficheiro_erros);

#endif
