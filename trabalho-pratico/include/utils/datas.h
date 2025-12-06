#ifndef DATAS_H
#define DATAS_H

#include <stdbool.h>
#include <stddef.h>

typedef struct DataHora DataHora;

DataHora* ler_data_hora(const char *texto);
DataHora* ler_data(const char *texto);
char *data_hora_para_texto(DataHora *dh);
char *data_para_texto(DataHora *dh);
int diferenca_em_dias(DataHora *d1, DataHora *d2);
int diferenca_em_minutos(DataHora *d1, DataHora *d2);
int diferenca_em_anos(int data1, int data2);
int esta_entre_datas(DataHora *alvo, DataHora *inicio, DataHora *fim);
void destroy_data_hora(DataHora *dh);
DataHora* copy_data_hora (const DataHora *src);
int get_hora(DataHora *dh);
int get_data(DataHora *dh);
int comparar_data_hora(const DataHora *d1, const DataHora *d2);

#endif
