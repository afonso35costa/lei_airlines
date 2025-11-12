#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "passageiros.h"



// FUNÇÃO DE VALIDAÇÃO - verifica se os dados são válidos

/*
bool validate_passageiro(const Passageiros *p) {
    if (p == NULL) return false;
    
    if (p->document_number == NULL || strlen(p->document_number) == 0) return false;
    if (p->first_name == NULL || strlen(p->first_name) == 0) return false;
    if (p->last_name == NULL || strlen(p->last_name) == 0) return false; 
    if (p->dob == NULL || strlen(p->dob) != 10) return false; // formato aaaa-mm-dd
    if (p->nationality == NULL || strlen(p->nationality) == 0) return false;
    if (p->gender == NULL || strlen(p->gender) == 0) return false;
    if (p->email == NULL || strlen(p->email) == 0) return false;
    if (p->phone == NULL || strlen(p->phone) == 0) return false;
    if (p->address == NULL || strlen(p->address) == 0) return false;
    if (p->photo == NULL || strlen(p->photo) == 0) return false;
    return true;
}
*/

bool validate_passageiro(const Passageiros *p) {
    if (p == NULL) return false;

    if (!is_valid_string(get_document_number(p))) return false;
    if (!is_valid_string(get_first_name(p))) return false;
    if (!is_valid_string(get_last_name(p))) return false;
    if (!is_valid_string(get_dob(p)) || strlen(get_dob(p)) != 10) return false; // Data tem formato específico (aaaa-mm-dd)
    if (!is_valid_string(get_nationality(p))) return false;
    if (!is_valid_string(get_gender(p))) return false;
    if (!is_valid_string(get_email(p))) return false;
    if (!is_valid_string(get_phone(p))) return false;
    if (!is_valid_string(get_address(p))) return false;
    if (!is_valid_string(get_photo(p))) return false;

    return true;
}

// Função auxiliar para verificar se string é válida
bool is_valid_string(const char *str) {
    return str != NULL && strlen(str) > 0;
}