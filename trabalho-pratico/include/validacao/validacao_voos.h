#ifndef VALIDACAO_VOOS_H
#define VALIDACAO_VOOS_H

#include "voos.h"   


/**
 * @brief Valida o identificador do voo.
 * 
 * @param flight_id Identificador do voo a ser validado
 * 
 * @return 1 se válido, 0 caso contrário
 */
int validar_flight_id_voos(const char *flight_id);


/**
 * @brief Valida um voo completo.
 * 
 * @param v Ponteiro para o voo a ser validado
 * 
 * @return 1 se válido, 0 caso contrário
 */
int validar_voo(const Voo *v);


#endif
