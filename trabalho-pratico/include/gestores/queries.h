#ifndef QUERIES_H
#define QUERIES_H

#include <stdio.h>
#include "gestor_aeroportos.h"
#include "gestor_aeronaves.h"
#include "gestor_voos.h"
#include "datas.h"  // Para DataHora

/* Q1: Listar resumo de um aeroporto */
Aeroportos *query1(GestorAeroportos *ga, const char *code, FILE *out);

typedef struct aircraft_stats AircraftStats;

// Funcao que percorre todos os voos e verifica a aeronave ligada a cada voo
void percorre_voos_aeronaves(GestorVoos *gv, GestorAeronaves *ga);

// Função de comparação para ordenação de Aeronaves

gint compare_aeronaves(gconstpointer a, gconstpointer b);

void free_aircraft_stats(gpointer data);

// Função que passa cada value da hash table de aeronaves para um array de Aeronaves e o ordena automaticamente

GList* ordena_tudo (GestorAeronaves *ga);

/* Q2: Top N aeronaves com mais voos realizados */
Aeronaves **query2(GList *stats_list, int N, const char *manufacturer_filter, FILE *out);

// Funcao que percorre todos os voos e conta partidas por aeroporto
void percorre_voos_aeroportos(GestorVoos *gv, GestorAeroportos *ga, char* start_date, char* end_date);

/* Q3: Aeroporto com mais partidas entre 2 datas */
Aeroportos *query3(GestorAeroportos *ga, FILE *out);

#endif