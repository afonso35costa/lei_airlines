#include <glib.h>
#include <stdlib.h>
#include <string.h>
#include "aeronaves.h"
#include "gestor_aeronaves.h"

struct gestor_aeronaves {
    GPtrArray *array;  // array de Aeronaves*
};

// Cria gestor
GestorAeronaves* gestor_aeronaves_create(void) {
    GestorAeronaves *ga = malloc(sizeof(GestorAeronaves));
    if (!ga) return NULL;
    ga->array = g_ptr_array_new_with_free_func((GDestroyNotify)free_aeronave);
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
        if (g_strcmp0(get_identifier_aeronave(a), identifier) == 0) {
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

// 🔧 NOVO: Retorna tamanho do array
guint gestor_aeronaves_get_length(GestorAeronaves *ga) {
    return ga ? ga->array->len : 0;
}

// 🔧 NOVO: Procura aeronave por identificador
Aeronaves* gestor_aeronaves_find_by_id(GestorAeronaves *ga, const char *identifier) {
    if (!ga || !identifier) return NULL;
    
    for (guint i = 0; i < ga->array->len; i++) {
        Aeronaves *a = g_ptr_array_index(ga->array, i);
        const char *id = get_identifier_aeronave(a);
        if (id && strcmp(id, identifier) == 0) {
            return a;
        }
    }
    return NULL;
}

// Liberta gestor e todas as aeronaves
void gestor_aeronaves_free(GestorAeronaves *ga) {
    if (ga) {
        g_ptr_array_free(ga->array, TRUE);
        free(ga);
    }
}