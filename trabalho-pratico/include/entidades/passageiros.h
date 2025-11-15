#ifndef PASSAGEIROS_H
#define PASSAGEIROS_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// Estrutura que representa um passageiro
typedef struct passageiros Passageiros;

// ==============================================================================================================================================================================================
// FUNÇÕES DE GESTÃO DE MEMÓRIA
// ==============================================================================================================================================================================================

// Cria um novo passageiro e aloca memória
Passageiros* create_passageiro(void);

// Inicializa um passageiro com dados
Passageiros *init_passageiro(const char *doc, const char *fname, const char *lname,
                             const char *birth, const char *nat, const char *gen,
                             const char *mail, const char *tel, const char *addr, const char *pic);

// Compara dois passageiros
int compare_passageiros(const Passageiros *p1, const Passageiros *p2);

// Imprime os dados de um passageiro
void print_passageiro(const Passageiros *p);

// Liberta toda a memória associada a um passageiro
void destroy_passageiro(Passageiros *p);

// ==============================================FUNÇÕES DE VALIDAÇÃO============================================================================================================================

// Valida se os dados do passageiro são válidos
bool validate_passageiro(const Passageiros *p);
// Função auxiliar para validação
bool is_valid_string(const char *str);

// ==============================================================================================================================================================================================
// GETTERS - Funções para obter valores
// ==============================================================================================================================================================================================

char* get_document_number_passageiros(const Passageiros *p);
char* get_first_name_passageiros(const Passageiros *p);
char* get_last_name_passageiros(const Passageiros *p);
char* get_dob_passageiros(const Passageiros *p);
char* get_nationality_passageiros(const Passageiros *p);
char* get_gender_passageiros(const Passageiros *p);
char* get_email_passageiros(const Passageiros *p);
char* get_phone_passageiros(const Passageiros *p);
char* get_address_passageiros(const Passageiros *p);
char* get_photo_passageiros(const Passageiros *p);

// =================================================================================================================================
// SETTERS - Funções para definir valores
// =================================================================================================================================

void set_document_number_passageiros(Passageiros *p, const char *doc);
void set_first_name_passageiros(Passageiros *p, const char *name);
void set_last_name_passageiros(Passageiros *p, const char *name);
void set_dob_passageiros(Passageiros *p, const char *birth);
void set_nationality_passageiros(Passageiros *p, const char *nat);
void set_gender_passageiros(Passageiros *p, const char *gen);
void set_email_passageiros(Passageiros *p, const char *mail);
void set_phone_passageiros(Passageiros *p, const char *tel);
void set_address_passageiros(Passageiros *p, const char *addr);
void set_photo_passageiros(Passageiros *p, const char *pic);


#endif 