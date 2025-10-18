#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Estrutura principal para guardar data e hora
typedef struct {
    int data;   // AAAAMMDD
    int hora;   // HHMM
} DataHora;

// ------------------------- Funções de leitura -------------------------

// Lê "YYYY-MM-DD HH:MM" e devolve um DataHora
DataHora ler_data_hora(const char *texto) {
    DataHora dh = {0, 0};
    int ano, mes, dia, hora, minuto;

    if (sscanf(texto, "%d-%d-%d %d:%d", &ano, &mes, &dia, &hora, &minuto) == 5) {
        dh.data = ano * 10000 + mes * 100 + dia;
        dh.hora = hora * 100 + minuto;
    }
    return dh;
}

// Lê "YYYY-MM-DD" e devolve um DataHora (hora = 0)
DataHora ler_data(const char *texto) {
    DataHora dh = {0, 0};
    int ano, mes, dia;

    if (sscanf(texto, "%d-%d-%d", &ano, &mes, &dia) == 3) {
        dh.data = ano * 10000 + mes * 100 + dia;
        dh.hora = 0;
    }
    return dh;
}

// ------------------------- Funções de conversão -------------------------

// Converte DataHora para string "YYYY-MM-DD HH:MM"
char *data_hora_para_texto(DataHora dh) {
    int ano = dh.data / 10000;
    int mes = (dh.data / 100) % 100;
    int dia = dh.data % 100;
    int hora = dh.hora / 100;
    int minuto = dh.hora % 100;

    char *buffer = malloc(20);
    sprintf(buffer, "%04d-%02d-%02d %02d:%02d", ano, mes, dia, hora, minuto);
    return buffer;
}

// Converte apenas a data para "YYYY-MM-DD"
char *data_para_texto(DataHora dh) {
    int ano = dh.data / 10000;
    int mes = (dh.data / 100) % 100;
    int dia = dh.data % 100;

    char *buffer = malloc(12);
    sprintf(buffer, "%04d-%02d-%02d", ano, mes, dia);
    return buffer;
}

// ------------------------- Funções de diferença -------------------------

// Diferença aproximada em dias (funciona se estiverem no mesmo mês)
int diferenca_em_dias(DataHora d1, DataHora d2) {
    int dia1 = d1.data % 100;
    int dia2 = d2.data % 100;
    return dia2 - dia1;
}

// Diferença em minutos (baseado em dia, hora e minuto)
int diferenca_em_minutos(DataHora d1, DataHora d2) {
    int dia1 = d1.data % 100;
    int dia2 = d2.data % 100;

    int hora1 = d1.hora / 100;
    int min1 = d1.hora % 100;
    int hora2 = d2.hora / 100;
    int min2 = d2.hora % 100;

    int total1 = (dia1 * 24 * 60) + (hora1 * 60) + min1;
    int total2 = (dia2 * 24 * 60) + (hora2 * 60) + min2;

    return total2 - total1;
}

// Diferença em anos entre duas datas completas
int diferenca_em_anos(int data1, int data2) {
    int a1 = data1 / 10000, m1 = (data1 / 100) % 100, d1 = data1 % 100;
    int a2 = data2 / 10000, m2 = (data2 / 100) % 100, d2 = data2 % 100;

    int diff = a2 - a1;
    if (m2 < m1 || (m2 == m1 && d2 < d1)) diff--;
    return diff;
}

// ------------------------- Funções de comparação -------------------------

// Verifica se uma data/hora está entre duas outras (inclusive)
bool esta_entre_datas(DataHora alvo, DataHora inicio, DataHora fim) {
    if (alvo.data < inicio.data || alvo.data > fim.data) return false;
    if (alvo.data == inicio.data && alvo.hora < inicio.hora) return false;
    if (alvo.data == fim.data && alvo.hora > fim.hora) return false;
    return true;
}

