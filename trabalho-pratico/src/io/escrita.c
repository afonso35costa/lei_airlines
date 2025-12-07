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

void escreve_aeroporto1 (Aeroportos *a, FILE *out) {
    if (!a) fprintf(out, "\n");

    else {
        fprintf(out, "%s,%s,%s,%s,%s\n",
        get_code_aeroporto(a),
        get_name_aeroporto(a),
        get_city_aeroporto(a),
        get_country_aeroporto(a),
        get_type_aeroporto(a)
    );
    }
}

// Escreve array de aeronaves em ficheiro

void escreve_aeronaves (Aeronaves **stats, int num_aeronaves, FILE *out) {
    if (!stats) {
        fprintf(out, "\n");
        return;
    }
    for (int i = 0; i < num_aeronaves; i++) {
        fprintf(out, "%s,%s,%s,%d\n",
                get_identifier_aeronave(stats[i]),
                get_manufacturer_aeronave(stats[i]),
                get_model_aeronave(stats[i]),
                get_num_voos_aeronave(stats[i])
            );
    }
    for (int i = num_aeronaves; i < num_aeronaves; i++) {
        free_aeronave(stats[i]);
    }
    free(stats);
}

// Escreve aeroporto e num_departures

void escreve_aeroporto3 (Aeroportos *a, FILE *out) {
    if (!a) fprintf(out, "\n");

    else { 
        fprintf(out, "%s,%s,%s,%s,%d\n",
        get_code_aeroporto(a),
        get_name_aeroporto(a),
        get_city_aeroporto(a),
        get_country_aeroporto(a),
        get_departures_aeroporto(a)
    );
    }
}

