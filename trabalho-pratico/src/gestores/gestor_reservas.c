#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "reservas.h"
#include "gestor_reservas.h"

// Estrutura do gestor de reservas
typedef struct gestor_reservas {
    Reservas **reservas;           // Array dinâmico de reservas
    int count;                     // Número atual de reservas
    int capacity;                  // Capacidade atual do array
    bool sorted;                   // Flag se está ordenado
} GestorReservas;

// ===========================================
// FUNÇÕES DE GESTÃO DE MEMÓRIA
// ===========================================

GestorReservas* create_gestor_reservas(void) {
    GestorReservas *gestor = malloc(sizeof(GestorReservas));
    if (gestor == NULL) return NULL;
    
    gestor->capacity = 100;  // Capacidade inicial
    gestor->reservas = malloc(gestor->capacity * sizeof(Reservas*));
    if (gestor->reservas == NULL) {
        free(gestor);
        return NULL;
    }
    
    gestor->count = 0;
    gestor->sorted = true;  // Array vazio está "ordenado"
    
    return gestor;
}

void destroy_gestor_reservas(GestorReservas *gestor) {
    if (gestor == NULL) return;
    
    // Liberta todas as reservas
    for (int i = 0; i < gestor->count; i++) {
        destroy_reserva(gestor->reservas[i]);
    }
    
    // Liberta o array e o gestor
    free(gestor->reservas);
    free(gestor);
}

// ===========================================
// FUNÇÕES DE MANIPULAÇÃO
// ===========================================

// Redimensiona o array se necessário
static bool resize_if_needed(GestorReservas *gestor) {
    if (gestor->count >= gestor->capacity) {
        int new_capacity = gestor->capacity * 2;
        Reservas **new_array = realloc(gestor->reservas, 
                                      new_capacity * sizeof(Reservas*));
        if (new_array == NULL) return false;
        
        gestor->reservas = new_array;
        gestor->capacity = new_capacity;
    }
    return true;
}

bool add_reserva(GestorReservas *gestor, Reservas *reserva) {
    if (gestor == NULL || reserva == NULL) return false;
    
    // Verifica se já existe (evita duplicados)
    if (find_reserva_by_id(gestor, get_reservation_id(reserva)) != NULL) {
        printf("AVISO: Reserva com ID %s já existe\n", 
               get_reservation_id(reserva));
        return false;
    }
    
    // Redimensiona se necessário
    if (!resize_if_needed(gestor)) return false;
    
    // Adiciona a reserva
    gestor->reservas[gestor->count] = reserva;
    gestor->count++;
    gestor->sorted = false;  // Array já não está ordenado
    
    return true;
}

bool remove_reserva(GestorReservas *gestor, const char *reservation_id) {
    if (gestor == NULL || reservation_id == NULL) return false;
    
    // Procura a reserva
    for (int i = 0; i < gestor->count; i++) {
        char *id = get_reservation_id(gestor->reservas[i]);
        if (id != NULL && strcmp(id, reservation_id) == 0) {
            // Liberta a reserva
            destroy_reserva(gestor->reservas[i]);
            
            // Move todos os elementos para trás
            for (int j = i; j < gestor->count - 1; j++) {
                gestor->reservas[j] = gestor->reservas[j + 1];
            }
            
            gestor->count--;
            return true;
        }
    }
    
    return false;  // Não encontrou
}

// ===========================================
// FUNÇÕES DE PESQUISA
// ===========================================

Reservas* find_reserva_by_id(GestorReservas *gestor, const char *reservation_id) {
    if (gestor == NULL || reservation_id == NULL) return NULL;
    
    for (int i = 0; i < gestor->count; i++) {
        char *id = get_reservation_id(gestor->reservas[i]);
        if (id != NULL && strcmp(id, reservation_id) == 0) {
            return gestor->reservas[i];
        }
    }
    
    return NULL;
}

Reservas** find_reservas_by_passenger(GestorReservas *gestor, const char *document_number, int *found_count) {
    if (gestor == NULL || document_number == NULL || found_count == NULL) return NULL;
    
    *found_count = 0;
    Reservas **results = malloc(gestor->count * sizeof(Reservas*));
    if (results == NULL) return NULL;
    
    for (int i = 0; i < gestor->count; i++) {
        char *doc = get_document_number_reserva(gestor->reservas[i]);
        if (doc != NULL && strcmp(doc, document_number) == 0) {
            results[*found_count] = gestor->reservas[i];
            (*found_count)++;
        }
    }
    
    if (*found_count == 0) {
        free(results);
        return NULL;
    }
    
    return results;
}

