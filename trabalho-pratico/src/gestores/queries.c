#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <glib.h> 
#include "gestor_aeroportos.h"
#include "gestor_aeronaves.h"
#include "gestor_voos.h"
#include "gestor_reservas.h"
#include "gestor_passageiros.h"
#include "aeroportos.h"
#include "aeronaves.h"
#include "reservas.h"
#include "passageiros.h"
#include "voos.h"
#include "datas.h"
#include "queries.h"

// Função que percorre as reservas e aumenta as contagens

void checka_reservas(Reservas *r, HashVoos *hash_voos, GestorAeroportos *ga){
    if (r) {
        char **flight_ids = get_flight_ids_reservas(r);

        for (int j = 0; j < get_num_flights_reserva(r); j++) {
            Voo *v = hash_voos_get(hash_voos, flight_ids[j]);
            if (!v) {
                return;
            }
            if (v && strcmp(get_status_voo(v), "Cancelled") != 0) {
                Aeroportos *a1 = gestor_aeroportos_get(ga, get_origin_voo(v));
                if (a1) {
                    int count = get_arr_count_aeroporto(a1);
                    set_arr_count_aeroporto(a1, count + 1);
                }
                Aeroportos *a2 = gestor_aeroportos_get(ga, get_destination_voo(v));
                if (a2) {
                    int count = get_dep_count_aeroporto(a2);
                    set_dep_count_aeroporto(a2, count + 1);
                }
            }
        }
    }
}

