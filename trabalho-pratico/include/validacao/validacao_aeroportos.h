#ifndef VALIDACAO_AEROPORTOS_H
#define VALIDACAO_AEROPORTOS_H

#include "aeroportos.h"

// Funções de validação individual
int validar_code(const char *code);
int validar_name(const char *name);
int validar_city(const char *city);
int validar_country(const char *country);
int validar_latitude(double latitude);
int validar_longitude(double longitude);
int validar_icao(const char *icao);
int validar_type(const char *type);

// Função geral
int validar_aeroporto(const Aeroportos *a);

// Processamento do ficheiro CSV
void processar_ficheiro_aeroportos(const char *input_path, const char *erros_path);

#endif
