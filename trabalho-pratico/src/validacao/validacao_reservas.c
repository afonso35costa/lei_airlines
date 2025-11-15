#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "validacao_reservas.h"

// ============================================================
// FUNÇÕES DE VALIDAÇÃO INDIVIDUAIS
// ============================================================


int validar_reservation_id(const char *reservation_id) {
    if (!reservation_id || strlen(reservation_id) != 10) return 0;

    if (reservation_id[0] != 'R')
        return 0;

    for (int i = 1; i < 10; i++) {
        if (!isdigit(reservation_id[i]))
            return 0;
    }

    return 1;
}

// ID do voo (alfanumérico)
int validar_flight_ids(const char *flight_ids) {
    if (!flight_ids || strlen(flight_ids) != 7) return 0;
    for (int i = 0; i < 2; i++) {
        if (!isupper(flight_ids[i])) return 0;
    }

    for (int i = 2; i < 7; i++) {
        if (!isdigit(flight_ids[i])) return 0;
    }

    return 1;
}

// Documento do passageiro (alfanumérico, 5–15 chars)
int validar_document_number_reserva(const char *document_number) {
    if (!document_number || strlen(document_number) != 9) return 0;
    for (int i = 0; i < 9; i++) {
        if (!isdigit(document_number[i])) return 0;
    }
    return 1;
}

// Lugar (ex: 12A, 3C)
int validar_seat(const char *seat) {
    if (!seat) return 0;
    int len = strlen(seat);
    if (len < 1 || len > 4) return 0;

    int i = 0;
    while (isdigit(seat[i])) i++;
    if (i == 0 || i >= len) return 0; // precisa número + letra
    char letra = toupper(seat[i]);
    return (letra >= 'A' && letra <= 'F');
}

// Preço (valor positivo)
int validar_price(double price) {
    return price > 0.0 && price < 999999.0;
}

// Bagagem extra (valor >= 0 e < 100 kg)
int validar_extra_luggage(bool extra_luggage) {
    return (extra_luggage == true || extra_luggage == false);
}

// Priority boarding (bool - 0 ou 1)
int validar_priority_boarding(bool priority_boarding) {
    return (priority_boarding == true || priority_boarding == false);
}

// Código QR (alfanumérico + pode conter '-')
int validar_qr_code(const char *qr) {
    if (!qr) return 0;
    int len = strlen(qr);
    if (len < 4 || len > 20) return 0;
    for (int i = 0; i < len; i++)
        if (!isalnum(qr[i]) && qr[i] != '-') return 0;
    return 1;
}

// ============================================================
// FUNÇÃO DE VALIDAÇÃO GERAL (COM ENCAPSULAMENTO)
// ============================================================

int validar_reserva(const Reservas *r) {
    if (!r) return 0;

    return validar_reservation_id(get_reservation_id(r)) &&
           validar_flight_ids(get_flight_ids(r)) &&
           validar_document_number_reserva(get_document_number_reserva(r)) &&
           validar_seat(get_seat(r)) &&
           validar_price(get_price(r)) &&
           validar_extra_luggage(get_extra_luggage(r)) &&
           validar_priority_boarding(get_priority_boarding(r)) &&
           validar_qr_code(get_qr_code(r));
}

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
