#ifndef PASSAGEIROS_H
#define PASSAGEIROS_H

#include <stdbool.h>

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

char* get_document_number(const Passageiros *p);
char* get_first_name(const Passageiros *p);
char* get_last_name(const Passageiros *p);
char* get_dob(const Passageiros *p);
char* get_nationality(const Passageiros *p);
char* get_gender(const Passageiros *p);
char* get_email(const Passageiros *p);
char* get_phone(const Passageiros *p);
char* get_address(const Passageiros *p);
char* get_photo(const Passageiros *p);

// =================================================================================================================================
// SETTERS - Funções para definir valores
// =================================================================================================================================

void set_document_number(Passageiros *p, const char *doc);
void set_first_name(Passageiros *p, const char *name);
void set_last_name(Passageiros *p, const char *name);
void set_dob(Passageiros *p, const char *birth);
void set_nationality(Passageiros *p, const char *nat);
void set_gender(Passageiros *p, const char *gen);
void set_email(Passageiros *p, const char *mail);
void set_phone(Passageiros *p, const char *tel);
void set_address(Passageiros *p, const char *addr);
void set_photo(Passageiros *p, const char *pic);

// ===========================================
// PARSER - Funções para ler dados
// ===========================================

// Parse de uma linha CSV para passageiro
Passageiros* parse_passageiro_from_csv(const char *linha);

// Carrega passageiros de ficheiro CSV
int load_passageiros_from_file(const char *filename, Passageiros ***passageiros, int *count);

// Liberta array de passageiros
void free_passageiros_array(Passageiros **passageiros, int count);


#endif 