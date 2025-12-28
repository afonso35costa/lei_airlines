#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "voos.h"
#include "datas.h"
#include "validacao_voos.h"
#include "parser_voos.h"
#include "parser_utils.h"

#define ERRO_FILE "resultados/voos_errors.csv"

Voo *parse_voo_line(const char *line) {
    if (!line) return NULL;

    char *temp = strdup(line);
    if (!temp) return NULL;

    char *rest = temp;
    char *token = strsep(&rest, ",");
    char *campos[11] = {0};
    int i = 0;

    while ((token) != NULL && i < 11) {
        campos[i] = strip_quotes(token);
        i++;
        token = strsep(&rest, ",");
    }

    DataHora *dep = ler_data_hora(campos[1]);
    DataHora *act_dep = ler_data_hora(campos[2]);
    DataHora *arr = ler_data_hora(campos[3]);
    DataHora *act_arr = ler_data_hora(campos[4]);

    Voo *v = init_voo(campos[0], dep, act_dep, arr, act_arr,
                        campos[5], campos[6], campos[7], campos[8],
                        campos[9], campos[10]);
    for (int j = 0; j < 11; j++) free(campos[j]);

    free(temp);
    return v;
}

Voo *parse_and_validate_voo_line(const char *line, FILE *ferr) {
    if (!line || strlen(line) == 0)
        return NULL;

    // Parsing sintático (sempre válido estruturalmente)
    Voo *v = parse_voo_line(line);

    // Validação semântica
     if (!validar_voo(v)) {
        if (ferr) {
            fprintf(ferr, "%s\n", line);  // só escreve a linha inválida
        }
        destroy_voo(v);
        return NULL;
    }
    
    return v;  // válido ✅
}

// Funcao que transforma um Voo numa linha CSV
char *voo_para_csv(Voo *v) {
    if (!v) return NULL;
    char *dep_str = data_hora_para_texto(get_departure_voo(v));
    char *act_dep_str = data_hora_para_texto(get_actual_departure_voo(v));
    char *arr_str = data_hora_para_texto(get_arrival_voo(v));
    char *act_arr_str = data_hora_para_texto(get_actual_arrival_voo(v));
    char *line = malloc(512);
    if (!line) {
        free(dep_str);
        free(act_dep_str);
        free(arr_str);
        free(act_arr_str);
        return NULL;
    }
    snprintf(line, 512, "\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\"",
             get_flight_id_voo(v), dep_str, act_dep_str, arr_str, act_arr_str, get_gate_voo(v),
             get_status_voo(v), get_origin_voo(v), get_destination_voo(v), get_aircraft_voo(v),
             get_airline_voo(v));
    free(dep_str);
    free(act_dep_str);
    free(arr_str);
    free(act_arr_str);
    return line;
}
