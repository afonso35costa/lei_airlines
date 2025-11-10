#ifndef VALIDACAO_AERONAVES_H
#define VALIDACAO_AERONAVES_H

#include "aeronaves.h"

// Funções de validação individual
int validar_identifier(const char *identifier);
int validar_manufacturer(const char *manufacturer);
int validar_model(const char *model);
int validar_year(int year);
int validar_capacity(int capacity);
int validar_range(int range);

// Função geral para validar uma aeronave
int validar_aeronave(const Aeronaves *a);

// Função para processar o ficheiro CSV e gerar erros
void processar_ficheiro_aeronaves(const char *input_path, const char *erros_path);

#endif
