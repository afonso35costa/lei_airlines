#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "passageiros.h"

typedef struct passageiros {
    char *document_number; // número do documento de identificação
    char *first_name;      // primeiro nome
    char *last_name;       // apelido
    char *dob;             // data de nascimento (aaaa-mm-dd)
    char *nationality;     // nacionalidade
    char *gender;          // género (M, F, Outro)
    char *email;           // email
    char *phone;           // número de telefone
    char *address;         // morada
    char *photo;           // fotografia (ficheiro ou URL)
} Passageiros;

