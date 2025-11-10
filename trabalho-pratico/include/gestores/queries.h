#ifndef QUERIES_H
#define QUERIES_H

#include <stdio.h>
#include "gestor_aeroportos.h"
#include "gestor_aeronaves.h"
#include "gestor_voos.h"
#include "datas.h"  // Para DataHora

/* Q1: Listar resumo de um aeroporto */
void query1(GestorAeroportos *ga, const char *code, FILE *out);

/* Q2: Top N aeronaves com mais voos realizados */
void query2(GestorAeronaves *gae, GestorVoos *gv, int n, const char *manufacturer, FILE *out);

/* Q3: Aeroporto com mais partidas entre 2 datas */
void query3(GestorAeroportos *ga, GestorVoos *gv, DataHora *start_date, DataHora *end_date, FILE *out);

#endif