Reservas** find_reservas_by_flight(GestorReservas *gestor, const char *flight_id, int *found_count) {
    if (gestor == NULL || flight_id == NULL || found_count == NULL) return NULL;
    
    *found_count = 0;
    Reservas **results = malloc(gestor->count * sizeof(Reservas*));
    if (results == NULL) return NULL;
    
    for (int i = 0; i < gestor->count; i++) {
        char **flights = get_flight_ids(gestor->reservas[i]);
        if (flights != NULL) {
            // Verifica se o flight_id está na lista
            for (int j = 0; flights[j] != NULL; j++) {
                if (strcmp(flights[j], flight_id) == 0) {
                    results[*found_count] = gestor->reservas[i];
                    (*found_count)++;
                    break;  // Não precisamos verificar mais flights desta reserva
                }
            }
        }
    }
    
    if (*found_count == 0) {
        free(results);
        return NULL;
    }
    
    return results;
}

Reservas** find_reservas_by_price_range(GestorReservas *gestor, double min_price, double max_price, int *found_count) {
    if (gestor == NULL || found_count == NULL) return NULL;
    
    *found_count = 0;
    Reservas **results = malloc(gestor->count * sizeof(Reservas*));
    if (results == NULL) return NULL;
    
    for (int i = 0; i < gestor->count; i++) {
        double price = get_price(gestor->reservas[i]);
        if (price >= min_price && price <= max_price) {
            results[*found_count] = gestor->reservas[i];
            (*found_count)++;
        }
    }
    
    if (*found_count == 0) {
        free(results);
        return NULL;
    }
    
    return results;
}

Reservas** find_reservas_with_extras(GestorReservas *gestor, bool with_extra_luggage, bool with_priority_boarding, int *found_count) {
    if (gestor == NULL || found_count == NULL) return NULL;
    
    *found_count = 0;
    Reservas **results = malloc(gestor->count * sizeof(Reservas*));
    if (results == NULL) return NULL;
    
    for (int i = 0; i < gestor->count; i++) {
        bool has_extra = get_extra_luggage(gestor->reservas[i]);
        bool has_priority = get_priority_boarding(gestor->reservas[i]);
        
        // Verifica se corresponde aos critérios
        if ((!with_extra_luggage || has_extra) && 
            (!with_priority_boarding || has_priority)) {
            results[*found_count] = gestor->reservas[i];
            (*found_count)++;
        }
    }
    
    if (*found_count == 0) {
        free(results);
        return NULL;
    }
    
    return results;
}

// ===========================================
// FUNÇÕES DE ORDENAÇÃO
// ===========================================

void sort_reservas(GestorReservas *gestor) {
    if (gestor == NULL || gestor->sorted) return;
    
    // Bubble sort (simples para começar)
    for (int i = 0; i < gestor->count - 1; i++) {
        for (int j = 0; j < gestor->count - i - 1; j++) {
            if (compare_reservas(gestor->reservas[j], gestor->reservas[j + 1]) > 0) {
                // Troca
                Reservas *temp = gestor->reservas[j];
                gestor->reservas[j] = gestor->reservas[j + 1];
                gestor->reservas[j + 1] = temp;
            }
        }
    }
    
    gestor->sorted = true;
}

void sort_reservas_by_price(GestorReservas *gestor) {
    if (gestor == NULL) return;
    
    // Bubble sort por preço (crescente)
    for (int i = 0; i < gestor->count - 1; i++) {
        for (int j = 0; j < gestor->count - i - 1; j++) {
            double price1 = get_price(gestor->reservas[j]);
            double price2 = get_price(gestor->reservas[j + 1]);
            
            if (price1 > price2) {
                // Troca
                Reservas *temp = gestor->reservas[j];
                gestor->reservas[j] = gestor->reservas[j + 1];
                gestor->reservas[j + 1] = temp;
            }
        }
    }
    
    gestor->sorted = false;  // Ordenado por preço, não por ID
}

// ===========================================
// FUNÇÕES DE CARREGAMENTO
// ===========================================

bool load_reservas_to_gestor(GestorReservas *gestor, const char *filename) {
    if (gestor == NULL || filename == NULL) return false;
    
    Reservas **reservas_array;
    int count;
    
    // Carrega do ficheiro CSV
    if (load_reservas_from_file(filename, &reservas_array, &count) != 0) {
        return false;
    }
    
    // Adiciona cada reserva ao gestor
    int added = 0;
    for (int i = 0; i < count; i++) {
        if (add_reserva(gestor, reservas_array[i])) {
            added++;
        } else {
            destroy_reserva(reservas_array[i]);  // Liberta se não conseguiu adicionar
        }
    }
    
    free(reservas_array);  // Liberta só o array, não as reservas
    
    printf("Adicionadas %d/%d reservas ao gestor\n", added, count);
    return added > 0;
}

// ===========================================
// FUNÇÕES DE INFORMAÇÃO
// ===========================================

int get_reservas_count(GestorReservas *gestor) {
    return (gestor != NULL) ? gestor->count : 0;
}

double get_total_revenue(GestorReservas *gestor) {
    if (gestor == NULL) return 0.0;
    
    double total = 0.0;
    for (int i = 0; i < gestor->count; i++) {
        total += get_price(gestor->reservas[i]);
    }
    
    return total;
}

