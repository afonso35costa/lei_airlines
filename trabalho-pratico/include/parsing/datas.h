#ifndef DATAS_H
#define DATAS_H

#include <stdbool.h>
#include <stddef.h>

typedef struct DataHora;

DataHora ler_data_hora(const char *texto);
DataHora ler_data(const char *texto);
void data_hora_para_texto(DataHora dh, char *destino, size_t tamanho);
void data_para_texto(DataHora dh, char *destino, size_t tamanho);
int diferenca_em_dias(DataHora d1, DataHora d2);
int diferenca_em_minutos(DataHora d1, DataHora d2);
int diferenca_em_anos(int data1, int data2);
bool esta_entre_datas(DataHora alvo, DataHora inicio, DataHora fim);

#endif
