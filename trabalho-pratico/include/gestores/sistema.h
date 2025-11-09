#ifndef SISTEMA_H
#define SISTEMA_H

#include "gestor_aeroportos.h"
#include "gestor_aeronaves.h"
#include "gestor_voos.h"
#include "gestor_passageiros.h"
#include "gestor_reservas.h"

/* Estrutura principal do sistema */
typedef struct sistema {
    GestorAeroportos *aeroportos;
    GestorAeronaves *aeronaves;
    GestorVoos *voos;
    GestorPassageiros *passageiros;
    GestorReservas *reservas;
} Sistema;

/* Criação e destruição */
Sistema *criar_sistema();
void libertar_sistema(Sistema *s);

/* Carregamento de dados a partir de ficheiros CSV */
int carregar_aeroportos(Sistema *s, const char *filename);
int carregar_aeronaves(Sistema *s, const char *filename);
int carregar_voos(Sistema *s, const char *filename);
int carregar_passageiros(Sistema *s, const char *filename);
int carregar_reservas(Sistema *s, const char *filename);

/* Carrega tudo de uma pasta */
int carregar_tudo(Sistema *s, const char *pasta);

#endif
