#ifndef QUERIES_H
#define QUERIES_H

#include <stdio.h>
#include "gestor_aeroportos.h"
#include "gestor_aeronaves.h"
#include "gestor_voos.h"
#include "gestor_reservas.h"
#include "datas.h"  // Para DataHora

void checka_reservas(Reservas *r, HashVoos *hash_voos, GestorAeroportos *ga);

/* Q1: Listar resumo de um aeroporto */
Aeroportos *query1(GestorAeroportos *ga, const char *code);

typedef struct aircraft_stats AircraftStats;

// Funcao que percorre todos os voos e verifica a aeronave ligada a cada voo
void percorre_voos_aeronaves(ArrayVoos *gv, GestorAeronaves *ga);

// Função de comparação para ordenação de Aeronaves

gint compare_aeronaves(gconstpointer a, gconstpointer b);

// Função que passa cada value da hash table de aeronaves para um array de Aeronaves e o ordena automaticamente

GList* ordena_aeronaves (GestorAeronaves *ga);

/* Q2: Top N aeronaves com mais voos realizados */
Aeronaves **query2(GList *stats_list, int N, const char *manufacturer_filter);

// Funcao que percorre todos os voos e conta partidas por aeroporto
void percorre_voos_aeroportos(ArrayVoos *gv, GestorAeroportos *ga, char* start_date, char* end_date);

/* Q3: Aeroporto com mais partidas entre 2 datas */
Aeroportos *query3(GestorAeroportos *ga);

// Query 5:

typedef struct hash_time HashTime;

typedef struct time Time;

int get_time_delayed_count(Time *t);

int get_time_total(Time *t);

char *get_time_airline(Time *t);

void free_time(Time *t);

HashTime *hash_time_create(void);

HashTime *conta_tempo(ArrayVoos *voos);

double round3(double x);

gint compara_tempos(gconstpointer a, gconstpointer b);

GList *ordena_tempo_medio (HashTime *hash);

Time **query5(GList *tempo_medio, int N);

#endif