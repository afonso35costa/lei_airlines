#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <glib.h> 
#include "gestor_aeroportos.h"
#include "gestor_aeronaves.h"
#include "gestor_voos.h"
#include "aeroportos.h"
#include "aeronaves.h"
#include "voos.h"
#include "datas.h"

void query1(GestorAeroportos *ga, const char *code, FILE *out) {
    if (!ga || !code || !out)
        return;

    // procurar aeroporto
    Aeroportos *a = gestor_aeroportos_get(ga, code);

    // se não existir → linha vazia
    if (!a) {
        fprintf(out, "\n");
        return;
    }

    // Formato exigido:
    // code,name,city,country,type
    fprintf(out, "%s,%s,%s,%s,%s\n",
        get_code_aeroporto(a),
        get_name_aeroporto(a),
        get_city_aeroporto(a),
        get_country_aeroporto(a),
        get_type_aeroporto(a)
    );
}

// Estrutura auxiliar para estatísticas de aeronaves
typedef struct {
    char *identifier;
    char *manufacturer;
    char *model;
    int flight_count;
} AircraftStats;

// Função de comparação para ordenar os voos em ordem decrescente
int compare_aircraft_stats(const void *a, const void *b) {
    AircraftStats *stats_a = *(AircraftStats **)a;
    AircraftStats *stats_b = *(AircraftStats **)b;
    return stats_b->flight_count - stats_a->flight_count;  // Ordem decrescente
}

// Liberta estrutura AircraftStats
static void free_aircraft_stats(gpointer data) {
    AircraftStats *stats = (AircraftStats *)data;
    if (stats) {
        free(stats->identifier);
        free(stats->manufacturer);
        free(stats->model);
        free(stats);
    }
}

void query2(GestorAeronaves *gae, GestorVoos *gv, int n, const char *manufacturer, FILE *out) {
    if (!gae || !gv || !out || n <= 0) return;

    // 1️⃣ Construir hash table de aeronaves para lookup rápido
    GHashTable *aircraft_table = g_hash_table_new(g_str_hash, g_str_equal);
    for (guint i = 0; i < gestor_aeronaves_get_length(gae); i++) {
        Aeronaves *a = gestor_aeronaves_get(gae, i);
        if (a && get_identifier_aeronave(a))
            g_hash_table_insert(aircraft_table, get_identifier_aeronave(a), a);
    }

    // 2️⃣ Hash table para contar voos por aeronave
    /* Hash table para contar voos por aeronave.
       Se for passado `manufacturer`, inicializa apenas com aeronaves desse fabricante,
       caso contrário inicializa com todas (contagem a 0). */
    GHashTable *flight_counts = g_hash_table_new_full(g_str_hash, g_str_equal, free, free);
    for (guint i = 0; i < gestor_aeronaves_get_length(gae); i++) {
        Aeronaves *a = gestor_aeronaves_get(gae, i);
        if (!a) continue;

        char *id = get_identifier_aeronave(a);
        if (!id) continue;

        if (manufacturer) {
            char *manu = get_manufacturer_aeronave(a);
            if (!manu || strcmp(manu, manufacturer) != 0) continue;
        }

        int *cnt = malloc(sizeof(int));
        *cnt = 0;
        g_hash_table_insert(flight_counts, strdup(id), cnt);
    }

    // 3️⃣ Iterar sobre todos os voos
    for (guint i = 0; i < gestor_voos_get_length(gv); i++) {
        Voo *voo = gestor_voos_get(gv, i);
        if (!voo) continue;

        // Ignora voos cancelados
        char *status = get_status_voo(voo);
        if (!status || strcmp(status, "Cancelled") == 0) continue;

        char *aircraft_id = get_aircraft_voo(voo);
        if (!aircraft_id) continue;

        // Busca aeronave na hash table
        Aeronaves *aeronave = g_hash_table_lookup(aircraft_table, aircraft_id);
        if (!aeronave) continue;

        // Filtra por fabricante se especificado
        if (manufacturer && get_manufacturer_aeronave(aeronave)) {
            if (strcmp(get_manufacturer_aeronave(aeronave), manufacturer) != 0) continue;
        }

        // Incrementa contador
        gpointer existing = g_hash_table_lookup(flight_counts, aircraft_id);
        if (existing) {
            int *count = (int *)existing;
            (*count)++;
        } else {
            int *new_count = malloc(sizeof(int));
            *new_count = 1;
            g_hash_table_insert(flight_counts, strdup(aircraft_id), new_count);
        }
    }

    // 4️⃣ Converte hash table em array para ordenação
    GPtrArray *stats_array = g_ptr_array_new_with_free_func(free_aircraft_stats);
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, flight_counts);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        char *identifier = (char *)key;
        int *count = (int *)value;
        Aeronaves *aeronave = g_hash_table_lookup(aircraft_table, identifier);
        if (aeronave) {
            AircraftStats *stats = malloc(sizeof(AircraftStats));
            stats->identifier = strdup(identifier);
            stats->manufacturer = strdup(get_manufacturer_aeronave(aeronave));
            stats->model = strdup(get_model_aeronave(aeronave));
            stats->flight_count = *count;
            g_ptr_array_add(stats_array, stats);
        }
    }

    // 5️⃣ Ordena e escreve resultados
    g_ptr_array_sort(stats_array, compare_aircraft_stats);
    guint limit = (n < (int)stats_array->len) ? n : stats_array->len;
    for (guint i = 0; i < limit; i++) {
        AircraftStats *stats = g_ptr_array_index(stats_array, i);
        fprintf(out, "%s,%s,%s,%d\n",
                stats->identifier,
                stats->manufacturer,
                stats->model,
                stats->flight_count);
    }

    // 6️⃣ Limpa memória
    g_ptr_array_unref(stats_array);
    g_hash_table_destroy(flight_counts);
    g_hash_table_destroy(aircraft_table);
}


