#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sistema.h"

/* ===================== CRIAÇÃO E DESTRUIÇÃO ===================== */

Sistema *criar_sistema() {
    Sistema *s = malloc(sizeof(Sistema));
    if (!s) return NULL;

    s->aeroportos = criar_gestor_aeroportos();
    s->aeronaves = criar_gestor_aeronaves();
    s->voos = criar_gestor_voos();
    s->passageiros = criar_gestor_passageiros();
    s->reservas = criar_gestor_reservas();

    return s;
}

void libertar_sistema(Sistema *s) {
    if (!s) return;
    libertar_gestor_aeroportos(s->aeroportos);
    libertar_gestor_aeronaves(s->aeronaves);
    libertar_gestor_voos(s->voos);
    libertar_gestor_passageiros(s->passageiros);
    libertar_gestor_reservas(s->reservas);
    free(s);
}

/* ===================== CARREGAMENTO (CSV → memória) ===================== */

int carregar_aeroportos(Sistema *s, const char *filename) {
    Aeroportos **arr;
    int count;
    if (load_aeroportos_from_file(filename, &arr, &count) != 0) return -1;

    for (int i = 0; i < count; i++)
        inserir_aeroporto(s->aeroportos, arr[i]);

    free(arr);
    return count;
}

int carregar_aeronaves(Sistema *s, const char *filename) {
    Aeronaves **arr;
    int count;
    if (load_aeronaves_from_file(filename, &arr, &count) != 0) return -1;

    for (int i = 0; i < count; i++)
        inserir_aeronave(s->aeronaves, arr[i]);

    free(arr);
    return count;
}

int carregar_voos(Sistema *s, const char *filename) {
    Voo **arr;
    int count;
    if (load_voos_from_file(filename, &arr, &count) != 0) return -1;

    for (int i = 0; i < count; i++)
        inserir_voo(s->voos, arr[i]);

    free(arr);
    return count;
}

int carregar_passageiros(Sistema *s, const char *filename) {
    Passageiros **arr;
    int count;
    if (load_passageiros_from_file(filename, &arr, &count) != 0) return -1;

    for (int i = 0; i < count; i++)
        inserir_passageiro(s->passageiros, arr[i]);

    free(arr);
    return count;
}

int carregar_reservas(Sistema *s, const char *filename) {
    Reservas **arr;
    int count;
    if (load_reservas_from_file(filename, &arr, &count) != 0) return -1;

    for (int i = 0; i < count; i++)
        inserir_reserva(s->reservas, arr[i]);

    free(arr);
    return count;
}

/* ===== Carrega tudo automaticamente de uma pasta ===== */

int carregar_tudo(Sistema *s, const char *pasta) {
    char path[256];

    sprintf(path, "%s/aeroportos.csv", pasta);
    carregar_aeroportos(s, path);

    sprintf(path, "%s/aeronaves.csv", pasta);
    carregar_aeronaves(s, path);

    sprintf(path, "%s/voos.csv", pasta);
    carregar_voos(s, path);

    sprintf(path, "%s/passageiros.csv", pasta);
    carregar_passageiros(s, path);

    sprintf(path, "%s/reservas.csv", pasta);
    carregar_reservas(s, path);

    return 1;
}
