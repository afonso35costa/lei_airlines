#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "reservas.h"

typedef struct reservas {
    char *reservation_id;             // número da reserva
    char **flight_ids;                // identificadores de voo
    char *document_number;        // documento de identificação do passageiro
    char *seat;                   // número do assento (ex: "12A")
    double price;                     // preço da reserva
    bool extra_luggage;               // bagagem extra incluída
    bool priority_boarding;           // embarque prioritário incluído
} Reservas;

// FUNÇÃO CONSTRUTORA - Criar nova reserva e alocar memória
Reservas* create_reserva(void) {
    Reservas *r = malloc(sizeof(Reservas));
    if (r == NULL) {
        return NULL;
    }
    
    // Inicializa todos os campos
    r->reservation_id = NULL;
    r->flight_ids = NULL;
    r->document_number = NULL;
    r->seat = NULL;
    r->price = 0.0;
    r->extra_luggage = false;
    r->priority_boarding = false;
    
    return r;
}

// FUNÇÃO INICIALIZADORA - Inicializar reserva com valores
Reservas* init_reserva(const char *reservation_id, char **flight_ids, 
                      const char *document_number, const char *seat, 
                      double price, bool extra_luggage, bool priority_boarding) {
    Reservas *r = create_reserva();
    if (r == NULL) return NULL;
    
    // Aloca e copia strings simples
    r->reservation_id = reservation_id ? strdup(reservation_id) : NULL;
    r->document_number = document_number ? strdup(document_number) : NULL;
    r->seat = seat ? strdup(seat) : NULL;
    
    // Copia array de flight_ids
    if (flight_ids != NULL) {
        // Conta quantos flight_ids existem
        int count = 0;
        while (flight_ids[count] != NULL) count++;
        
        // Aloca array para os ponteiros + NULL terminator
        r->flight_ids = malloc((count + 1) * sizeof(char*));
        if (r->flight_ids != NULL) {
            for (int i = 0; i < count; i++) {
                if (flight_ids[i])  // protecção extra
                    r->flight_ids[i] = strdup(flight_ids[i]);
                else
                    r->flight_ids[i] = NULL;
            }
            r->flight_ids[count] = NULL; // Terminator
        }
    }
    
    // Copia valores numéricos/booleanos
    r->price = price;
    r->extra_luggage = extra_luggage;
    r->priority_boarding = priority_boarding;
    
    return r;
}

// FUNÇÃO DE COMPARAÇÃO - Comparar reservas por ID
int compare_reservas(const Reservas *r1, const Reservas *r2) {
    if (r1 == NULL && r2 == NULL) return 0;
    if (r1 == NULL) return -1;
    if (r2 == NULL) return 1;
    
    // Compara pelo ID da reserva (chave única)
    char *id1 = get_reservation_id_reservas(r1);
    char *id2 = get_reservation_id_reservas(r2);
    
    if (id1 == NULL && id2 == NULL) return 0;
    if (id1 == NULL) return -1;
    if (id2 == NULL) return 1;
    
    return strcmp(id1, id2);
}


// FUNÇÃO DESTRUTORA - Libertar toda a memória
void destroy_reserva(Reservas *r) {
    if (r == NULL) return;
    
    // Liberta strings simples
    free(r->reservation_id);

    if (r->flight_ids) {
        for (int i = 0; r->flight_ids[i] != NULL; i++) {
            free(r->flight_ids[i]);
        }
        free(r->flight_ids);
    }
    free(r->document_number);
    free(r->seat);
    
    // Liberta a estrutura principal
    free(r);
}

// ============================================================================
// GETTERS - Funções para obter valores
// ============================================================================

char* get_reservation_id_reservas(const Reservas *r) {
    return (r != NULL) ? r->reservation_id : NULL;
}

char** get_flight_ids_reservas(const Reservas *r) {
    return (r != NULL) ? r->flight_ids : NULL;
}

int get_num_flights_reserva(const Reservas *r) {
    if (r == NULL || r->flight_ids == NULL) return 0;
    
    int count = 0;
    while (r->flight_ids[count] != NULL) {
        count++;
    }
    return count;
}

char* get_document_number_reservas(const Reservas *r) {
    return (r != NULL) ? r->document_number : NULL;
}

char* get_seat_reservas(const Reservas *r) {
    return (r != NULL) ? r->seat : NULL;
}

double get_price_reservas(const Reservas *r) {
    return (r != NULL) ? r->price : 0.0;
}

bool get_extra_luggage_reservas(const Reservas *r) {
    return (r != NULL) ? r->extra_luggage : false;
}

bool get_priority_boarding_reservas(const Reservas *r) {
    return (r != NULL) ? r->priority_boarding : false;
}


// ============================================================================
// SETTERS - Funções para definir valores
// ============================================================================

void set_reservation_id_reservas(Reservas *r, const char *id) {
    if (r == NULL) return;
    free(r->reservation_id);
    r->reservation_id = id ? strdup(id) : NULL;
}

void set_flight_ids_reservas(Reservas *r, char **flight_ids) {
    if (r == NULL) return;
    
    // Liberta array anterior
    if (r->flight_ids != NULL) {
        for (int i = 0; r->flight_ids[i] != NULL; i++) {
            free(r->flight_ids[i]);
        }
        free(r->flight_ids);
    }
    
    // Copia novo array
    if (flight_ids != NULL) {
        int count = 0;
        while (flight_ids[count] != NULL) count++;
        
        r->flight_ids = malloc((count + 1) * sizeof(char*));
        if (r->flight_ids != NULL) {
            for (int i = 0; i < count; i++) {
                r->flight_ids[i] = strdup(flight_ids[i]);
            }
            r->flight_ids[count] = NULL;
        }
    } else {
        r->flight_ids = NULL;
    }
}

void set_document_number_reservas(Reservas *r, const char *doc) {
    if (r == NULL) return;
    free(r->document_number);
    r->document_number = doc ? strdup(doc) : NULL;
}

void set_seat_reservas(Reservas *r, const char *seat) {
    if (r == NULL) return;
    free(r->seat);
    r->seat = seat ? strdup(seat) : NULL;
}

void set_price_reservas(Reservas *r, double price) {
    if (r != NULL) r->price = price;
}

void set_extra_luggage_reservas(Reservas *r, bool extra) {
    if (r != NULL) r->extra_luggage = extra;
}

void set_priority_boarding(Reservas *r, bool priority) {
    if (r != NULL) r->priority_boarding = priority;
}

