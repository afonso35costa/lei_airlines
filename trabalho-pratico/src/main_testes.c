#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/resource.h>
#include "aeroportos.h"
#include "voos.h"
#include "aeronaves.h"
#include "passageiros.h"
#include "reservas.h"
#include "gestor_aeroportos.h"
#include "gestor_voos.h"
#include "gestor_aeronaves.h"
#include "gestor_reservas.h"
#include "queries.h"
#include "leitura.h"
#include "escrita.h"
#include "parser_geral.h"


#define MAX_LINE 1024


// Função para comparar dois ficheiros linha a linha


int check_results_file(const char *path_res, const char *path_exp, int query_number) {

    FILE *file_res = fopen(path_res, "r");
    if (!file_res) return 1;

    fseek(file_res, 0, SEEK_SET);

    FILE *file_exp = fopen(path_exp, "r");
    if (!file_exp) {
        fclose(file_res);
        return 1;
    }

    char *line_res = NULL;
    char *line_exp = NULL;
    size_t len_res = 0, len_exp = 0;
    ssize_t read_res, read_exp;
    int line_number = 0;

    while (1) {
        read_res = getline(&line_res, &len_res, file_res);
        read_exp = getline(&line_exp, &len_exp, file_exp);

        // EOF nos dois ficheiros
        if (read_res == -1 && read_exp == -1)
            break;

        line_number++;

        // Linhas diferentes
        if (strcmp(line_res, line_exp) != 0) {
            printf("Discrepância na query %d: linha %d de %s\n", query_number, line_number, path_res);
            fclose(file_res);
            fclose(file_exp);
            free(line_res);
            free(line_exp);
            return 1;
        }
    }

    free(line_res);
    free(line_exp);
    fclose(file_res);
    fclose(file_exp);
    return 0;
}

