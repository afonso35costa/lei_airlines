#ifndef VALIDACAO_VOOS_H
#define VALIDACAO_VOOS_H

#include "voos.h"   


// Funções de validação individual

int validar_flight_id_voos(const char *flight_id);


// ============================================================
// Validação geral
// ============================================================
int validar_voo(const Voo *v);


#endif
