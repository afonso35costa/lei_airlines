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
#include "gestor_reservas.h"
#include "gestor_passageiros.h"
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
    ArrayVoos *array_voos = array_voos_create();
    HashVoos *hash_voos = hash_voos_create();
    GestorAeronaves *g_aeroN = gestor_aeronaves_create();
    HashAeroportosPassageiro *aero_pass = hash_aero_pass_create();
    HashReservas *hash_reservas = hash_reservas_create();
    HashPassageiros *hash_passageiros = hash_passageiros_create();


    // -------------------------------------------------------------
    // Abrir ficheiros CSV e ficheiros de erro
    // -------------------------------------------------------------

    FILE *faero = abrir_ficheiro_leitura(csv_path, "airports.csv");
    FILE *fvoos = abrir_ficheiro_leitura(csv_path, "flights.csv");
    FILE *faeron = abrir_ficheiro_leitura(csv_path, "aircrafts.csv");
    FILE *fpass = abrir_ficheiro_leitura(csv_path, "passengers.csv");
    FILE *fres = abrir_ficheiro_leitura(csv_path, "reservations.csv");

    FILE *err_faero = abrir_ficheiro_escrita("resultados/airports_errors.csv");
    FILE *err_fvoos = abrir_ficheiro_escrita("resultados/flights_errors.csv");
    FILE *err_faeron = abrir_ficheiro_escrita("resultados/aircrafts_errors.csv");
    FILE *err_fpass = abrir_ficheiro_escrita("resultados/passengers_errors.csv");
    FILE *err_fres = abrir_ficheiro_escrita("resultados/reservations_errors.csv");

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

    processar_ficheiro(faero, (FuncaoParser) parse_and_validate_aeroporto_line, action_add_aeroporto, g_aero, NULL, NULL, NULL, NULL, err_faero);
    processar_ficheiro(faeron, (FuncaoParser) parse_and_validate_aeronave_line, action_add_aeronave, g_aeroN, NULL, NULL, NULL, NULL, err_faeron);
    processar_ficheiro(fvoos, (FuncaoParser) parse_and_validate_voo_line, action_add_voo, array_voos, hash_voos, g_aeroN, NULL, NULL, err_fvoos);
    processar_ficheiro(fpass, (FuncaoParser) parse_and_validate_passageiro_line, action_add_passageiro, NULL, hash_passageiros, NULL, NULL, NULL, err_fpass);
    processar_ficheiro(fres, (FuncaoParser) parse_and_validate_reserva_line, action_add_reserva, hash_passageiros, hash_voos, g_aero, hash_reservas, aero_pass, err_fres);

    percorre_voos_aeronaves(array_voos, g_aeroN);
    GList *stats_list = ordena_aeronaves(g_aeroN);
    GList *tempo_medio = ordena_tempo_medio(conta_tempo(array_voos));

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

        char output_path[MAX_LINE];
        snprintf(output_path, MAX_LINE, "resultados/command%d_output.txt", command_count);

        FILE *fout = fopen(output_path, "w");
        if (!fout) { perror("Erro ao criar output"); continue; }

        // --- Interpretar query ---
        char query_type[10];
        char arg1[256], arg2[256], arg3[256], arg4[256], arg5[256], arg6[256], arg7[256], arg8[256];
        arg1[0] = arg2[0] = arg3[0] = arg4[0] = arg5[0] = arg6[0] = arg7[0] = arg8[0] = '\0';

        int n_args = sscanf(line, "%s %s %s %s %s %s %s %s %s", query_type, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);

        // -------------------------
        // Execução das queries
        // -------------------------

        //  QUERY 1

        if (strcmp(query_type, "1S") == 0 || strcmp(query_type, "1") == 0) {
            if (n_args >= 2) escreve_aeroporto1(query1(g_aero, arg1), fout, query_type);
        }

        // QUERY 2

        else if (strcmp(query_type, "2") == 0 || strcmp(query_type, "2S") == 0) {
            if (n_args == 2) {
                escreve_aeronaves(query2(stats_list, atoi(arg1), NULL), atoi(arg1), fout, query_type);
            } else if (n_args == 3) {
                escreve_aeronaves(query2(stats_list, atoi(arg1), arg2), atoi(arg1), fout, query_type);
            }
            else {
                fprintf(fout, "\n");
            }
        }

        // QUERY 3

        else if (strcmp(query_type, "3") == 0 || strcmp(query_type, "3S") == 0) {
            if (n_args == 3) {
                percorre_voos_aeroportos(array_voos, g_aero, arg1, arg2);
                escreve_aeroporto3(query3(g_aero), fout, query_type);
            }
        }

        // QUERY 5

        else if (strcmp(query_type, "5") == 0 || strcmp(query_type, "5S") == 0) {
            if (n_args == 2) {
                escreve_tempos5(query5(tempo_medio, atoi(arg1)), atoi(arg1), fout, query_type);
            }
        }

        // QUERY 6

        else if (strcmp(query_type, "6") == 0 || strcmp(query_type, "6S") == 0) {
            if (n_args == 2) {
                escreve_aeroporto6(query6(aero_pass, arg1), fout, query_type);
            }
            else if (n_args == 3) {
                char combined_arg[512];
                snprintf(combined_arg, sizeof(combined_arg), "%s %s", arg1, arg2);
                escreve_aeroporto6(query6(aero_pass, combined_arg), fout, query_type);
            }
            else if (n_args == 4) {
                char combined_arg[768];
                snprintf(combined_arg, sizeof(combined_arg), "%s %s %s", arg1, arg2, arg3);
                escreve_aeroporto6(query6(aero_pass, combined_arg), fout, query_type);
            }
            else if (n_args == 5) {
                char combined_arg[1024];
                snprintf(combined_arg, sizeof(combined_arg), "%s %s %s %s", arg1, arg2, arg3, arg4);
                escreve_aeroporto6(query6(aero_pass, combined_arg), fout, query_type);
            }
            else if (n_args == 6) {
                char combined_arg[1280];
                snprintf(combined_arg, sizeof(combined_arg), "%s %s %s %s %s", arg1, arg2, arg3, arg4, arg5);
                escreve_aeroporto6(query6(aero_pass, combined_arg), fout, query_type);
            }
            else if (n_args == 7) {
                char combined_arg[1536];
                snprintf(combined_arg, sizeof(combined_arg), "%s %s %s %s %s %s", arg1, arg2, arg3, arg4, arg5, arg6);
                escreve_aeroporto6(query6(aero_pass, combined_arg), fout, query_type);
            }
            else if (n_args == 8) {
                char combined_arg[1792];
                snprintf(combined_arg, sizeof(combined_arg), "%s %s %s %s %s %s %s", arg1, arg2, arg3, arg4, arg5, arg6, arg7);
                escreve_aeroporto6(query6(aero_pass, combined_arg), fout, query_type);
            }
            else if (n_args == 9) {
                char combined_arg[2048];
                snprintf(combined_arg, sizeof(combined_arg), "%s %s %s %s %s %s %s %s", arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
                escreve_aeroporto6(query6(aero_pass, combined_arg), fout, query_type);
            }
            else {
                fprintf(fout, "\n");
            }
        fclose(fout);
        }
    }
    fclose(f);
    printf("DEBUG: queries terminadas\n");

    // ------------------------- LIBERTAÇÃO MEMÓRIA -------------------------
    gestor_aeroportos_free(g_aero);
    g_list_free(stats_list);
    g_list_free(tempo_medio);
    gestor_aeronaves_free(g_aeroN);
    hash_voos_free(hash_voos);
    array_voos_free(array_voos);
    hash_aero_pass_free(aero_pass);
    hash_reservas_free(hash_reservas);
    hash_passageiros_free(hash_passageiros);
    free(line);

    printf("DEBUG: programa terminado\n");

    return 0;
}



