#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "validacao_voos.h"
#include "voos.h"
#include "datas.h"
#include "validacao_aeroportos.h"

// ============================================================
// VALIDAÇÕES INDIVIDUAIS
// ============================================================

int validar_flight_id_voos(const char *flight_id) {
    if (!flight_id ) return 0;
    for (int i = 0; i < 2; i++) {
        if (!isupper(flight_id[i])) return 0;
    }

    for (int i = 2; flight_id[i] != "\0"; i++) {
        if (!isdigit(flight_id[i])) return 0;
    }
    return 1;
}

int validar_datas_voos(DataHora *dep, DataHora *act_dep, DataHora *arr, DataHora *act_arr) {
    if (!dep || !act_dep || !arr || !act_arr) return 0;

    if (get_data(act_dep) == 0 && get_hora(act_dep) == 0 && get_data(act_arr) == 0 && get_hora(act_arr) == 0) {
        return 1; // Voo cancelado
    }
    if (comparar_data_hora(arr,dep) < 0) return 0;
    if (comparar_data_hora(act_arr, act_dep) < 0) return 0;


    return 1;
}

int validar_status_voos(Voo *v) {
    if (!v) return 0;
    const char *status = get_status_voo(v);
    if (!status) return 0;

    if (!(strcmp(status, "On Time") == 0 || strcmp(status, "Delayed") == 0 || strcmp(status, "Cancelled") == 0)) {
        return 0;
    }

    if (strcmp(status, "Cancelled") == 0) {
        DataHora *act_dep = get_actual_departure_voo(v);
        DataHora *act_arr = get_actual_arrival_voo(v);
        if (get_data(act_dep) != 0 || get_hora(act_dep) != 0 || get_data(act_arr) != 0 || get_hora(act_arr) != 0) {
            return 0;
        }
    }

    if (strcmp(status, "Delayed") == 0) {
        DataHora *dep = get_departure_voo(v);
        DataHora *act_dep = get_actual_departure_voo(v);
        DataHora *arr = get_arrival_voo(v);
        DataHora *act_arr = get_actual_arrival_voo(v);

        if (comparar_data_hora(act_dep, dep) <= 0 && comparar_data_hora(act_arr, arr) <= 0) {
            return 0;
        }
    }    
    return 1;
}

int valida_destination_origin_voos(const char *destination, const char *origin) {
    if (!destination || !origin ) return 0;
    if (strcmp(destination, origin) == 0) return 0;
    if (!validar_code_aeroporto(destination)) return 0;
    if (!validar_code_aeroporto(origin)) return 0;
    return 1;
}

// ============================================================
// VALIDAÇÃO GERAL (com encapsulamento)
// ============================================================

int validar_voo(Voo *v) {
    if (!v) return 0;
    if (!valida_destination_origin_voos(get_destination_voo(v), get_origin_voo(v))) return 0;
    if (!validar_status_voos(v)) return 0;
    if (!validar_datas_voos(get_departure_voo(v), get_actual_departure_voo(v), get_arrival_voo(v), get_actual_arrival_voo(v))) return 0;
    if (!validar_flight_id_voos(get_flight_id_voo(v))) return 0;

    return 1;
}
