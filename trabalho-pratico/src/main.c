#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aeroportos.h"
#include "voos.h"
#include "aeronaves.h"
#include "parser_aeroportos.h"
#include "parser_voos.h"
#include "parser_aeronaves.h"
#include "gestor_aeroportos.h"
#include "gestor_voos.h"
#include "gestor_aeronaves.h"

#define MAX_LINE 1024

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <caminho_csv> <ficheiro_queries>\n", argv[0]);
        return 1;
    }

    char *csv_path = argv[1];
    char *commands_file = argv[2];

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

    // ------------------------- EXECUÇÃO QUERIES -------------------------
    FILE *f = fopen(commands_file, "r");
    if (!f) { perror("Erro ao abrir ficheiro de comandos"); return 1; }

    int command_count = 0;
    while (fgets(line, sizeof(line), f)) {
        if (strlen(line) <= 1) continue;
        command_count++;
        char output_path[MAX_LINE];
        snprintf(output_path, MAX_LINE, "resultados/command%d_output.txt", command_count);

        FILE *fout = fopen(output_path, "w");
        if (!fout) { perror("Erro ao criar output"); continue; }

        int query_type;
        char arg1[256], arg2[256];
        arg1[0] = arg2[0] = '\0';

        int n_args = sscanf(line, "%d %s %s", &query_type, arg1, arg2);

        // Escolha da query
        if (query_type == 1) {
            query1(g_aero, arg1, fout);
        } else if (query_type == 2) {
            if (n_args == 2) query2(g_aero, g_voos, atoi(arg1), NULL, fout);
            else query2(g_aero, g_voos, atoi(arg1), arg2, fout);
        } else if (query_type == 3) {
            if (n_args == 3) query3(g_aero, g_voos, arg1, arg2, fout);
        }

        fclose(fout);

    }
    fclose(f);

    // ------------------------- LIBERTAÇÃO MEMÓRIA -------------------------
    gestor_aeroportos_free(g_aero);
    gestor_aeronaves_free(g_aeroN);
    gestor_voos_free(g_voos);

    return 0;
}
