#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/resource.h>
#include "aeroportos.h"
#include "aeronaves.h"
#include "voos.h"
#include "gestor_aeroportos.h"
#include "gestor_aeronaves.h"
#include "gestor_voos.h"
#include "queries.h"

#define MAX_LINE 1024

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Uso: %s <csv_folder> <commands_file> <expected_output_folder>\n", argv[0]);
        return 1;
    }

    const char *csv_folder = argv[1];
    const char *commands_file = argv[2];
    const char *expected_folder = argv[3];

    // Início medição de tempo
    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);

    // Início gestores
    GestorAeroportos *ga = gestor_aeroportos_create();
    GestorAeronaves *gar = gestor_aeronaves_create();
    GestorVoos *gv = gestor_voos_create();

    // ------------------------- PARSING CSVs -------------------------
    char path[MAX_LINE];

    // Aeroportos
    snprintf(path, MAX_LINE, "%s/airports.csv", csv_folder);
    FILE *f = fopen(path, "r");
    if (!f) { perror("Erro ao abrir airports.csv"); return 1; }
    // Cria ficheiro de erros
    snprintf(path, MAX_LINE, "resultados/aeroportos_errors.csv");
    FILE *ferr = fopen(path, "w"); if (ferr) fclose(ferr);

    char line[MAX_LINE];
    int is_header = 1;
    while (fgets(line, sizeof(line), f)) {
        Aeroportos *a = parse_and_validate_aeroporto_line(line, is_header, fopen("resultados/aeroportos_errors.csv", "a"));
        if (a) gestor_aeroportos_add(ga, a);
        is_header = 0;
    }
    fclose(f);

    // Aeronaves
    snprintf(path, MAX_LINE, "%s/aircrafts.csv", csv_folder);
    f = fopen(path, "r");
    if (!f) { perror("Erro ao abrir aircrafts.csv"); return 1; }
    snprintf(path, MAX_LINE, "resultados/aeronaves_errors.csv");
    ferr = fopen(path, "w"); if (ferr) fclose(ferr);

    is_header = 1;
    while (fgets(line, sizeof(line), f)) {
        Aeronaves *ar = parse_and_validate_aeronave_line(line, is_header, fopen("resultados/aeronaves_errors.csv", "a"));
        if (ar) gestor_aeronaves_add(gar, ar);
        is_header = 0;
    }
    fclose(f);

    // Voos
    snprintf(path, MAX_LINE, "%s/flights.csv", csv_folder);
    f = fopen(path, "r");
    if (!f) { perror("Erro ao abrir flights.csv"); return 1; }
    snprintf(path, MAX_LINE, "resultados/voos_errors.csv");
    ferr = fopen(path, "w"); if (ferr) fclose(ferr);

    is_header = 1;
    while (fgets(line, sizeof(line), f)) {
        Voo *v = parse_and_validate_voo_line(line, is_header, fopen("resultados/voos_errors.csv", "a"));
        if (v) gestor_voos_add(gv, v);
        is_header = 0;
    }
    fclose(f);

    // ------------------------- EXECUÇÃO QUERIES -------------------------
    f = fopen(commands_file, "r");
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
            query1(ga, arg1, fout);
        } else if (query_type == 2) {
            if (n_args == 2) query2(gar, gv, atoi(arg1), NULL, fout);
            else query2(gar, gv, atoi(arg1), arg2, fout);
        } else if (query_type == 3) {
            if (n_args == 3) query3(ga, gv, arg1, arg2, fout);
        }

        fclose(fout);

        // ------------------------- COMPARAÇÃO COM OUTPUT ESPERADO -------------------------
        char expected_file[MAX_LINE];
        snprintf(expected_file, MAX_LINE, "%s/command%d_output.txt", expected_folder, command_count);

        FILE *fexp = fopen(expected_file, "r");
        fout = fopen(output_path, "r");
        if (!fexp || !fout) continue;

        char line_expected[MAX_LINE], line_result[MAX_LINE];
        int line_num = 0, correct_lines = 0;
        int first_mismatch_line = -1;

        while (fgets(line_expected, sizeof(line_expected), fexp) &&
               fgets(line_result, sizeof(line_result), fout)) {
            line_num++;
            if (strcmp(line_expected, line_result) == 0) correct_lines++;
            else if (first_mismatch_line == -1) first_mismatch_line = line_num;
        }

        printf("Query %d: %d linhas corretas", command_count, correct_lines);
        if (first_mismatch_line != -1)
            printf(", primeira incongruência na linha %d", first_mismatch_line);
        printf("\n");

        fclose(fexp);
        fclose(fout);
    }
    fclose(f);

    // ------------------------- FIM MEDIÇÃO TEMPO -------------------------
    clock_gettime(CLOCK_REALTIME, &end);
    double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec)/1e9;
    printf("Tempo total de execução: %.6f segundos\n", elapsed);

    // ------------------------- MEMÓRIA -------------------------
    struct rusage r_usage;
    getrusage(RUSAGE_SELF, &r_usage);
    printf("Memória máxima usada: %ld KB\n", r_usage.ru_maxrss);

    // ------------------------- LIBERTAÇÃO MEMÓRIA -------------------------
    gestor_aeroportos_free(ga);
    gestor_aeronaves_free(gar);
    gestor_voos_free(gv);

    return 0;
}


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
    if (argc != 4) {
        fprintf(stderr, "Uso: %s <csv_folder> <commands_file> <expected_output_folder>\n", argv[0]);
        return 1;
    }

    const char *csv_folder = argv[1];
    const char *commands_file = argv[2];
    const char *expected_folder = argv[3];

    // Início medição de tempo
    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);

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
            query1(ga, arg1, fout);
        } else if (query_type == 2) {
            if (n_args == 2) query2(gar, gv, atoi(arg1), NULL, fout);
            else query2(gar, gv, atoi(arg1), arg2, fout);
        } else if (query_type == 3) {
            if (n_args == 3) query3(ga, gv, arg1, arg2, fout);
        }

        fclose(fout);

        // ------------------------- COMPARAÇÃO COM OUTPUT ESPERADO -------------------------
        char expected_file[MAX_LINE];
        snprintf(expected_file, MAX_LINE, "%s/command%d_output.txt", expected_folder, command_count);

        FILE *fexp = fopen(expected_file, "r");
        fout = fopen(output_path, "r");
        if (!fexp || !fout) continue;

        char line_expected[MAX_LINE], line_result[MAX_LINE];
        int line_num = 0, correct_lines = 0;
        int first_mismatch_line = -1;

        while (fgets(line_expected, sizeof(line_expected), fexp) &&
               fgets(line_result, sizeof(line_result), fout)) {
            line_num++;
            if (strcmp(line_expected, line_result) == 0) correct_lines++;
            else if (first_mismatch_line == -1) first_mismatch_line = line_num;
        }

        printf("Query %d: %d linhas corretas", command_count, correct_lines);
        if (first_mismatch_line != -1)
            printf(", primeira incongruência na linha %d", first_mismatch_line);
        printf("\n");

        fclose(fexp);
        fclose(fout);
    }
    fclose(f);

    // ------------------------- FIM MEDIÇÃO TEMPO -------------------------
    clock_gettime(CLOCK_REALTIME, &end);
    double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec)/1e9;
    printf("Tempo total de execução: %.6f segundos\n", elapsed);

    // ------------------------- MEMÓRIA -------------------------
    struct rusage r_usage;
    getrusage(RUSAGE_SELF, &r_usage);
    printf("Memória máxima usada: %ld KB\n", r_usage.ru_maxrss);

    // ------------------------- LIBERTAÇÃO MEMÓRIA -------------------------
    gestor_aeroportos_free(ga);
    gestor_aeronaves_free(gar);
    gestor_voos_free(gv);

    return 0;
}