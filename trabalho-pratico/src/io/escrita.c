#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "escrita.h"
#include "aeroportos.h"
#include "aeronaves.h"
#include "queries.h"

//Função que abre ficheiros para escrita
FILE* abrir_ficheiro_escrita(const char* path_filename) {
    char path[512];
    snprintf(path, sizeof(path), "%s", path_filename);
    FILE *f = fopen(path, "w");
    if (!f) {
        perror(path);
    }
    return f;
}

// Escreve aeroporto em ficheiro

void escreve_aeroporto1 (Aeroportos *a, FILE *out, char* qtype) {
    if (!a) fprintf(out, "\n");

    else if (strcmp(qtype, "1") == 0) {
        fprintf(out, "%s;%s;%s;%s;%s;%d;%d\n",
        get_code_aeroporto(a),
        get_name_aeroporto(a),
        get_city_aeroporto(a),
        get_country_aeroporto(a),
        get_type_aeroporto(a),
        get_dep_count_aeroporto(a),
        get_arr_count_aeroporto(a)
    );
    }
    else if (strcmp(qtype, "1S") == 0) {
        fprintf(out, "%s=%s=%s=%s=%s=%d=%d\n",
        get_code_aeroporto(a),
        get_name_aeroporto(a),
        get_city_aeroporto(a),
        get_country_aeroporto(a),
        get_type_aeroporto(a),
        get_dep_count_aeroporto(a),
        get_arr_count_aeroporto(a)
    );
    }
}

// Escreve array de aeronaves em ficheiro

void escreve_aeronaves (Aeronaves **stats, int num_aeronaves, FILE *out, char* qtype) {
    if (!stats) {
        fprintf(out, "\n");
        return;
    }
    if (strcmp (qtype, "2") == 0) {
        for (int i = 0; i < num_aeronaves; i++) {
            fprintf(out, "%s;%s;%s;%d\n",
                    get_identifier_aeronave(stats[i]),
                    get_manufacturer_aeronave(stats[i]),
                    get_model_aeronave(stats[i]),
                    get_num_voos_aeronave(stats[i])
                );
        }
        for (int i = num_aeronaves; i < num_aeronaves; i++) {
            destroy_aeronave(stats[i]);
        }
        free(stats);
        return;
    }
    else if (strcmp (qtype, "2S") == 0) {
        for (int i = 0; i < num_aeronaves; i++) {
        fprintf(out, "%s=%s=%s=%d\n",
                get_identifier_aeronave(stats[i]),
                get_manufacturer_aeronave(stats[i]),
                get_model_aeronave(stats[i]),
                get_num_voos_aeronave(stats[i])
            );
        }
        for (int i = num_aeronaves; i < num_aeronaves; i++) {
            destroy_aeronave(stats[i]);
        }
    }
    free(stats);
}

// Escreve aeroporto e num_departures

void escreve_aeroporto3 (Aeroportos *a, FILE *out, char* qtype) {
    if (!a) fprintf(out, "\n");

    else if (strcmp(qtype, "3") == 0) { 
        fprintf(out, "%s;%s;%s;%s;%d\n",
        get_code_aeroporto(a),
        get_name_aeroporto(a),
        get_city_aeroporto(a),
        get_country_aeroporto(a),
        get_departures_aeroporto(a)
    );
    } 
    else if (strcmp(qtype, "3S") == 0) {
        fprintf(out, "%s=%s=%s=%s=%d\n",
        get_code_aeroporto(a),
        get_name_aeroporto(a),
        get_city_aeroporto(a),
        get_country_aeroporto(a),
        get_departures_aeroporto(a)
    );
    }
}

void escreve_tempos5 (Time **time, int num_companhias, FILE *out, char *q_type) {
    if (!time) {
        fprintf(out, "\n");
        return;
    }
    if (strcmp (q_type, "5") == 0) {
        for (int i = 0; i < num_companhias; i++) {
            if (!time[i]) printf("NULL\n");
            fprintf(out, "%s;%d,%.3f\n",
                    get_time_airline(time[i]),
                    get_time_delayed_count(time[i]),
                    round3((double) get_time_total(time[i]) / get_time_delayed_count(time[i]))
                );
        }
        for (int j=num_companhias; j < num_companhias ; j++) {
            free_time(time[j]);
        }
        free(time);
        return;
    }
    else if (strcmp (q_type, "5S") == 0) {
        for (int i = 0; i < num_companhias; i++) {
        fprintf(out, "%s=%d=%.3f\n",
                get_time_airline(time[i]),
                get_time_delayed_count(time[i]),
                round3((double) get_time_total(time[i]) / get_time_delayed_count(time[i]))
            );
        }
        for (int j=num_companhias; j < num_companhias ; j++) {
            free_time(time[j]);
        }
        free(time);
        return;
    }
}

