#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aeroportos.h"
#include "voos.h"
#include "aeronaves.h"
#include "passageiros.h"
#include "reservas.h"
#include "parser_aeroportos.h"
#include "parser_voos.h"
#include "parser_aeronaves.h"
#include "parser_passageiros.h"
#include "parser_reservas.h"
#include "gestor_aeroportos.h"
#include "gestor_voos.h"
#include "gestor_aeronaves.h"


#define MAX_LINE 1024


int main(int argc, char *argv[]) {

    if (argc != 3) {
        fprintf(stderr, "Uso: %s <caminho_csv> <ficheiro_queries>\n", argv[0]);
        return 1;
    }



    printf("DEBUG: programa iniciado\n");




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
    char path_aero[512], path_voos[512], path_aeron[512], path_pass[512], path_res[512];
    char err_aero[512], err_voos[512], err_aeron[512], err_pass[512], err_res[512];

    snprintf(path_aero, sizeof(path_aero), "%s/airports.csv", csv_path);
    snprintf(path_voos, sizeof(path_voos), "%s/flights.csv", csv_path);
    snprintf(path_aeron, sizeof(path_aeron), "%s/aircrafts.csv", csv_path);
    snprintf(path_pass, sizeof(path_pass), "%s/passengers.csv", csv_path);
    snprintf(path_res, sizeof(path_res), "%s/reservations.csv", csv_path);

    snprintf(err_aero, sizeof(err_aero), "resultados/airports_errors.csv");
    snprintf(err_voos, sizeof(err_voos), "resultados/flights_errors.csv");
    snprintf(err_aeron, sizeof(err_aeron), "resultados/aircrafts_errors.csv");
    snprintf(err_pass, sizeof(err_pass), "resultados/passengers_errors.csv");
    snprintf(err_res, sizeof(err_res), "resultados/reservations_errors.csv");

    FILE *faero = fopen(path_aero, "r");
    if (!faero) perror(path_aero);

    FILE *fvoos = fopen(path_voos, "r");
    if (!fvoos) perror(path_voos);

    FILE *faeron = fopen(path_aeron, "r");
    if (!faeron) perror(path_aeron);

    FILE *fpass = fopen(path_pass, "r");
    if (!fpass) perror(path_pass);

    FILE *fres = fopen(path_res, "r");
    if (!fres) perror(path_res);

    FILE *err_faero = fopen(err_aero, "w");
    if (!err_faero) perror(err_aero);

    FILE *err_fvoos = fopen(err_voos, "w");
    if (!err_fvoos) perror(err_voos);

    FILE *err_faeron = fopen(err_aeron, "w");
    if (!err_faeron) perror(err_aeron);

    FILE *err_fpass = fopen(err_pass, "w");
    if (!err_fpass) perror(err_pass);

    FILE *err_fres = fopen(err_res, "w");
    if (!err_fres) perror(err_res);

    if (!faero || !fvoos || !faeron || !fpass || !fres || !err_faero || !err_fvoos || !err_faeron || !err_fpass || !err_fres) {
    fprintf(stderr, "Erro ao abrir ficheiros.\n");
    return 1;
}

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
    while (getline(&line, &len, faero) != -1) {
        // Remove newline no fim, se existir
        size_t nread = strlen(line);
        if (nread > 0 && line[nread - 1] == '\n') {
            line[nread - 1] = '\0';
        }

        Aeroportos *a = parse_and_validate_aeroporto_line(line, err_faero);

        //Aeroportos validados
        
        if (a) {
            gestor_aeroportos_add(g_aero, a);
        }

        //Aeroportos adicionados
    }

    printf("DEBUG: aeroportos processados\n");

    // -------------------------------------------------------------
    // Processar voos
    // -------------------------------------------------------------
    while (getline(&line, &len, fvoos) != -1) {
        // Remove newline no fim, se existir
        size_t nread = strlen(line);
        if (nread > 0 && line[nread - 1] == '\n') {
            line[nread - 1] = '\0';
        }

        Voo *a = parse_and_validate_voo_line(line, err_fvoos);

        //Voos validados

        if (a) {
            gestor_voos_add(g_voos, a);
        }

        //Voos adicionados
    }


    printf("DEBUG: voos processados\n");


    // -------------------------------------------------------------
    // Processar aeronaves
    // -------------------------------------------------------------
    while (getline(&line, &len, faeron) != -1) {
        // Remove newline no fim, se existir
        size_t nread = strlen(line);
        if (nread > 0 && line[nread - 1] == '\n') {
            line[nread - 1] = '\0';
        }

        Aeronaves *a = parse_and_validate_aeronave_line(line, err_faeron);
        //Aeronaves validadas

        if (a) {
            gestor_aeronaves_add(g_aeroN, a);
        }

        //Aeronaves adicionadas
    }

    printf("DEBUG: aeronaves processadas\n");

    // -------------------------------------------------------------
    // Processar passageiros
    // -------------------------------------------------------------
    while (getline(&line, &len, fpass) != -1) {
        // Remove newline no fim, se existir
        size_t nread = strlen(line);
        if (nread > 0 && line[nread - 1] == '\n') {
            line[nread - 1] = '\0';
        }

        Passageiros *p = parse_and_validate_passageiro_line(line, err_fpass);
    }
    
    printf("DEBUG: passageiros processados\n");

    // -------------------------------------------------------------
    // Processar reservas
    // -------------------------------------------------------------
    while (getline(&line, &len, fres) != -1) {
        // Remove newline no fim, se existir
        size_t nread = strlen(line);
        if (nread > 0 && line[nread - 1] == '\n') {
            line[nread - 1] = '\0';
        }

        Reservas *r = parse_and_validate_reserva_line(line, err_fres);
    }

    printf("DEBUG: reservas processadas\n");

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
    while (getline(&line, &len, f) != -1) {   // linha anterior while (fgets(&line, &len, f) != -1)
        if (strlen(line) <= 1) continue;
        command_count++;
        char output_path[MAX_LINE];

        printf("CHEGUEI\n");

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
            if (n_args == 2) query2(g_aeroN, g_voos, atoi(arg1), NULL, fout);
            else query2(g_aeroN, g_voos, atoi(arg1), arg2, fout);
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
    free(line);

    printf("DEBUG: programa terminado\n");

    return 0;
}



