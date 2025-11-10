#include "queries.h"
#include <string.h>
#include <stdlib.h>
#include <glib.h> 

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
    // code;name;city;country;type
    fprintf(out, "%s;%s;%s;%s;%s\n",
        a->code,
        a->name,
        a->city,
        a->country,
        a->type
    );
}

// Estrutura auxiliar para estatísticas de aeronaves
typedef struct {
    char *identifier;
    char *manufacturer;
    char *model;
    int flight_count;
} AircraftStats;

// Função de comparação para ordenação
static gint compare_aircraft_stats(gconstpointer a, gconstpointer b) {
    const AircraftStats *aa = (const AircraftStats *)a;
    const AircraftStats *bb = (const AircraftStats *)b;
    
    // Primeiro ordena por número de voos (descrescente)
    if (aa->flight_count != bb->flight_count) {
        return bb->flight_count - aa->flight_count;
    }
    
    // Em caso de empate, ordena por identificador (crescente, posição a posição)
    return strcmp(aa->identifier, bb->identifier);
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

// Função auxiliar para encontrar aeronave por identificador
static Aeronaves* find_aeronave_by_identifier(GestorAeronaves *gae, const char *identifier) {
    if (!gae || !identifier) return NULL;
    
    for (guint i = 0; i < gae->array->len; i++) {
        Aeronaves *a = g_ptr_array_index(gae->array, i);
        if (strcmp(a->identifier, identifier) == 0) {
            return a;
        }
    }
    return NULL;
}

/* Q2: Top N aeronaves com mais voos realizados */
void query2(GestorAeronaves *gae, GestorVoos *gv, int n, const char *manufacturer, FILE *out) {
    if (!gae || !gv || !out || n <= 0) {
        return;
    }

    // Hash table para contar voos por aeronave
    GHashTable *flight_counts = g_hash_table_new_full(g_str_hash, g_str_equal, 
                                                      free, free);
    
    // Itera sobre todos os voos
    for (guint i = 0; i < gv->array->len; i++) {
        Voo *voo = g_ptr_array_index(gv->array, i);
        
        // Só conta voos não cancelados
        if (!voo || !voo->status || strcmp(voo->status, "Cancelled") == 0) {
            continue;
        }
        
        // Verifica se a aeronave existe
        Aeronaves *aeronave = find_aeronave_by_identifier(gae, voo->aircraft);
        if (!aeronave) {
            continue; // Aeronave não encontrada, ignora este voo
        }
        
        // Aplica filtro de fabricante se especificado
        if (manufacturer && strcmp(aeronave->manufacturer, manufacturer) != 0) {
            continue; // Não corresponde ao fabricante filtrado
        }
        
        // Incrementa contador para esta aeronave
        char *aircraft_id = voo->aircraft;
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
    
    // Converte hash table para GPtrArray para ordenação
    GPtrArray *stats_array = g_ptr_array_new_with_free_func(free_aircraft_stats);
    
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, flight_counts);
    
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        char *identifier = (char *)key;
        int *count = (int *)value;
        
        // Procura dados completos da aeronave
        Aeronaves *aeronave = find_aeronave_by_identifier(gae, identifier);
        if (aeronave) {
            AircraftStats *stats = malloc(sizeof(AircraftStats));
            stats->identifier = strdup(identifier);
            stats->manufacturer = strdup(aeronave->manufacturer);
            stats->model = strdup(aeronave->model);
            stats->flight_count = *count;
            
            g_ptr_array_add(stats_array, stats);
        }
    }
    
    // Ordena o array
    g_ptr_array_sort(stats_array, compare_aircraft_stats);
    
    // Escreve os resultados (limitado a N)
    guint limit = (n < (int)stats_array->len) ? n : stats_array->len;
    for (guint i = 0; i < limit; i++) {
        AircraftStats *stats = g_ptr_array_index(stats_array, i);
        fprintf(out, "%s, %s, %s, %d\n",
                stats->identifier,
                stats->manufacturer,
                stats->model,
                stats->flight_count);
    }
    
    // Limpa memória
    g_ptr_array_unref(stats_array);
    g_hash_table_destroy(flight_counts);
}

// Estrutura auxiliar para estatísticas de aeroportos
typedef struct {
    char *code;
    char *name;
    char *city;
    char *country;
    int departure_count;
} AirportStats;

// Função de comparação para aeroportos (por partidas desc, depois código asc)
static gint compare_airport_stats(gconstpointer a, gconstpointer b) {
    const AirportStats *aa = (const AirportStats *)a;
    const AirportStats *bb = (const AirportStats *)b;
    
    // Primeiro ordena por número de partidas (descrescente)
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

// Função auxiliar para verificar se data está no intervalo
static gboolean is_date_in_range(DataHora *date, DataHora *start_date, DataHora *end_date) {
    if (!date || !start_date || !end_date) return FALSE;
    
    // Assumindo que existe função de comparação de DataHora
    // date >= start_date && date <= end_date
    return (compare_data_hora(date, start_date) >= 0 && 
            compare_data_hora(date, end_date) <= 0);
}

/* Q3: Aeroporto com mais partidas entre 2 datas */
void query3(GestorAeroportos *ga, GestorVoos *gv, DataHora *start_date, DataHora *end_date, FILE *out) {
    if (!ga || !gv || !out || !start_date || !end_date) {
        return;
    }

    // Hash table para contar partidas por aeroporto
    GHashTable *departure_counts = g_hash_table_new_full(g_str_hash, g_str_equal, 
                                                         free, free);
    
    // Itera sobre todos os voos
    for (guint i = 0; i < gv->array->len; i++) {
        Voo *voo = g_ptr_array_index(gv->array, i);
        
        // Verifica se o voo não foi cancelado
        if (!voo || !voo->status || strcmp(voo->status, "Cancelled") == 0) {
            continue;
        }
        
        // Verifica se tem data real de partida
        if (!voo->actual_departure) {
            continue;
        }
        
        // Verifica se a data de partida real está no intervalo
        if (!is_date_in_range(voo->actual_departure, start_date, end_date)) {
            continue;
        }
        
        // Verifica se o aeroporto de origem existe
        if (!voo->origin) {
            continue;
        }
        
        // Incrementa contador para este aeroporto
        char *origin_code = voo->origin;
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
            stats->name = strdup(aeroporto->name);
            stats->city = strdup(aeroporto->city);
            stats->country = strdup(aeroporto->country);
            stats->departure_count = *count;
            
            g_ptr_array_add(stats_array, stats);
        }
    }
    
    // Ordena o array (maior número de partidas primeiro, depois menor código)
    g_ptr_array_sort(stats_array, compare_airport_stats);
    
    // Escreve apenas o primeiro resultado (aeroporto com mais partidas)
    if (stats_array->len > 0) {
        AirportStats *winner = g_ptr_array_index(stats_array, 0);
        fprintf(out, "%s, %s, %s, %s, %d\n",
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