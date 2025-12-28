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
#include "gestor_passageiros.h"
#include "queries.h"

// Parser geral para ficheiros CSV

void processar_ficheiro(FILE *f, FuncaoParser funcao_parser, FuncaoAddGestor funcao_add, void *gestor1, void *gestor2, void *gestor3, void *gestor4, void *gestor5, FILE *err_file) {

    char *line = NULL;
    size_t len = 0;

    while (getline(&line, &len, f) != -1) {

        size_t n = strlen(line);
        if (n > 0 && line[n - 1] == '\n')
            line[n - 1] = '\0';

        void *obj = funcao_parser(line, err_file);

        if (obj)
            if (funcao_add(obj, gestor1, gestor2, gestor3, gestor4, gestor5)) {
                fprintf(err_file, "%s\n", line); // escreve a linha inválida
            }
    }

    free(line);
}


int action_add_aeroporto(void *ptr, void* g_aero, void* unused1, void* unused2, void* unused3, void* unused4) {
    (void) unused1;
    (void) unused2;
    (void) unused3;
    (void) unused4;
    Aeroportos *a = ptr;
    GestorAeroportos *gestor = g_aero;
    if (a) gestor_aeroportos_add(gestor, a);
    return 0;
}

int action_add_aeronave(void *ptr, void* g_aeroN, void* unused1, void* unused2, void* unused3, void* unused4) {
    (void) unused1;
    (void) unused2;
    (void) unused3;
    (void) unused4;
    Aeronaves *a = ptr;
    GestorAeronaves *gestor = g_aeroN;
    if (a) {
        gestor_aeronaves_add(gestor, a);
    }
    return 0;
}

int action_add_voo(void *ptr, void* array_voos, void* hash_voos, void*gestor_aeronaves, void* unused2, void* unused3) {
    (void) unused2;
    (void) unused3;
    Voo *v = ptr;
    GestorAeronaves *ga = gestor_aeronaves;
    if (v && ga) {
        char *aircraft_id = get_aircraft_voo(v);
        if (!aircraft_id || !gestor_aeronaves_get(ga, aircraft_id)) {
            destroy_voo(v);
            return 1;
        }
    }
    ArrayVoos *gestor_array = array_voos;
    HashVoos *gestor_hash = hash_voos;
    if (v) {
        array_voos_add(gestor_array, v);
        hash_voos_add(gestor_hash, v);
    }
    return 0;
}

int action_add_passageiro(void *ptr, void* hash, void* hash_pass, void* hash_voos, void *gestor2, void *unused3) {
    (void) hash_voos;
    (void) gestor2;
    (void) hash;
    (void) unused3;
    HashPassageiros *hash_passageiros = hash_pass;
    Passageiros *p = ptr;
    if (p) hash_passageiros_add(hash_passageiros, p);
    return 0;
}

int action_add_reserva(void *ptr, void* g_pass, void* hash_voos, void *ga, void *hash_res, void *aero_pass) {
    Reservas *r = ptr;
    HashAeroportosPassageiro *hap = aero_pass;
    HashPassageiros *hash_pass = g_pass;
    HashVoos *hash = hash_voos;
    HashReservas *hash_reservas = hash_res;

    if (r) {
        if (!hash_passageiros_get(hash_pass, get_document_number_reservas(r))) {
            destroy_reserva(r);
            return 1;
        }
        char **flight_ids = get_flight_ids_reservas(r);

        if (!flight_ids) {
            destroy_reserva(r);
            return 1;
        }
    
        for (int i = 0; i < get_num_flights_reserva(r); i++) {
            if (!flight_ids[i]) {  
                destroy_reserva(r);
                return 1;
            }

            if (!hash_voos_get(hash, flight_ids[i])) {
                destroy_reserva(r);
                return 1;
            }
        }
        if (get_num_flights_reserva(r) == 2){
            if (strcmp(get_destination_voo(hash_voos_get(hash, get_flight_ids_reservas(r)[0])), get_origin_voo(hash_voos_get(hash, get_flight_ids_reservas(r)[1]))) != 0) {
                destroy_reserva(r);
                return 1;
            }
        }
        GestorAeroportos *g_aero = ga;
        hash_reservas_add(hash_reservas, r);
        checka_reservas(r, hash, g_aero);
        verifica_passageiros(hash_pass, hap, r, hash);
    }
    return 0;
}

