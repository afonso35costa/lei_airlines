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
#include "gestor_reservas.h"
#include "queries.h"

// Parser geral para ficheiros CSV

void processar_ficheiro(FILE *f, FuncaoParser funcao_parser, FuncaoAddGestor funcao_add, void *gestor1, void *gestor2, void *gestor3, void *gestor4,  FILE *err_file) {

    char *line = NULL;
    size_t len = 0;

    while (getline(&line, &len, f) != -1) {

        size_t n = strlen(line);
        if (n > 0 && line[n - 1] == '\n')
            line[n - 1] = '\0';

        void *obj = funcao_parser(line, err_file);

        if (obj)
            funcao_add(obj, gestor1, gestor2, gestor3, gestor4);
    }

    free(line);
}


void action_add_aeroporto(void *ptr, void* g_aero, void* unused1, void* unused2, void* unused3) {
    (void) unused1;
    (void) unused2;
    (void) unused3;
    Aeroportos *a = ptr;
    GestorAeroportos *gestor = g_aero;
    if (a) gestor_aeroportos_add(gestor, a);
}

void action_add_aeronave(void *ptr, void* g_aeroN, void* unused1, void* unused2, void* unused3) {
    (void) unused1;
    (void) unused2;
    (void) unused3;
    Aeronaves *a = ptr;
    GestorAeronaves *gestor = g_aeroN;
    if (a) {
        gestor_aeronaves_add(gestor, a);
    }
}

void action_add_voo(void *ptr, void* array_voos, void* hash_voos, void*unused, void* unused2) {
    (void) unused;
    (void) unused2;
    Voo *v = ptr;
    ArrayVoos *gestor_array = array_voos;
    HashVoos *gestor_hash = hash_voos;
    if (v) {
        array_voos_add(gestor_array, v);
        hash_voos_add(gestor_hash, v);
    }
}

void action_add_passageiro(void *ptr, void* hash, void* gestor1, void* hash_voos, void *gestor2) {
    HashAeroportosPassageiro *hash_ap = hash;
    GestorAeroportos *ga = gestor1;
    HashVoos *hv = hash_voos;
    HashReservas *hr = gestor2;
    Passageiros *p = ptr;
    verifica_passageiros(p, hash_ap, ga, hr, hv);
    destroy_passageiro(p);
}

void action_add_reserva(void *ptr, void* g_res, void* hash_voos, void *ga, void *hash_res) {
    Reservas *r = ptr;
    GestorReservas *gestor = g_res;
    HashReservas *hash_reservas = hash_res;
    HashVoos *hash = hash_voos;
    GestorAeroportos *g_aero = ga;
    if (r) {
        gestor_reservas_add(gestor, r);
        hash_reservas_add(hash_reservas, r);
        checka_reservas(r, hash, g_aero);
    }
}

