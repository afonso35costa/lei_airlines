#include <stdio.h>
#include <stdlib.h>

#include "passageiros.h"

typedef struct passageiros{
    int document_number;        // número do documento de identificação do passageiro
    char first_name[50];       // primeiro nome do passageiro
    char last_name[50];        // último nome do passageiro
    char dob[11];              // data de nascimento do passageiro (YYYY/MM/DD)
    char nationality[50];      // nacionalidade do passageiro
    char gender[2];            // género do passageiro (M/F)
    char email[100];           // email do passageiro
    char phone[20];            // número de telefone do passageiro
    char address[200];         // morada do passageiro
    char photo[100];           // fotografia do passageiro
}; Passageiros;