double get_average_price(GestorReservas *gestor) {
    if (gestor == NULL || gestor->count == 0) return 0.0;
    
    return get_total_revenue(gestor) / gestor->count;
}

void get_extras_statistics(GestorReservas *gestor, int *with_extra_luggage, int *with_priority_boarding, int *with_both) {
    if (gestor == NULL) return;
    
    *with_extra_luggage = 0;
    *with_priority_boarding = 0;
    *with_both = 0;
    
    for (int i = 0; i < gestor->count; i++) {
        bool has_extra = get_extra_luggage(gestor->reservas[i]);
        bool has_priority = get_priority_boarding(gestor->reservas[i]);
        
        if (has_extra) (*with_extra_luggage)++;
        if (has_priority) (*with_priority_boarding)++;
        if (has_extra && has_priority) (*with_both)++;
    }
}

void print_all_reservas(GestorReservas *gestor) {
    if (gestor == NULL) {
        printf("Gestor inválido\n");
        return;
    }
    
    printf("=== LISTA DE RESERVAS (%d total) ===\n", gestor->count);
    for (int i = 0; i < gestor->count; i++) {
        printf("\n--- Reserva %d ---\n", i + 1);
        print_reserva(gestor->reservas[i]);
    }
    printf("====================================\n");
}

void print_reservas_summary(GestorReservas *gestor) {
    if (gestor == NULL) {
        printf("Gestor inválido\n");
        return;
    }
    
    int with_extra, with_priority, with_both;
    get_extras_statistics(gestor, &with_extra, &with_priority, &with_both);
    
    printf("=== RESUMO DE RESERVAS ===\n");
    printf("Total: %d reservas\n", gestor->count);
    printf("Capacidade: %d\n", gestor->capacity);
    printf("Ordenado: %s\n", gestor->sorted ? "Sim" : "Não");
    printf("Receita total: %.2f€\n", get_total_revenue(gestor));
    printf("Preço médio: %.2f€\n", get_average_price(gestor));
    printf("Com bagagem extra: %d (%.1f%%)\n", with_extra, 
           gestor->count > 0 ? (with_extra * 100.0 / gestor->count) : 0.0);
    printf("Com embarque prioritário: %d (%.1f%%)\n", with_priority,
           gestor->count > 0 ? (with_priority * 100.0 / gestor->count) : 0.0);
    printf("Com ambos extras: %d (%.1f%%)\n", with_both,
           gestor->count > 0 ? (with_both * 100.0 / gestor->count) : 0.0);
    printf("=========================\n");
}

// ===========================================
// FUNÇÕES DE VALIDAÇÃO
// ===========================================

bool validate_all_reservas(GestorReservas *gestor) {
    if (gestor == NULL) return false;
    
    bool all_valid = true;
    for (int i = 0; i < gestor->count; i++) {
        if (!validate_reserva(gestor->reservas[i])) {
            printf("ERRO: Reserva %d inválida\n", i + 1);
            all_valid = false;
        }
    }
    
    return all_valid;
}

// ===========================================
// FUNÇÕES ESPECÍFICAS PARA RESERVAS
// ===========================================

// Calcula ocupação por voo
void get_flight_occupancy(GestorReservas *gestor, const char *flight_id, int *passenger_count) {
    if (gestor == NULL || flight_id == NULL || passenger_count == NULL) return;
    
    *passenger_count = 0;
    
    for (int i = 0; i < gestor->count; i++) {
        char **flights = get_flight_ids(gestor->reservas[i]);
        if (flights != NULL) {
            for (int j = 0; flights[j] != NULL; j++) {
                if (strcmp(flights[j], flight_id) == 0) {
                    (*passenger_count)++;
                    break;
                }
            }
        }
    }
}

// Lista todos os voos únicos nas reservas
char** get_unique_flights(GestorReservas *gestor, int *flight_count) {
    if (gestor == NULL || flight_count == NULL) return NULL;
    
    // Array temporário para guardar voos únicos
    char **unique_flights = malloc(gestor->count * 10 * sizeof(char*)); // Estimativa
    *flight_count = 0;
    
    for (int i = 0; i < gestor->count; i++) {
        char **flights = get_flight_ids(gestor->reservas[i]);
        if (flights != NULL) {
            for (int j = 0; flights[j] != NULL; j++) {
                // Verifica se já existe na lista
                bool exists = false;
                for (int k = 0; k < *flight_count; k++) {
                    if (strcmp(unique_flights[k], flights[j]) == 0) {
                        exists = true;
                        break;
                    }
                }
                
                if (!exists) {
                    unique_flights[*flight_count] = strdup(flights[j]);
                    (*flight_count)++;
                }
            }
        }
    }
    
    // Redimensiona para o tamanho exato
    unique_flights = realloc(unique_flights, (*flight_count) * sizeof(char*));
    
    return unique_flights;
}

// Liberta array de voos únicos
void free_unique_flights(char **flights, int count) {
    if (flights == NULL) return;
    
    for (int i = 0; i < count; i++) {
        free(flights[i]);
    }
    free(flights);
}