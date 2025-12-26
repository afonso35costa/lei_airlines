#ifndef ESCRITA_H
#define ESCRITA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queries.h"

typedef void (*FuncaoEscreve)(void *objeto, FILE *out);

//Função que abre ficheiros para escrita
FILE* abrir_ficheiro_escrita(const char* path_filename);

// Funcao que escreve aeroportos em ficheiro
void escreve_aeroporto1 (Aeroportos *a, FILE *out, char* qtype);

// Funcao que escreve aeronaves em ficheiro
void escreve_aeronaves (Aeronaves **a, int num_aeronaves, FILE *out, char* qtype);

// Funcao que escreve aerporto mais num_departures
void escreve_aeroporto3 (Aeroportos *a, FILE *out, char* qtype);

void escreve_tempos5 (Time **time, int num_companhias, FILE *out, char *q_type);

#endif