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
    
    if (!is_valid_string(p->document_number)) return false;
    if (!is_valid_string(p->first_name)) return false;
    if (!is_valid_string(p->last_name)) return false;
    if (!is_valid_string(p->dob) || strlen(p->dob) != 10) return false; // Data tem formato específico (aaaa-mm-dd)
    if (!is_valid_string(p->nationality)) return false;
    if (!is_valid_string(p->gender)) return false;
    if (!is_valid_string(p->email)) return false;
    if (!is_valid_string(p->phone)) return false;
    if (!is_valid_string(p->address)) return false;
    if (!is_valid_string(p->photo)) return false;
    
    return true;
}

// Função auxiliar para verificar se string é válida
bool is_valid_string(const char *str) {
    return str != NULL && strlen(str) > 0;
}