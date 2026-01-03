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
#include "validacao_aeroportos.h"



#define MAX_LINE 1024

int main(int argc, char *argv[]) {
    
    // Verificar que não recebe argumentos 
    if (argc != 1) {
        fprintf(stderr, "Uso: %s (sem argumentos)\n", argv[0]);
        return 1;
    }

    char csv_path[512];
    
    
    // Pedir ao utilizador o caminho dos ficheiros CSV
        printf("Introduza o caminho dos ficheiros de dados: ");
    if (fgets(csv_path, sizeof(csv_path), stdin) == NULL) {
        strcpy(csv_path, "dataset-fase-2/com_erros");
    }
    
    // Remover newline
    size_t len = strlen(csv_path);
    if (len > 0 && csv_path[len-1] == '\n') {
        csv_path[len-1] = '\0';
    }
    
    // Se vazio, usar default
    if (strlen(csv_path) == 0) {
        strcpy(csv_path, "dataset-fase-2/com_erros");
    }
    
    printf("Dataset carregado...\n");

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
    size_t len_line = 0;

    if (getline(&line, &len_line, faero) != -1) fprintf(err_faero, "%s", line);
    if (getline(&line, &len_line, fvoos) != -1) fprintf(err_fvoos, "%s", line);
    if (getline(&line, &len_line, faeron) != -1) fprintf(err_faeron, "%s", line);
    if (getline(&line, &len_line, fpass) != -1) fprintf(err_fpass, "%s", line);
    if (getline(&line, &len_line, fres) != -1) fprintf(err_fres, "%s", line);

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


    
    // Loop interativo para receber queries do utilizador

    
    char query_type[10];
    
    while (1) {
        
        // Perguntar que query executar
       
        printf("\nQue query deseja executar? ");
        
        if (fgets(query_type, sizeof(query_type), stdin) == NULL) {
            break;
        }
        
        // Remover newline
        size_t qt_len = strlen(query_type);
        if (qt_len > 0 && query_type[qt_len-1] == '\n') {
            query_type[qt_len-1] = '\0';
        }
        
        // Verificar comandos especiais
        if (strcmp(query_type, "0") == 0 || strcmp(query_type, "exit") == 0 || strcmp(query_type, "quit") == 0) {
            printf("A sair...\n");
            break;
        }
        
        if (strcmp(query_type, "r") == 0 || strcmp(query_type, "R") == 0 || strcmp(query_type, "reset") == 0) {
            printf("RESET\n");
            continue;
        }

        FILE *fout = stdout;


        // Execução das queries

        //  QUERY 1

         if (strcmp(query_type, "1") == 0 || strcmp(query_type, "1S") == 0) {
            char arg1[256];
            printf("Código do aeroporto: ");
            if (fgets(arg1, sizeof(arg1), stdin) == NULL) continue;
            arg1[strcspn(arg1, "\n")] = '\0';  // Remover newline
            
            if (!validar_code_aeroporto(arg1)) {  
                printf("Código de aeroporto inválido. Introduza um novo com 3 letras maiúsculas.\n");
                continue;
        }

            printf("Output: ");
            escreve_aeroporto1(query1(g_aero, arg1), fout, query_type);
        }



        // QUERY 2

        else if (strcmp(query_type, "2") == 0 || strcmp(query_type, "2S") == 0) {
            char arg1[256], arg2[256];
            printf("Número de aeronaves (N): ");
            if (fgets(arg1, sizeof(arg1), stdin) == NULL) continue;
            arg1[strcspn(arg1, "\n")] = '\0';

            int n = atoi(arg1);

            printf("Fabricante (opcional, Enter para todos): ");
            if (fgets(arg2, sizeof(arg2), stdin) == NULL) continue;
            arg2[strcspn(arg2, "\n")] = '\0';
            

            printf("Output: \n");
            if (strlen(arg2) > 0) {
                escreve_aeronaves(query2(stats_list, n, arg2), n, fout, query_type);
            } else {
                escreve_aeronaves(query2(stats_list, n, NULL), n, fout, query_type);
            }
        }

        // QUERY 3

        else if (strcmp(query_type, "3") == 0 || strcmp(query_type, "3S") == 0) {
            char arg1[256], arg2[256];
            printf("Data inicial (aaaa-mm-dd): ");
            if (fgets(arg1, sizeof(arg1), stdin) == NULL) continue;
            arg1[strcspn(arg1, "\n")] = '\0';
            
            printf("Data final (aaaa-mm-dd): ");
            if (fgets(arg2, sizeof(arg2), stdin) == NULL) continue;
            arg2[strcspn(arg2, "\n")] = '\0';
            
            int data1_valida = 1, data2_valida = 1;
            for (int i = 0; i < 10; i++) {
                if (i != 4 && i != 7) {
                    if (arg1[i] < '0' || arg1[i] > '9') data1_valida = 0;
                    if (arg2[i] < '0' || arg2[i] > '9') data2_valida = 0;
                }
            }
            
            if (!data1_valida) {
                printf("Data inicial contém caracteres inválidos.\n");
                continue;
            }
            if (!data2_valida) {
                printf("Data final contém caracteres inválidos.\n");
                continue;
            }
            
            // Validar intervalos básicos (ano, mês, dia)
            int ano1 = atoi(arg1);
            int mes1 = atoi(arg1 + 5);
            int dia1 = atoi(arg1 + 8);
            
            int ano2 = atoi(arg2);
            int mes2 = atoi(arg2 + 5);
            int dia2 = atoi(arg2 + 8);
            
            if (mes1 < 1 || mes1 > 12 || dia1 < 1 || dia1 > 31) {
                printf("Data inicial inválida.\n");
                continue;
            }
            if (mes2 < 1 || mes2 > 12 || dia2 < 1 || dia2 > 31) {
                printf("Data final inválida.\n");
                continue;
            }
            
            // Validar data inicial <= data final
            if (ano1 > ano2 || (ano1 == ano2 && mes1 > mes2) || 
                (ano1 == ano2 && mes1 == mes2 && dia1 > dia2)) {
                printf("Data inicial tem de ser anterior à data final.\n");
                continue;
            }
            printf("Output: ");
            percorre_voos_aeroportos(array_voos, g_aero, arg1, arg2);
            escreve_aeroporto3(query3(g_aero), fout, query_type);
        }

        // QUERY 5

        else if (strcmp(query_type, "5") == 0 || strcmp(query_type, "5S") == 0) {
            char arg1[256];
            printf("Número de companhias (N): ");
            if (fgets(arg1, sizeof(arg1), stdin) == NULL) continue;
            arg1[strcspn(arg1, "\n")] = '\0';

            int n = atoi(arg1);
            
            printf("Output: \n");
            escreve_tempos5(query5(tempo_medio, n), n, fout, query_type);
        }
        

        // QUERY 6

        else if (strcmp(query_type, "6") == 0 || strcmp(query_type, "6S") == 0) {
            char arg1[256], arg2[256], arg3[256], arg4[256], arg5[256], arg6[256], arg7[256], arg8[256];
            arg1[0] = arg2[0] = arg3[0] = arg4[0] = arg5[0] = arg6[0] = arg7[0] = arg8[0] = '\0';
            
            printf("Nacionalidade: ");
            char input_line[1024];
            fgets(input_line, sizeof(input_line), stdin);
            input_line[strcspn(input_line, "\n")] = '\0';
            
            
            
            // Parsing da linha
            int n_args = sscanf(input_line, "%255s %255s %255s %255s %255s %255s %255s %255s", 
                               arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
            
            
            // ✅ VALIDAÇÃO: Máximo 8 argumentos
            if (n_args > 8 || n_args <= 0) {
                printf("❌ ERRO: Nacionalidade deve ter entre 1 e 8 palavras.\n");
                continue;
            }
            
            // DEBUG: Testar query6 diretamente
            void *resultado_q6 = (n_args == 1) ? query6(aero_pass, arg1) : NULL;
            if (n_args == 1) {
                printf("%s\n", resultado_q6 ? "algo" : "NULL");
            }
            
            printf("Output: ");
            
            // Executar query (IGUAL ao main.c)
            if (n_args == 1) {
                escreve_aeroporto6(resultado_q6, fout, query_type);
            }
            else if (n_args == 2) {
                char combined_arg[512];
                snprintf(combined_arg, sizeof(combined_arg), "%s %s", arg1, arg2);
                escreve_aeroporto6(query6(aero_pass, combined_arg), fout, query_type);
            }
            else if (n_args == 3) {
                char combined_arg[768];
                snprintf(combined_arg, sizeof(combined_arg), "%s %s %s", arg1, arg2, arg3);
                escreve_aeroporto6(query6(aero_pass, combined_arg), fout, query_type);
            }
            else if (n_args == 4) {
                char combined_arg[1024];
                snprintf(combined_arg, sizeof(combined_arg), "%s %s %s %s", arg1, arg2, arg3, arg4);
                escreve_aeroporto6(query6(aero_pass, combined_arg), fout, query_type);
            }
            else if (n_args == 5) {
                char combined_arg[1280];
                snprintf(combined_arg, sizeof(combined_arg), "%s %s %s %s %s", arg1, arg2, arg3, arg4, arg5);
                escreve_aeroporto6(query6(aero_pass, combined_arg), fout, query_type);
            }
            else if (n_args == 6) {
                char combined_arg[1536];
                snprintf(combined_arg, sizeof(combined_arg), "%s %s %s %s %s %s", arg1, arg2, arg3, arg4, arg5, arg6);
                escreve_aeroporto6(query6(aero_pass, combined_arg), fout, query_type);
            }
            else if (n_args == 7) {
                char combined_arg[1792];
                snprintf(combined_arg, sizeof(combined_arg), "%s %s %s %s %s %s %s", arg1, arg2, arg3, arg4, arg5, arg6, arg7);
                escreve_aeroporto6(query6(aero_pass, combined_arg), fout, query_type);
            }
            else if (n_args == 8) {
                char combined_arg[2048];
                snprintf(combined_arg, sizeof(combined_arg), "%s %s %s %s %s %s %s %s", arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
                escreve_aeroporto6(query6(aero_pass, combined_arg), fout, query_type);
            }
        }
        
        // Query não reconhecida
        else {
            printf("Query não implementada ou inválida\n");
            printf("Pressione: 0 (sair), r (reset) ou outra query válida.\n");
        }
    }

    // Libertação de memória
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

//         else if (strcmp(query_type, "6") == 0 || strcmp(query_type, "6S") == 0) {
            
//             printf("Nacionalidade: ");
//             char input_line[256];
//             if (fgets(arg1, sizeof(arg1), stdin) == NULL) continue;
//             arg1[strcspn(arg1, "\n")] = '\0';
            

//             int n_args = sscanf(input_line, "%s %s %s %s %s %s %s %s", 
//                                arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
            
//             // Validação do máximo 8 argumentos (palavras)
//             if (n_args > 8 || n_args == 0) {
//                 printf("Nacionalidade tem de ter entre 1 e 8 palavras.\n");
//                 continue;
//             }
            
//             printf("Output: ");
            
//             // Executar query consoante número de argumentos 
//             if (n_args == 1) {
//                 escreve_aeroporto6(query6(aero_pass, arg1), fout, query_type);
//             }
//             else if (n_args == 2) {
//                 char combined_arg[512];
//                 snprintf(combined_arg, sizeof(combined_arg), "%s %s", arg1, arg2);
//                 escreve_aeroporto6(query6(aero_pass, combined_arg), fout, query_type);
//             }
//             else if (n_args == 3) {
//                 char combined_arg[768];
//                 snprintf(combined_arg, sizeof(combined_arg), "%s %s %s", arg1, arg2, arg3);
//                 escreve_aeroporto6(query6(aero_pass, combined_arg), fout, query_type);
//             }
            
//             else if (n_args == 4) {
//                 char combined_arg[1024];
//                 snprintf(combined_arg, sizeof(combined_arg), "%s %s %s %s", arg1, arg2, arg3, arg4);
//                 escreve_aeroporto6(query6(aero_pass, combined_arg), fout, query_type);
//             }
//             else if (n_args == 5) {
//                 char combined_arg[1280];
//                 snprintf(combined_arg, sizeof(combined_arg), "%s %s %s %s %s", arg1, arg2, arg3, arg4, arg5);
//                 escreve_aeroporto6(query6(aero_pass, combined_arg), fout, query_type);
//             }
//             else if (n_args == 6) {
//                 char combined_arg[1536];
//                 snprintf(combined_arg, sizeof(combined_arg), "%s %s %s %s %s %s", arg1, arg2, arg3, arg4, arg5, arg6);
//                 escreve_aeroporto6(query6(aero_pass, combined_arg), fout, query_type);
//             }
//             else if (n_args == 7) {
//                 char combined_arg[1792];
//                 snprintf(combined_arg, sizeof(combined_arg), "%s %s %s %s %s %s %s", arg1, arg2, arg3, arg4, arg5, arg6, arg7);
//                 escreve_aeroporto6(query6(aero_pass, combined_arg), fout, query_type);
//             }
//             else if (n_args == 8) {
//                 char combined_arg[2048];
//                 snprintf(combined_arg, sizeof(combined_arg), "%s %s %s %s %s %s %s %s", arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
//                 escreve_aeroporto6(query6(aero_pass, combined_arg), fout, query_type);
//             }
//         }
        
        
//         // Query não reconhecida
//         else {
//             printf("Query não implementada ou inválida\n ");
//             printf("Pressione: 0 (sair), r (reset) ou outra query válida.\n");
//         }
//     }

//     //  LIBERTAÇÃO MEMÓRIA 
//     gestor_aeroportos_free(g_aero);
//     g_list_free(stats_list);
//     g_list_free(tempo_medio);
//     gestor_aeronaves_free(g_aeroN);
//     hash_voos_free(hash_voos);
//     array_voos_free(array_voos);
//     hash_aero_pass_free(aero_pass);
//     hash_reservas_free(hash_reservas);
//     hash_passageiros_free(hash_passageiros);
//     free(line);

//     printf("DEBUG: programa terminado\n");

//     return 0;
// }