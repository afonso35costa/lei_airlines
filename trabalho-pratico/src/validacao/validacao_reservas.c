#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "validacao_reservas.h"
#include "validacao_voos.h"
#include "reservas.h"



int validar_reservation_id_reservas(const char *reservation_id) {
    if (!reservation_id || strlen(reservation_id) != 10) return 0;

    if (reservation_id[0] != 'R')
        return 0;

    for (int i = 1; i < 10; i++) {
        if (!isdigit(reservation_id[i]))
            return 0;
    }

    return 1;
}


int validar_document_number_reserva(const char *document_number) {
    if (!document_number || strlen(document_number) != 9 ) return 0;
    for (int i = 0; i < 9; i++) {
        if (!isdigit(document_number[i])) return 0;
    }
    return 1;
}

int validar_listas_reservas(const char **flight_ids) {
    if (!flight_ids) return 0;

    for (int i = 0; flight_ids[i] != NULL; i++) {
        if (!validar_flight_id_voos(flight_ids[i])) return 0;
    }
    return 1;
}
// ============================================================
// FUNÇÃO DE VALIDAÇÃO GERAL (COM ENCAPSULAMENTO)
// ============================================================

int validar_reserva(const Reservas *r) {
    if (!r) return 0;

    return validar_reservation_id_reservas(get_reservation_id_reservas(r)) &&
           validar_document_number_reserva(get_document_number_reservas(r)) &&
           validar_listas_reservas(get_flight_ids_reservas(r));
}

/*
// ============================================================
// LEITURA DE FICHEIRO E GERAÇÃO DE FICHEIRO DE ERROS
// ============================================================

void processar_ficheiro_reservas(const char *ficheiro_entrada, const char *ficheiro_erros) {
    FILE *fin = fopen(ficheiro_entrada, "r");
    if (!fin) {
        printf("Erro ao abrir ficheiro de entrada: %s\n", ficheiro_entrada);
        return;
    }

    FILE *ferr = fopen(ficheiro_erros, "w");
    if (!ferr) {
        printf("Erro ao criar ficheiro de erros: %s\n", ficheiro_erros);
        fclose(fin);
        return;
    }

    char linha[512];
    int linha_num = 0;
    int validos = 0, invalidos = 0;

    fprintf(ferr, "linha,erro\n");

    while (fgets(linha, sizeof(linha), fin)) {
        linha_num++;

        // Ignorar linhas vazias
        if (strlen(linha) < 5) continue;

        linha[strcspn(linha, "\n")] = '\0';

        // Espera-se 8 campos (com price, bagagem, priority e qr)
        char *token = strtok(linha, ",");
        char *campos[8];
        int i = 0;
        while (token && i < 8) {
            campos[i++] = token;
            token = strtok(NULL, ",");
        }

        if (i < 8) {
            fprintf(ferr, "%d,campos insuficientes\n", linha_num);
            invalidos++;
            continue;
        }

        double price = atof(campos[4]);
        double extra = atof(campos[5]);
        bool priority = (strcmp(campos[6], "1") == 0 || strcasecmp(campos[6], "true") == 0);

        // Criar reserva temporária
        Reservas *r = init_reserva(
            campos[0], campos[1], campos[2], campos[3],
            price, extra, priority, campos[7]
        );

        if (!validar_reserva(r)) {
            fprintf(ferr, "%d,campos inválidos\n", linha_num);
            invalidos++;
        } else {
            validos++;
        }

        destroy_reserva(r);
    }

    fclose(fin);
    fclose(ferr);

    printf("Validação concluída ✅\n");
    printf("Reservas válidas: %d\n", validos);
    printf("Reservas inválidas: %d (ver ficheiro '%s')\n", invalidos, ficheiro_erros);
}

*/