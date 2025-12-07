#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser_aeronaves.h"
#include "parser_aeroportos.h"
#include "parser_voos.h"
#include "parser_passageiros.h"
#include "parser_reservas.h"
#include "parser_utils.h"
#include "gestor_aeroportos.h"
#include "gestor_aeronaves.h"
#include "gestor_voos.h"

// Parser geral para ficheiros CSV

void processar_ficheiro(FILE *f, FuncaoParser funcao_parser, FuncaoAddGestor funcao_add, void *gestor, FILE *err_file) {

    char *line = NULL;
    size_t len = 0;

    while (getline(&line, &len, f) != -1) {

        size_t n = strlen(line);
        if (n > 0 && line[n - 1] == '\n')
            line[n - 1] = '\0';

        void *obj = funcao_parser(line, err_file);

        if (obj)
            funcao_add(obj, gestor);
    }

    free(line);
}


void action_add_aeroporto(void *ptr, void* g_aero) {
    Aeroportos *a = ptr;
    GestorAeroportos *gestor = g_aero;
    gestor_aeroportos_add(gestor, a);
}

void action_add_aeronave(void *ptr, void* g_aeroN) {
    Aeronaves *a = ptr;
    GestorAeronaves *gestor = g_aeroN;
    gestor_aeronaves_add(gestor, a);
}

void action_add_voo(void *ptr, void* g_voos) {
    Voo *v = ptr;
    GestorVoos *gestor = g_voos;
    gestor_voos_add(gestor, v);
}

void action_add_passageiro(void *ptr) {
    Passageiros *p = ptr;
    destroy_passageiro(p);
}

void action_add_reserva(void *ptr) {
    Reservas *r = ptr;
    destroy_reserva(r);
}