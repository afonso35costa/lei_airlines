#ifndef VALIDACAO_PASSAGEIROS_H
#define VALIDACAO_PASSAGEIROS_H
#include "passageiros.h"

// Funções de validação individuais
int validar_document_number(const char *document_number);
int validar_first_name(const char *first_name);
int validar_last_name(const char *last_name);
int validar_dob(const char *dob);
int validar_nationality(const char *nationality);
int validar_gender(const char *gender);
int validar_email(const char *email);
int validar_phone(const char *phone);
int validar_address(const char *address);
int validar_photo(const char *photo);

// Validação geral
int validar_passageiro(const Passageiros *p);

// Leitura e geração de ficheiros
void processar_ficheiro_passageiros(const char *ficheiro_entrada, const char *ficheiro_erros);

#endif
