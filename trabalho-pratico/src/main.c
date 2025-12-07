#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aeroportos.h"
#include "voos.h"
#include "aeronaves.h"
#include "passageiros.h"
#include "reservas.h"
#include "gestor_aeroportos.h"
#include "gestor_voos.h"
#include "gestor_aeronaves.h"
#include "queries.h"
#include "leitura.h"
#include "escrita.h"
#include "parser_geral.h"

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

    FILE *faero = abrir_ficheiro_leitura(csv_path, "airports.csv");
    FILE *fvoos = abrir_ficheiro_leitura(csv_path, "flights.csv");
    FILE *faeron = abrir_ficheiro_leitura(csv_path, "aircrafts.csv");
    FILE *fpass = abrir_ficheiro_leitura(csv_path, "passengers.csv");
    FILE *fres = abrir_ficheiro_leitura(csv_path, "reservations.csv");

    FILE *err_faero = abrir_ficheiro_escrita("resultados/airports_errors.txt");
    FILE *err_fvoos = abrir_ficheiro_escrita("resultados/flights_errors.txt");
    FILE *err_faeron = abrir_ficheiro_escrita("resultados/aircrafts_errors.txt");
    FILE *err_fpass = abrir_ficheiro_escrita("resultados/passengers_errors.txt");
    FILE *err_fres = abrir_ficheiro_escrita("resultados/reservations_errors.txt");

    // -------------------------------------------------------------
    // Ler headers e copiar para ficheiros de erro
    // -------------------------------------------------------------
    char *line = NULL;
    size_t len = 0;

    if (getline(&line, &len, faero) != -1) fprintf(err_faero, "%s", line);
    if (getline(&line, &len, fvoos) != -1) fprintf(err_fvoos, "%s", line);
    if (getline(&line, &len, faeron) != -1) fprintf(err_faeron, "%s", line);
    if (getline(&line, &len, fpass) != -1) fprintf(err_fpass, "%s", line);
    if (getline(&line, &len, fres) != -1) fprintf(err_fres, "%s", line);

    // -------------------------------------------------------------
    // Processar aeroportos
    // -------------------------------------------------------------

    processar_ficheiro(faero, (FuncaoParser) parse_and_validate_aeroporto_line, action_add_aeroporto, g_aero, err_faero);
    processar_ficheiro(fvoos, (FuncaoParser) parse_and_validate_voo_line, action_add_voo, g_voos, err_fvoos);
    processar_ficheiro(faeron, (FuncaoParser) parse_and_validate_aeronave_line, action_add_aeronave, g_aeroN, err_faeron);
    processar_ficheiro(fpass, (FuncaoParser) parse_and_validate_passageiro_line, action_add_passageiro, NULL, err_fpass);
    processar_ficheiro(fres, (FuncaoParser) parse_and_validate_reserva_line, action_add_reserva, NULL, err_fres);

    percorre_voos_aeronaves(g_voos, g_aeroN);
    GList *stats_list = ordena_tudo(g_aeroN);

    // -------------------------------------------------------------
    // Fechar ficheiros CSV e de erros
    // -------------------------------------------------------------
    fclose(faero); fclose(fvoos); fclose(faeron); fclose(fpass); fclose(fres);
    fclose(err_faero); fclose(err_fvoos); fclose(err_faeron); fclose(err_fpass); fclose(err_fres);


    // Processa ficheiro de comandos


    // ------------------------- EXECUÇÃO QUERIES -------------------------
    FILE *f = fopen(commands_file, "r");
    if (!f) { perror("Erro ao abrir ficheiro de comandos"); return 1; }

    int command_count = 0;


    while (getline(&line, &len, f) != -1) {  

        if (strlen(line) <= 1) continue;

        // Agora sim, a linha contém uma query válida
        command_count++;

        // Criar ficheiro de output desta query
        char *path_filename = "resultados/command_output.txt"; // CORRIGIR
        FILE *fout = abrir_ficheiro_escrita(path_filename);

        // --- Interpretar query ---
        int query_type;
        char arg1[256], arg2[256];
        arg1[0] = arg2[0] = '\0';

        int n_args = sscanf(line, "%d %s %s", &query_type, arg1, arg2);

        // -------------------------
        // Execução das queries
        // -------------------------
        if (query_type == 1) {
            if (n_args >= 2) escreve_aeroporto1(query1(g_aero, arg1, fout), fout);
        }
        else if (query_type == 2) {
            if (n_args == 2) {
                escreve_aeronaves(query2(stats_list, atoi(arg1), NULL, fout), atoi(arg1), fout);
            } else if (n_args == 3) {
                escreve_aeronaves(query2(stats_list, atoi(arg1), arg2, fout), atoi(arg1), fout);
            }
        }
        else if (query_type == 3) {
            if (n_args == 3) {
                percorre_voos_aeroportos(g_voos, g_aero, arg1, arg2);
                escreve_aeroporto3(query3(g_aero, fout), fout);
            }
        }
        fclose(fout);
    }

    fclose(f);
    printf("DEBUG: queries terminadas\n");

    // ------------------------- LIBERTAÇÃO MEMÓRIA -------------------------
    gestor_aeroportos_free(g_aero);
    gestor_aeronaves_free(g_aeroN);
    gestor_voos_free(g_voos);
    free(line);
    g_list_free_full(stats_list, (GDestroyNotify) free_aeronave);

    printf("DEBUG: programa terminado\n");

    return 0;
}