int main(int argc, char *argv[]) {

    struct timespec start, end;
    double parsing_time, q1_time=0, q2_time=0, q3_time=0, q5_time=0;
    double total_time;

    if (argc != 4) {
        fprintf(stderr, "Usa: %s <caminho_csv> <ficheiro_queries> <ficheiro_resultados>\n", argv[0]);
        return 1;
    }

    clock_gettime(CLOCK_REALTIME, &start);

    printf("DEBUG: programa iniciado\n");




    char *csv_path = argv[1];
    char *commands_file = argv[2];
    char *expected_results_path = argv[3];

    // -------------------------------------------------------------
    // Inicializar gestores
    // -------------------------------------------------------------
    GestorAeroportos *g_aero = gestor_aeroportos_create();
    ArrayVoos *array_voos = array_voos_create();
    HashVoos *hash_voos = hash_voos_create();
    GestorAeronaves *g_aeroN = gestor_aeronaves_create();
    GestorReservas *g_reservas = gestor_reservas_create();

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

    processar_ficheiro(faero, (FuncaoParser) parse_and_validate_aeroporto_line, action_add_aeroporto, g_aero, NULL, NULL, err_faero);
    processar_ficheiro(fvoos, (FuncaoParser) parse_and_validate_voo_line, action_add_voo, array_voos, hash_voos, NULL, err_fvoos);
    processar_ficheiro(faeron, (FuncaoParser) parse_and_validate_aeronave_line, action_add_aeronave, g_aeroN, NULL, NULL, err_faeron);
    processar_ficheiro(fpass, (FuncaoParser) parse_and_validate_passageiro_line, action_add_passageiro, NULL, NULL, NULL, err_fpass);
    processar_ficheiro(fres, (FuncaoParser) parse_and_validate_reserva_line, action_add_reserva, g_reservas, hash_voos, g_aero, err_fres);

    percorre_voos_aeronaves(array_voos, g_aeroN);
    GList *stats_list = ordena_aeronaves(g_aeroN);
    // GList *tempo_medio = ordena_tempo_medio(conta_tempo(array_voos));

    // -------------------------------------------------------------
    // Fechar ficheiros CSV e de erros
    // -------------------------------------------------------------
    fclose(faero); fclose(fvoos); fclose(faeron); fclose(fpass); fclose(fres);
    fclose(err_faero); fclose(err_fvoos); fclose(err_faeron); fclose(err_fpass); fclose(err_fres);


    // Tempo de parsing

    clock_gettime(CLOCK_REALTIME, &end);
    parsing_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;


    // ------------------------- EXECUÇÃO QUERIES -------------------------


    FILE *f = fopen(commands_file, "r");
    if (!f) { perror("Erro ao abrir ficheiro de comandos"); return 1; }

    // Número de vezes que as queries são efetuadas (Número de testes)

    int q1_count = 0;
    int q2_count = 0;
    int q3_count = 0;
    int q5_count = 0;

    // Número de fails por query
    int q1_fail = 0;
    int q2_fail = 0;
    int q3_fail = 0;
    int q5_fail = 0;

    int command_count = 0;

    while (getline(&line, &len, f) != -1) { 
        if (strlen(line) <= 1) continue; // Ignorar header
        command_count++;

        char output_path[MAX_LINE];
        snprintf(output_path, MAX_LINE, "resultados/command%d_output.txt", command_count);

        char results_path[MAX_LINE];
        snprintf(results_path, MAX_LINE, "%s/command%d_output.txt", expected_results_path, command_count);

        FILE *fout = fopen(output_path, "w");
        if (!fout) { perror("Erro ao criar output"); continue; }

        char query_type[10];
        char arg1[256], arg2[256];
        arg1[0] = arg2[0] = '\0';

        int n_args = sscanf(line, "%s %s %s", query_type, arg1, arg2);


        // Escolha da query 1
        if (strcmp(query_type, "1") == 0 || strcmp(query_type, "1S") == 0) {
            q1_count++;
            clock_gettime(CLOCK_REALTIME, &start);
            escreve_aeroporto1(query1(g_aero, arg1), fout, query_type);
            fclose(fout);
        // Se os ficheiro de resultados que a query criou for diferente do esperado, incrementar o contador de fails
            if (check_results_file(output_path, results_path, command_count) != 0) q1_fail++;
            clock_gettime(CLOCK_REALTIME, &end);
            q1_time += (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

        // Escolha da query 2  

        } else if (strcmp(query_type, "2") == 0 || strcmp(query_type, "2S") == 0) {
            q2_count++;
            clock_gettime(CLOCK_REALTIME, &start);
            if (n_args == 2) escreve_aeronaves(query2(stats_list, atoi(arg1), NULL), atoi(arg1), fout, query_type);
            else escreve_aeronaves(query2(stats_list, atoi(arg1), arg2), atoi(arg1), fout, query_type);
            fclose(fout);
        // Se os ficheiro de resultados que a query criou for diferente do esperado, incrementar o contador de fails
            if (check_results_file(output_path, results_path, command_count) != 0) q2_fail++;
            clock_gettime(CLOCK_REALTIME, &end);
            q2_time += (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

        // EScolha da query 3

        } else if (strcmp(query_type, "3") == 0 || strcmp(query_type, "3S") == 0) {
            q3_count++;
            clock_gettime(CLOCK_REALTIME, &start);
            percorre_voos_aeroportos(array_voos, g_aero, arg1, arg2);
            escreve_aeroporto3(query3(g_aero), fout, query_type);
            fclose(fout);
        // Se os ficheiro de resultados que a query criou for diferente do esperado, incrementar o contador de fails
            if (check_results_file(output_path, results_path, command_count) != 0) q3_fail++;
            clock_gettime(CLOCK_REALTIME, &end);
            q3_time += (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
        }

        /* Escolha da query 5

        else if (strcmp(query_type, "5") == 0 || strcmp(query_type, "5S") == 0) {
            q5_count++;
            clock_gettime(CLOCK_REALTIME, &start);
            if (n_args == 2) escreve_tempos5(query5(tempo_medio, atoi(arg1)), atoi(arg1), fout, query_type);
            fclose(fout);
        // Se os ficheiro de resultados que a query criou for diferente do esperado, incrementar o contador de fails
            if (check_results_file(output_path, results_path, command_count) != 0) q5_fail++;
            clock_gettime(CLOCK_REALTIME, &end);
            q5_time += (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
        } */


        else {
            fclose(fout);
        }
    }
    fclose(f);

    // ------------------------- LIBERTAÇÃO MEMÓRIA -------------------------
    gestor_aeroportos_free(g_aero);
    g_list_free(stats_list);
    // g_list_free(tempo_medio);
    gestor_aeronaves_free(g_aeroN);
    hash_voos_free(hash_voos);
    array_voos_free(array_voos);
    gestor_reservas_free(g_reservas);
    free(line);

    // Proporção de fails por query
    printf("Q1: %d de %d testes ok!\n", q1_count - q1_fail,  q1_count);
    printf("Q2: %d de %d testes ok!\n", q2_count - q2_fail,  q2_count);
    printf("Q3: %d de %d testes ok!\n", q3_count - q3_fail,  q3_count);

    // Memória utilizada
    struct rusage r_usage;
    getrusage(RUSAGE_SELF, &r_usage);
    printf("Memória utilizada: %ld KB\n", r_usage.ru_maxrss);

    // Print dos tempos
    total_time = parsing_time + q1_time + q2_time + q3_time;
    printf("Tempos de execução:\n");
    printf("\tParsing: %.6f segundos\n", parsing_time);
    printf("\tQuery 1: %.6f segundos\n", q1_time);
    printf("\tQuery 2: %.6f segundos\n", q2_time);
    printf("\tQuery 3: %.6f segundos\n", q3_time);
    printf("Tempo total: %.6f segundos\n", total_time);


    printf("DEBUG: programa terminado\n");

    return 0;
}