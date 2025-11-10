#include "gestor_voos.h"
#include <glib.h>
#include <stdlib.h>

struct gestor_voos {
    GPtrArray *array;  // array de Voo*
};

// Cria gestor
GestorVoos* gestor_voos_create(void) {
    GestorVoos *gv = malloc(sizeof(GestorVoos));
    if (!gv) return NULL;
    gv->array = g_ptr_array_new_with_free_func((GDestroyNotify)voo_free);
    return gv;
}

// Adiciona voo
void gestor_voos_add(GestorVoos *gv, Voo *v) {
    g_ptr_array_add(gv->array, v);
}

// Remove voo por flight_id
void gestor_voos_remove(GestorVoos *gv, const char *flight_id) {
    for (guint i = 0; i < gv->array->len; i++) {
        Voo *v = g_ptr_array_index(gv->array, i);
        if (strcmp(v->flight_id, flight_id) == 0) {
            g_ptr_array_remove_index(gv->array, i);
            return;
        }
    }
}

// Retorna voo pelo índice
Voo* gestor_voos_get(GestorVoos *gv, int index) {
    if (index < 0 || index >= (int)gv->array->len) return NULL;
    return g_ptr_array_index(gv->array, index);
}

// Liberta gestor e todos os voos
void gestor_voos_free(GestorVoos *gv) {
    g_ptr_array_free(gv->array, TRUE);
    free(gv);
}
