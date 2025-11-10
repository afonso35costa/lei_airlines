#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "validacao_aeroportos.h"
#include "aeroportos.h"


// VALIDAÇÕES INDIVIDUAIS

int validar_code(const char *code) {
    // Código IATA = 3 letras
    if (!code || strlen(code) != 3) return 0;
    for (int i = 0; i < 3; i++) {
        if (!isalpha(code[i])) return 0;
    }
    return 1;
}

int validar_name(const char *name) {
    return name && strlen(name) > 2;
}

int validar_city(const char *city) {
    return city && strlen(city) > 1;
}

int validar_country(const char *country) {
    return country && strlen(country) > 1;
}

int validar_latitude(double latitude) {
    return latitude >= -90.0 && latitude <= 90.0;
}

int validar_longitude(double longitude) {
    return longitude >= -180.0 && longitude <= 180.0;
}

int validar_icao(const char *icao) {
    if (!icao || strlen(icao) != 4) return 0;
    for (int i = 0; i < 4; i++) {
        if (!isalpha(icao[i])) return 0;
    }
    return 1;
}

int validar_type(const char *type) {
    return type && strlen(type) > 5;
}


// VALIDAÇÃO GERAL

int validar_aeroporto(const Aeroportos *a) {
    if (!a) return 0;

    return validar_code(a->code) &&
           validar_name(a->name) &&
           validar_city(a->city) &&
           validar_country(a->country) &&
           validar_latitude(a->latitude) &&
           validar_longitude(a->longitude) &&
           validar_icao(a->icao) &&
           validar_type(a->type);
}


// LEITURA E GERAÇÃO DE FICHEIROS DE ERRO

void processar_ficheiro_aeroportos(const char *input_path, const char *erros_path) {
    FILE *input = fopen(input_path, "r");
    FILE *erros = fopen(erros_path, "w");

    if (!input || !erros) {
        printf("Erro ao abrir ficheiros.\n");
        return;
    }

    char linha[512];
    int linha_num = 0;

    while (fgets(linha, sizeof(linha), input)) {
        linha_num++;

        // Ignora cabeçalho
        if (linha_num == 1) continue;

        // Exemplo de validação fictícia
        Aeroportos *a = init_aeroporto("OPO", "Francisco Sá Carneiro", "Porto",
                                       "Portugal", 41.235, -8.678, "LPPR", "large_airport");

        if (!validar_aeroporto(a)) {
            fprintf(erros, "Linha %d: %s", linha_num, linha);
        }

        free_aeroporto(a);
    }

    fclose(input);
    fclose(erros);
}
