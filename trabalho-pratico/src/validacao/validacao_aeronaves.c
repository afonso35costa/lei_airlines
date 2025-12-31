#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "validacao_aeronaves.h"
#include "aeronaves.h"

// VALIDAÇÕES INDIVIDUAIS


int validar_ano_aeronave(const char *anoA) {
    if (!anoA || strlen(anoA) != 4) {
        return 0;
    }

    for (int i = 0; i < 4; i++) {
        if (!isdigit(anoA[i])) {
            return 0;
        }
    }
    return (atoi(anoA) <= 2025);
}

// VALIDAÇÃO GERAL 

int validar_aeronave(const Aeronaves *a) {
    if (!a) return 0;
    return validar_ano_aeronave(get_year_aeronave(a));
}