// ============================================================
// QUERY 3 - Aeroporto com mais partidas entre datas
// ============================================================

// Estrutura auxiliar para estatísticas de aeroportos
typedef struct {
    char *code;
    char *name;
    char *city;
    char *country;
    int departure_count;
} AirportStats;

// Função de comparação para aeroportos
static gint compare_airport_stats(gconstpointer a, gconstpointer b) {
    const AirportStats *aa = (const AirportStats *)a;
    const AirportStats *bb = (const AirportStats *)b;
    
    // Primeiro ordena por número de partidas (descendente)
    if (aa->departure_count != bb->departure_count) {
        return bb->departure_count - aa->departure_count;
    }
    
    // Em caso de empate, ordena por código (crescente, lexicográfico)
    return strcmp(aa->code, bb->code);
}

// Liberta estrutura AirportStats
static void free_airport_stats(gpointer data) {
    AirportStats *stats = (AirportStats *)data;
    if (stats) {
        free(stats->code);
        free(stats->name);
        free(stats->city);
        free(stats->country);
        free(stats);
    }
}

void query3(GestorAeroportos *ga, GestorVoos *gv, DataHora *start_date, DataHora *end_date, FILE *out) {
    if (!ga || !gv || !out || !start_date || !end_date) {
        return;
    }

    // Hash table para contar partidas por aeroporto
    GHashTable *departure_counts = g_hash_table_new_full(g_str_hash, g_str_equal, 
                                                         free, free);
    
    // Itera sobre todos os voos
    for (guint i = 0; i < gestor_voos_get_length(gv); i++) {
        Voo *voo = gestor_voos_get(gv, i);

        // Verifica se o voo não foi cancelado
        if (!voo || !get_status_voo(voo) || strcmp(get_status_voo(voo), "Cancelled") == 0) {
            continue;
        }
        
        // Verifica se tem data real de partida (actual_departure)
        DataHora *actual_dep = get_actual_departure_voo(voo);
        if (!actual_dep) {
            continue;
        }
        
        // Verifica se a data está no intervalo usando comparar_data_hora
        // actual_dep >= start_date && actual_dep <= end_date
        if (comparar_data_hora(actual_dep, start_date) < 0 || 
            comparar_data_hora(actual_dep, end_date) > 0) {
            continue;
        }
        
        // Verifica se o aeroporto de origem existe
        char *origin_code = get_origin_voo(voo);
        if (!origin_code) {
            continue;
        }
        
        // Incrementa contador para este aeroporto
        gpointer existing = g_hash_table_lookup(departure_counts, origin_code);
        
        if (existing) {
            int *count = (int *)existing;
            (*count)++;
        } else {
            int *new_count = malloc(sizeof(int));
            *new_count = 1;
            g_hash_table_insert(departure_counts, strdup(origin_code), new_count);
        }
    }
    
    // Verifica se houve voos no intervalo
    if (g_hash_table_size(departure_counts) == 0) {
        fprintf(out, "\n");  // Linha vazia se não houver voos
        g_hash_table_destroy(departure_counts);
        return;
    }
    
    // Converte hash table para GPtrArray para ordenação
    GPtrArray *stats_array = g_ptr_array_new_with_free_func(free_airport_stats);
    
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, departure_counts);
    
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        char *code = (char *)key;
        int *count = (int *)value;
        
        // Procura dados completos do aeroporto
        Aeroportos *aeroporto = gestor_aeroportos_get(ga, code);
        if (aeroporto) {
            AirportStats *stats = malloc(sizeof(AirportStats));
            stats->code = strdup(code);
            stats->name = strdup(get_name_aeroporto(aeroporto));
            stats->city = strdup(get_city_aeroporto(aeroporto));
            stats->country = strdup(get_country_aeroporto(aeroporto));
            stats->departure_count = *count;
            
            g_ptr_array_add(stats_array, stats);
        }
    }
    
    // Ordena o array
    g_ptr_array_sort(stats_array, compare_airport_stats);
    
    // Escreve apenas o primeiro resultado (aeroporto com mais partidas)
    if (stats_array->len > 0) {
        AirportStats *winner = g_ptr_array_index(stats_array, 0);
        fprintf(out, "%s,%s,%s,%s,%d\n",
                winner->code,
                winner->name,
                winner->city,
                winner->country,
                winner->departure_count);
    }
    
    // Limpa memória
    g_ptr_array_unref(stats_array);
    g_hash_table_destroy(departure_counts);
}