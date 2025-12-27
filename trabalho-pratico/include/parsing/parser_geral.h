#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser_aeronaves.h"
#include "parser_aeroportos.h"
#include "parser_voos.h"
#include "parser_reservas.h"
#include "parser_passageiros.h"
#include "parser_utils.h"
#include "gestor_aeroportos.h"
#include "gestor_aeronaves.h"
#include "gestor_voos.h"

// Parser geral para ficheiros CSV
void processar_ficheiro(FILE *f, FuncaoParser funcao_parser, FuncaoAddGestor funcao_add, void *gestor1, void *gestor2, void *gestor3, FILE *err_file);


void action_add_aeroporto(void *ptr, void* g_aero, void* unused);
void action_add_aeronave(void *ptr, void* g_aeroN, void* unused);
void action_add_voo(void *ptr, void* array_voos, void* hash_voos);
void action_add_passageiro(void *ptr, void* unused1, void* unused2);
void action_add_reserva(void *ptr, void* g_res, void* unused, void *ga);