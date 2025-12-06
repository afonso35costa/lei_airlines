#ifndef VALIDACAO_PASSAGEIROS_H
#define VALIDACAO_PASSAGEIROS_H
#include "passageiros.h"

// Funções de validação individuais
int validar_document_number_passageiro(const char *document_number);
int validar_email_passageiro(const char *email);
int validar_genero_passageiro(const char *genero);
int validar_dob_passageiro(const char *dob);

// Validação geral
int validar_passageiro(const Passageiros *p);

#endif
