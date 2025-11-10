#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "validacao_voos.h"
#include "voos.h"

// Funções de validação individual

int validar_flight_id(const char *flight_id) {
    if (!flight_id || strlen(flight_id) < 3) return 0;
    for (int i = 0; flight_id[i]; i++) {
        if (!isalnum(flight_id[i])) return 0;
    }
    return 1;
}

int validar_departure(const char *departure) {
    if (!departure || strlen(departure) != 3) return 0;
    for (int i = 0; i < 3; i++) {
        if (!isalpha(departure[i])) return 0;
    }
    return 1;
}

int validar_arrival(const char *arrival) {
    if (!arrival || strlen(arrival) != 3) return 0;
    for (int i = 0; i < 3; i++) {
        if (!isalpha(arrival[i])) return 0;
    }
    return 1;
}


int validar_aircraft(const char *aircraft) {
    if (!aircraft || strlen(aircraft) < 3) return 0;
    for (int i = 0; aircraft[i]; i++) {
        if (!isalnum(aircraft[i]) && aircraft[i] != '-') return 0;
    }
    return 1;
}

int validar_status(const char *status) {
    if (!status) return 0;

    const char *validos[] = {
        "scheduled",
        "active",
        "landed",
        "cancelled",
        "incident",
        "diverted"
    };
    int n = sizeof(validos) / sizeof(validos[0]);

    for (int i = 0; i < n; i++) {
        if (strcmp(status, validos[i]) == 0) return 1;
    }
    return 0;
}

int validar_tracking_url(const char *tracking_url) {
    if (!tracking_url || strlen(tracking_url) < 8) return 0;
    return (strncmp(tracking_url, "http://", 7) == 0 ||
            strncmp(tracking_url, "https://", 8) == 0);
}


// Funções auxiliares para validar data e hora


// Verifica formato de data AAAA-MM-DD
int validar_data(const char *data) {
    if (!data || strlen(data) != 10) return 0;
    if (data[4] != '-' || data[7] != '-') return 0;

    int ano, mes, dia;
    if (sscanf(data, "%d-%d-%d", &ano, &mes, &dia) != 3) return 0;
    if (ano < 1900 || ano > 2100) return 0;
    if (mes < 1 || mes > 12) return 0;
    if (dia < 1 || dia > 31) return 0;

    return 1;
}

// Verifica formato de hora HH:MM
int validar_hora(const char *hora) {
    if (!hora || strlen(hora) != 5) return 0;
    if (hora[2] != ':') return 0;

    int h, m;
    if (sscanf(hora, "%d:%d", &h, &m) != 2) return 0;
    if (h < 0 || h > 23) return 0;
    if (m < 0 || m > 59) return 0;

    return 1;
}

// ============================================================
// Função geral — valida todos os campos de um voo
// ============================================================
int validar_voo(const Voo *v) {
    if (!v) return 0;

    return validar_flight_id(v->flight_id) &&
           validar_departure(v->departure) &&
           validar_arrival(v->arrival) &&
           validar_aircraft(v->aircraft) &&
           validar_status(v->status) &&
           validar_tracking_url(v->tracking_url) &&
           validar_data(v->scheduled_departure->data) &&
           validar_hora(v->scheduled_departure->hora) &&
           validar_data(v->scheduled_arrival->data) &&
           validar_hora(v->scheduled_arrival->hora);
}

// ============================================================
// Processamento do ficheiro CSV — leitura e geração de erros
// ============================================================
void processar_ficheiro_voos(const char *input_path, const char *erros_path) {
    FILE *input = fopen(input_path, "r");
    FILE *erros = fopen(erros_path, "w");

    if (!input || !erros) {
        printf("Erro ao abrir ficheiros.\n");
        return;
    }

    char linha[1024];
    int linha_num = 0;

    while (fgets(linha, sizeof(linha), input)) {
        linha_num++;

        // Ignorar cabeçalho
        if (linha_num == 1) continue;

        // Exemplo genérico (deves substituir por parsing real via strtok)
        Voo *v = init_voo("TP1923", "OPO", "LIS", "A320", "scheduled",
                          "https://tracking.flytap.com/TP1923",
                          "2025-03-10", "09:15",
                          "2025-03-10", "10:10");

        if (!validar_voo(v)) {
            fprintf(erros, "Linha %d: %s", linha_num, linha);
        }

        destruir_voo(v);
    }

    fclose(input);
    fclose(erros);
}
