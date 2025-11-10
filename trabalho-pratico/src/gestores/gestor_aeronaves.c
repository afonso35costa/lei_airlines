#include "gestor_aeronaves.h"
#include <glib.h>
#include <stdlib.h>

struct gestor_aeronaves {
    GPtrArray *array;  // array de Aeronaves*
};

// Cria gestor
GestorAeronaves* gestor_aeronaves_create(void) {
    GestorAeronaves *ga = malloc(sizeof(GestorAeronaves));
    if (!ga) return NULL;
    ga->array = g_ptr_array_new_with_free_func((GDestroyNotify)aeronaves_free);
    return ga;
}

// Adiciona aeronave
void gestor_aeronaves_add(GestorAeronaves *ga, Aeronaves *aero) {
    g_ptr_array_add(ga->array, aero);
}

// Remove aeronave por identificador
void gestor_aeronaves_remove(GestorAeronaves *ga, const char *identifier) {
    for (guint i = 0; i < ga->array->len; i++) {
        Aeronaves *a = g_ptr_array_index(ga->array, i);
        if (strcmp(a->identifier, identifier) == 0) {
            g_ptr_array_remove_index(ga->array, i);
            return;
        }
    }
}

// Retorna aeronave pelo índice
Aeronaves* gestor_aeronaves_get(GestorAeronaves *ga, int index) {
    if (index < 0 || index >= (int)ga->array->len) return NULL;
    return g_ptr_array_index(ga->array, index);
}

// Liberta gestor e todas as aeronaves
void gestor_aeronaves_free(GestorAeronaves *ga) {
    g_ptr_array_free(ga->array, TRUE);
    free(ga);
}