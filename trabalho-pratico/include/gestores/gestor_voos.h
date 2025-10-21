#ifndef GESTOR_VOOS_H
#define GESTOR_VOOS_H

#include <stdbool.h>
#include "../entidades/voos.h"

typedef struct GestorVoos GestorVoos;

GestorVoos* criarGestorVoos(void);
void destruirGestorVoos(GestorVoos *gv);

void adicionarVoo(GestorVoos *gv, Voo *v);
bool removerVoo(GestorVoos *gv, const char *flight_id);
Voo* procurarVoo(const GestorVoos *gv, const char *flight_id);
int contarVoos(const GestorVoos *gv);
void iterarVoos(GestorVoos *gv, void (*callback)(Voo *));
void ordenarVoosPorData(GestorVoos *gv);
void listarVoos(const GestorVoos *gv);

#endif
