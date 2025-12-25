#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <glib.h> 
#include "gestor_aeroportos.h"
#include "gestor_aeronaves.h"
#include "gestor_voos.h"
#include "gestor_reservas.h"
#include "aeroportos.h"
#include "aeronaves.h"
#include "reservas.h"
#include "voos.h"
#include "datas.h"
#include "queries.h"

Aeroportos *query1(GestorAeroportos *ga, GestorReservas *gr, HashVoos *gv, const char *code, FILE *out) {
    if (!ga || !gr || !gv || !code || !out)
        return NULL;
    // procurar aeroporto
    Aeroportos *a = gestor_aeroportos_get(ga, code);
    if (a) {
        for (guint i = 0; i < gestor_reservas_get_length(gr); i++) {
            Reservas *r = gestor_reservas_get(gr, i);
            if (r) {
                char **flight_ids = get_flight_ids_reservas(r);

                for (guint j = 0; j < get_num_flights_reserva(r); j++) {
                    Voo *v = hash_voos_get(gv, flight_ids[j]);
                    if (!v) {
                        return NULL;
                    }
                    if (v && strcmp(get_status_voo(v), "Cancelled") != 0) {
                        // verificar se o aeroporto é origem ou destino
                        if (g_strcmp0(get_origin_voo(v), code) == 0) {
                            int count = get_arr_count_aeroporto(a);
                            set_arr_count_aeroporto(a, count + 1);
                        }
                        if (g_strcmp0(get_destination_voo(v), code) == 0) {
                            int count = get_dep_count_aeroporto(a);
                            set_dep_count_aeroporto(a, count + 1);
                        }
                    }
                }
            }
        }
    }
    return a;
}

// Estrutura auxiliar para estatísticas de aeronaves
struct aircraft_stats {
    char *identifier;
    char *manufacturer;
    char *model;
    int flight_count;
};

// Função que percorre todos os voos e verifica a aeronave ligada a cada voo

void percorre_voos_aeronaves(ArrayVoos *gv, GestorAeronaves *ga) {
    if (!gv || !ga) {
        return;
    }

    for (guint i = 0; i < array_voos_get_length(gv); i++) {
        Voo *voo = array_voos_get(gv, i);
        if (!voo) {
            continue;
        }

        char *aircraft_id = get_aircraft_voo(voo);
        if (strcmp(get_status_voo(voo), "Cancelled") != 0) {
            Aeronaves *aero = gestor_aeronaves_get(ga, aircraft_id);
            if (aero) {
                int current_count = get_num_voos_aeronave(aero);
                set_num_voos_aeronave(aero, current_count + 1);
            }
        }
        
    }
}

// Função de comparação para ordenação de Aeronaves    

gint compare_aeronaves(gconstpointer a, gconstpointer b) {
        const Aeronaves *aa = (const Aeronaves *)a;
        const Aeronaves *bb = (const Aeronaves *)b;

        if (get_num_voos_aeronave(aa) != get_num_voos_aeronave(bb))
            return get_num_voos_aeronave(bb) - get_num_voos_aeronave(aa); // descendente por contagem

        return strcmp(get_identifier_aeronave(aa), get_identifier_aeronave(bb)); // ascendente por identificador
}

// Função que passa cada value da hash table de aeronaves para um array de AircraftStats e o ordena

GList *ordena_tudo (GestorAeronaves *ga) {
    if (!ga) return NULL;

    GList *stats_list = NULL;

    // Percorre a hash table
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, gestor_aeronaves_get_hash(ga));

    while (g_hash_table_iter_next(&iter, &key, &value)) {
        Aeronaves *aero = (Aeronaves *)value;
        if (!aero) continue;
        stats_list = g_list_append(stats_list, aero);
    }

    // Ordena a lista
    stats_list = g_list_sort(stats_list, compare_aeronaves);
    return stats_list;
}

Aeronaves **query2(GList *stats_list, int N, const char *manufacturer_filter, FILE *out) {
    if (!stats_list || N <= 0 || !out) {
        return NULL;
    }

    Aeronaves **result = malloc(sizeof(Aeronaves *) * N);
    if (!result) return NULL;

    int count = 0;
    GList *current = stats_list;

    while (current != NULL && count < N) {
        Aeronaves *aeron = (Aeronaves *)current->data;
        if (!aeron) {
            current = current->next;
            continue;
        }

        // Aplica filtro de fabricante se fornecido
        if (manufacturer_filter == NULL || strcmp(manufacturer_filter, "") == 0 || strcmp(get_manufacturer_aeronave(aeron), manufacturer_filter) == 0) {

            // Guarda a referência no array de resultados
            result[count] = aeron;
            count++;
        }

        current = current->next;
    }

    // Se nao houver estatisticas para mostrar retorna NULL
    if (count == 0) {
        free(result);
        return NULL;
    }

    return result;
}

// ============================================================
// QUERY 3 - Aeroporto com mais partidas entre datas
// ============================================================


// Função que percorre todos os voos e conta partidas por aeroporto

void percorre_voos_aeroportos(ArrayVoos *gv, GestorAeroportos *ga, char* start_date, char* end_date) {

    // RESET na contagem de partidas de todos os aeroportos
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, gestor_aeroportos_get_hash(ga));
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        Aeroportos *aero = (Aeroportos*)value;
        if (aero) {
            set_departures_aeroporto(aero, 0);
        }
    }

    // Verifica se os gestores são válidos
    if (!gv || !ga) {
        return;
    }
    DataHora *start = ler_data(start_date);
    DataHora *end = ler_data(end_date);
    if (!start || !end) {
        destroy_data_hora(start);
        destroy_data_hora(end);
        return;
    }

    for (guint i = 0; i < array_voos_get_length(gv); i++) {
    //  for (guint i = 0; i < 5; i++) {

        Voo *voo = array_voos_get(gv, i);
        if (!voo) {
            continue;
        }

        char *origin = get_origin_voo(voo);
        DataHora *departure = get_actual_departure_voo(voo);
        if (!origin || !departure) {
            continue;
        }


        if (strcmp(get_status_voo(voo), "Cancelled") != 0 && esta_entre_datas(departure, start, end)) {
            add_departures_aeroporto(ga, origin);
        }
    }
    destroy_data_hora(start);
    destroy_data_hora(end);
}

// Resolução da query 3 que é dar o aeroporto com mais partidas entre datas

Aeroportos *query3(GestorAeroportos *ga, FILE *out) {
    if (!ga || !out) {
        return NULL;
    }

    // Percorre a hash table de aeroportos para encontrar o com mais partidas
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, gestor_aeroportos_get_hash(ga));

    Aeroportos *top_airport = NULL;
    int max_departures = -1;

    while (g_hash_table_iter_next(&iter, &key, &value)) {
        Aeroportos *aero = (Aeroportos *)value;
        if (!aero) continue;

        int departures = get_departures_aeroporto(aero);
        if (departures > max_departures) {
            max_departures = departures;
            top_airport = aero;
        }
        else if (departures == max_departures) {
            // Em caso de empate, escolher o que vem primeiro lexicograficamente pelo código
            if (top_airport && strcmp(get_code_aeroporto(aero), get_code_aeroporto(top_airport)) < 0) {
                top_airport = aero;
            }
        }
    }

    // Escreve o resultado no ficheiro de output
    if (top_airport && max_departures > 0) {
        return top_airport;
    }
    return NULL;
}