Aeroportos *query1(GestorAeroportos *ga, const char *code) {
    if (!ga || !code)
        return NULL;
    // procurar aeroporto
    Aeroportos *a = gestor_aeroportos_get(ga, code);
    
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

GList *ordena_aeronaves (GestorAeronaves *ga) {
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

Aeronaves **query2(GList *stats_list, int N, const char *manufacturer_filter) {
    if (!stats_list || N <= 0) {
        return NULL;
    }

    Aeronaves **result = calloc(N, sizeof(Aeronaves *));
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

Aeroportos *query3(GestorAeroportos *ga) {
    if (!ga) {
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

// Resolução da query 4:



// Resolução da query 5:

struct hash_time {
    GHashTable *hash;
};

struct time {
    int delayed_count;
    int time;
    char *airline;
};

int get_time_delayed_count(Time *t) {
    return t->delayed_count;
}

int get_time_total(Time *t) {
    if (t) {
        return t->time;
    }
    else return 0;
}

char *get_time_airline(Time *t) {
    return t->airline;
}

void free_time(Time *t) {
    if (!t) return;
    free(t->airline);
    free(t);
}

HashTime *hash_time_create(void){
    HashTime *h = malloc(sizeof(HashTime));
    if (!h) return NULL;
    h->hash = g_hash_table_new_full(g_str_hash, g_str_equal, free, NULL);
    return h;
}

// Função que cria Hash Table com chave Airline e insere uma struct composta por delayed_count e time, conforme percorre todos os voos.

HashTime *conta_tempo(ArrayVoos *voos) {
    if (!voos) return NULL;
    HashTime *hash_time = hash_time_create();
    for (guint i=0; i < array_voos_get_length(voos) ; i++){
        Voo *v = array_voos_get(voos, i);
        if (strcmp(get_status_voo(v), "Delayed") == 0) {
            if (!g_hash_table_lookup(hash_time->hash, get_airline_voo(v))) {
                Time *t = malloc(sizeof(Time));
                t->delayed_count = 1;
                t->time = diferenca_em_minutos(get_departure_voo(v), get_actual_departure_voo(v));
                t->airline = strdup (get_airline_voo(v));
                g_hash_table_insert(hash_time->hash, g_strdup(get_airline_voo(v)), t);
            }
            else {
                Time *t = g_hash_table_lookup(hash_time->hash, get_airline_voo(v));
                t->delayed_count ++;
                t->time  += diferenca_em_minutos(get_departure_voo(v), get_actual_departure_voo(v));
            }
        }
    }
    return hash_time;
}

// Funcao que compara tempos

double round3(double x) {
    if (x >= 0)
        return (int)(x * 1000 + 0.5) / 1000.0;
    else
        return (int)(x * 1000 - 0.5) / 1000.0;
}

gint compara_tempos(gconstpointer a, gconstpointer b) {
        const Time *aa = (const Time *)a;
        const Time *bb = (const Time *)b;

        double t1 = (double) aa->time / aa->delayed_count;
        double t2 = (double) bb->time / bb->delayed_count;

        if (round3(t1) > round3(t2))
            return -1; // descendente por contagem

        if (round3(t1) < round3(t2)){
            return 1; 
        } 
        return strcmp(aa->airline, bb->airline); // ascendente por identificador
}


// Função que passa de Hash para Lista e ordena por tempo médio de voos (time / delayed_count)

GList *ordena_tempo_medio (HashTime *hash_time) {
    if (!hash_time) return NULL;

    GList *tempo_medio = NULL;

    // Percorre a hash table
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, hash_time->hash);

    while (g_hash_table_iter_next(&iter, &key, &value)) {
        Time *t = (Time *)value;
        if (!t) continue;
        tempo_medio = g_list_append(tempo_medio, t);
    }
    g_hash_table_destroy(hash_time->hash);
    free(hash_time);
    // Ordena a lista
    tempo_medio = g_list_sort(tempo_medio, compara_tempos);
    tempo_medio = g_list_append(tempo_medio, NULL);
    return tempo_medio;
}

// Resultado Final: top N companhias com maior atraso médio por voo

Time **query5(GList *tempo_medio, int N) {
    if (!tempo_medio || N <= 0) {
        return NULL;
    }

    Time **result = malloc(sizeof(Time *) * N);
    if (!result) return NULL;

    int count = 0;
    GList *current = tempo_medio;

    while (current != NULL && count < N) {
        Time *t = (Time *)current->data;
        if (!t) {
            result[count] = NULL;
            return result;
        }

        result[count] = t;
        count++;
        current = current->next;
    }

    // Se nao houver estatisticas para mostrar retorna NULL
    if (count == 0) {
        printf("Zero");
        free(result);
        return NULL;
    }
    return result;
}

// Funções necessárias para a query 6: Listar o aeroporto de destino mais comum para passageiros de uma determinada nacionalidade

struct passageiro_stats{
    char *nacionalidade;
    char *aeroporto_code;
    int count;
};

char *get_nacionalidade_passageiro_stats(PassageiroStats *ps) {
    return ps->nacionalidade;
}

char *get_aeroporto_code_passageiro_stats(PassageiroStats *ps) {
    return ps->aeroporto_code;
}

int get_count_passageiro_stats(PassageiroStats *ps) {
    return ps->count;
}

void passageiro_stats_free(PassageiroStats *ps) {
    if (!ps) return;
    free(ps->nacionalidade);
    free(ps->aeroporto_code);
    free(ps);
}

struct hash_aeroportos_passageiro {
    GHashTable *hash;
};

HashAeroportosPassageiro *hash_aero_pass_create(void){
    HashAeroportosPassageiro *h = malloc(sizeof(HashAeroportosPassageiro));
    if (!h) return NULL;
    h->hash = g_hash_table_new_full(g_str_hash, g_str_equal, free, (GDestroyNotify) passageiro_stats_free);
    return h;
}

void hash_aero_pass_free(HashAeroportosPassageiro *hap) {
    if (!hap) return;
    g_hash_table_destroy(hap->hash);
    free(hap);
}


void verifica_passageiros(HashPassageiros *hash_passageiros, HashAeroportosPassageiro *hash_ap, Reservas *r, HashVoos *hv) {
    if (!hash_passageiros || !hash_ap || !r || !hv) return;

    char *doc = get_document_number_reservas(r);
    if (!doc) return;

    Passageiros *p = hash_passageiros_get(hash_passageiros, doc);
    if (!p) return;
    
    char *nacionalidade = get_nationality_passageiros(p);
    if (!nacionalidade) return;

        char **id = get_flight_ids_reservas(r);
        if (!id) return;

        int num_flights = get_num_flights_reserva(r);

        for (int i = 0; i < num_flights; i++) {
            if (!id[i]) {
                continue;
            }

            Voo *v = hash_voos_get(hv, id[i]);
            if (!v || strcmp(get_status_voo(v), "Cancelled") == 0) {
                continue;
            }

            char *destination = get_destination_voo(v);
            if (!destination) return;

            char chave[512];
            snprintf(chave, sizeof(chave), "%s_%s", nacionalidade, destination);

            PassageiroStats *stat = g_hash_table_lookup(hash_ap->hash, chave);
            if (!stat) {
                stat = malloc(sizeof(PassageiroStats));
                stat->nacionalidade = strdup(nacionalidade);
                stat->aeroporto_code = strdup(destination);
                stat->count = 0;
                g_hash_table_insert(hash_ap->hash, strdup(chave), stat);
            }

            stat->count += 1;
        }
}

PassageiroStats *query6(HashAeroportosPassageiro *hash_ap, const char *nacionalidade){
    if (!hash_ap || !nacionalidade) {
        printf("DEBUG: hash_ap ou nacionalidade nulos\n");
        return NULL;
    }

    // Percorre a hash table de aeroportos para encontrar o com mais partidas
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, hash_ap->hash);

    PassageiroStats *top_airport = NULL;
    int max_arr = -1;

    while (g_hash_table_iter_next(&iter, &key, &value)) {
        PassageiroStats *stats = (PassageiroStats *)value;
        if (!stats) {
            continue;
        }

        if (strcmp(stats->nacionalidade, nacionalidade) == 0) {
            if (stats->count > max_arr || (stats->count == max_arr && strcmp(stats->aeroporto_code, top_airport->aeroporto_code) < 0)) {
                max_arr = stats->count;
                top_airport = stats;
            }
        }
    }
    // Escreve o resultado no ficheiro de output
    if (top_airport && max_arr > 0) {
        return top_airport;
    }
    return NULL;
}

