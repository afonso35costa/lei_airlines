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
#include "queries.h"

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

// NUNCA ESCREVER COISAS NUM FICHEIRO NA FUNÇÃO DE QUERY
// CRIAR MÓDULO INPUT/OUTPUT PARA ISSO


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
struct aircraft_stats {
    char *identifier;
    char *manufacturer;
    char *model;
    int flight_count;
};

// Função que percorre todos os voos e verifica a aeronave ligada a cada voo

void percorre_voos_aeronaves(GestorVoos *gv, GestorAeronaves *ga) {
    if (!gv || !ga) {
        return;
    }

    for (guint i = 0; i < gestor_voos_get_length(gv); i++) {
        Voo *voo = gestor_voos_get(gv, i);
        if (!voo) {
            continue;
        }

        char *aircraft_id = get_aircraft_voo(voo);
        if (strcmp(get_status_voo(voo), "Cancelled") != 0) {
            HashValue *hv = gestor_aeronaves_get(ga, aircraft_id);
            if (hv) {
                add_voo_value(hv);
            }
        }
        
    }
}

// Função de comparação para ordenação de AircraftStats    

gint compare_aircraft_stats(gconstpointer a, gconstpointer b) {
        const AircraftStats *aa = (const AircraftStats *)a;
        const AircraftStats *bb = (const AircraftStats *)b;

        if (aa->flight_count != bb->flight_count)
            return bb->flight_count - aa->flight_count; // descendente por contagem

        return strcmp(aa->identifier, bb->identifier); // ascendente por identificador
}

void free_aircraft_stats(gpointer data) {
    AircraftStats *stats = (AircraftStats *)data;
    if (!stats) return;
    free(stats->identifier);
    free(stats->manufacturer);
    free(stats->model);
    free(stats);
}

// Função que passa cada value da hash table de aeronaves para um array de AircraftStats e o ordena automaticamente

GList *ordena_tudo (GestorAeronaves *ga) {
    if (!ga) return NULL;

    GList *stats_list = NULL;

    // Percorre a hash table
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, gestor_aeronaves_get_hash(ga));
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        HashValue *hv = (HashValue *)value;
        if (!hv) continue;

        AircraftStats *stats = malloc(sizeof(AircraftStats));
        if (!stats) continue;
        
        Aeronaves *aero = get_aeronave_value(hv);
        stats->identifier = strdup(get_identifier_aeronave(aero));
        stats->manufacturer = strdup(get_manufacturer_aeronave(aero));
        stats->model = strdup(get_model_aeronave(aero));
        stats->flight_count = get_num_voos_aeronave(hv);

        stats_list = g_list_append(stats_list, stats);
    }

    // Ordena a lista
    stats_list = g_list_sort(stats_list, compare_aircraft_stats);
    return stats_list;

}

// Resolução da query 2 que é dar o N número de aeronaves com mais voos
void query2(GList *stats_list, int N, const char *manufacturer_filter, FILE *out) {
    if (!stats_list || N <= 0 || !out) {
        return;
    }

    int count = 0;
    GList *current = stats_list;

    while (current != NULL && count < N) {
        AircraftStats *stats = (AircraftStats *)current->data;
        if (!stats) {
            current = current->next;
            continue;
        }

        // Aplica filtro de fabricante se fornecido
        if (manufacturer_filter == NULL || strcmp(manufacturer_filter, "") == 0 ||
            strcmp(stats->manufacturer, manufacturer_filter) == 0) {

            // Escreve no ficheiro de output
            fprintf(out, "%s,%s,%s,%d\n",
                stats->identifier,
                stats->manufacturer,
                stats->model,
                stats->flight_count
            );

            count++;
        }

        current = current->next;
    }

    // Se nao houver estatisticas para mostrar, escreve linha vazia
    if (count == 0) {
        fprintf(out, "\n");
    }

}



//

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

// Função que percorre todos os voos e conta partidas por aeroporto

void percorre_voos_aeroportos(GestorVoos *gv, GestorAeroportos *ga, char* start_date, char* end_date) {

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

    for (guint i = 0; i < gestor_voos_get_length(gv); i++) {
    //  for (guint i = 0; i < 5; i++) {

        Voo *voo = gestor_voos_get(gv, i);
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
}

// Resolução da query 3 que é dar o aeroporto com mais partidas entre datas

void query3(GestorAeroportos *ga, FILE *out) {
    if (!ga || !out) {
        return;
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
        fprintf(out, "%s,%s,%s,%s,%d\n",
            get_code_aeroporto(top_airport),
            get_name_aeroporto(top_airport),
            get_city_aeroporto(top_airport),
            get_country_aeroporto(top_airport),
            max_departures
        );
    } else {
        fprintf(out, "\n"); // Nenhum aeroporto com partidas (>0) encontrado
    }
}