#ifndef VALIDACAO_VOOS_H
#define VALIDACAO_VOOS_H

#include "voos.h"   


// Funções de validação individual

int validar_flight_id(const char *flight_id);
int validar_departure(const char *departure_date, const char *departure_time);
int validar_arrival(const char *arrival_date, const char *arrival_time);
int validar_aircraft(const char *aircraft);
int validar_status(const char *status);


// Funções auxiliares para validar datas e horas
int validar_data(const char *data);       // formato AAAA-MM-DD
int validar_hora(const char *hora);       // formato HH:MM

// ============================================================
// Validação geral
// ============================================================
int validar_voo(const Voo *v);

// ============================================================
// Leitura e processamento de ficheiro CSV
// ============================================================
void processar_ficheiro_voos(const char *input_path, const char *erros_path);

#endif
