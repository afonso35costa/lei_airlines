#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aeroportos.h"
#include "voos.h"
#include "aeronaves.h"
#include "parser_aeroportos.h"
#include "parser_voos.h"
#include "parser_aeronaves.h"
#include "gestores_aeroportos.h"
#include "gestores_voos.h"
#include "gestores_aeronaves.h"

#define MAX_LINE 1024

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <caminho_csv> <ficheiro_queries>\n", argv[0]);
        return 1;
    }

    char *csv_path = argv[1];
    char *queries_file = argv[2];

    // -------------------------------------------------------------
    // Inicializar gestores
    // -------------------------------------------------------------
    GestorAeroportos *g_aero = gestor_aeroportos_create();
    GestorVoos *g_voos = gestor_voos_create();
    GestorAeronaves *g_aeroN = gestor_aeronaves_create();

    // -------------------------------------------------------------
    // Abrir ficheiros CSV e ficheiros de erro
    // -------------------------------------------------------------
    char path_aero[512], path_voos[512], path_aeron[512];
    char err_aero[512], err_voos[512], err_aeron[512];

    snprintf(path_aero, sizeof(path_aero), "%s/aeroports.csv", csv_path);
    snprintf(path_voos, sizeof(path_voos), "%s/flights.csv", csv_path);
    snprintf(path_aeron, sizeof(path_aeron), "%s/aircrafts.csv", csv_path);

    snprintf(err_aero, sizeof(err_aero), "resultados/aeroportos_errors.csv");
    snprintf(err_voos, sizeof(err_voos), "resultados/voos_errors.csv");
    snprintf(err_aeron, sizeof(err_aeron), "resultados/aeronaves_errors.csv");

    FILE *faero = fopen(path_aero, "r");
    FILE *fvoos = fopen(path_voos, "r");
    FILE *faeron = fopen(path_aeron, "r");

    FILE *err_faero = fopen(err_aero, "w");
    FILE *err_fvoos = fopen(err_voos, "w");
    FILE *err_faeron = fopen(err_aeron, "w");

    if (!faero || !fvoos || !faeron || !err_faero || !err_fvoos || !err_faeron) {
        fprintf(stderr, "Erro ao abrir ficheiros.\n");
        return 1;
    }

    // -------------------------------------------------------------
    // Ler headers e copiar para ficheiros de erro
    // -------------------------------------------------------------
    char line[MAX_LINE];

    if (fgets(line, sizeof(line), faero)) fprintf(err_faero, "%s", line);
    if (fgets(line, sizeof(line), fvoos)) fprintf(err_fvoos, "%s", line);
    if (fgets(line, sizeof(line), faeron)) fprintf(err_faeron, "%s", line);

    // -------------------------------------------------------------
    // Processar aeroportos
    // -------------------------------------------------------------
    while (fgets(line, sizeof(line), faero)) {
        Aeroportos *a = parse_and_validate_aeroporto_line(line, err_faero);
        if (a) gestor_aeroportos_add(g_aero, a);
    }

    // -------------------------------------------------------------
    // Processar voos
    // -------------------------------------------------------------
    while (fgets(line, sizeof(line), fvoos)) {
        Voo *v = parse_and_validate_voo_line(line, err_fvoos);
        if (v) gestor_voos_add(g_voos, v);
    }

    // -------------------------------------------------------------
    // Processar aeronaves
    // -------------------------------------------------------------
    while (fgets(line, sizeof(line), faeron)) {
        Aeronaves *an = parse_and_validate_aeronave_line(line, err_faeron);
        if (an) gestor_aeronaves_add(g_aeroN, an);
    }

    // -------------------------------------------------------------
    // Fechar ficheiros CSV e de erros
    // -------------------------------------------------------------
    fclose(faero); fclose(fvoos); fclose(faeron);
    fclose(err_faero); fclose(err_fvoos); fclose(err_faeron);

    // Processa ficheiro de comandos

    FILE *fcmd = fopen(cmd_file, "r");
    if (!fcmd) {
        fprintf(stderr, "Erro ao abrir ficheiro de comandos: %s\n", cmd_file);
        return EXIT_FAILURE;
    }

    // PROVAVELMENTE VAI PRECISAR DE MAIS ARGUMENTOS PARA AS QUERIES

    char linha[512];
    int command_counter = 1;

    while (fgets(linha, sizeof(linha), fcmd)) {
        // Remove \n final
        linha[strcspn(linha, "\r\n")] = 0;
        if (strlen(linha) == 0) continue;

        int query_type = linha[0] - '0'; // Primeiro carácter é o número da query
        char output_file[256];
        snprintf(output_file, sizeof(output_file), RESULT_DIR"/command%d_output.txt", command_counter++);

        // ----- Aqui está o if das queries -----
        if (query_type == 1) {
            query1(linha + 2, output_file); // poucos argumentos, nao?
        } else if (query_type == 2) {
            query2(linha + 2, output_file);
        } else if (query_type == 3) {
            query3(linha + 2, output_file);
        }
        // --------------------------------------
    }

    fclose(fcmd);


    return 0;
}
