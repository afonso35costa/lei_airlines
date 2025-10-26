#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "reservas.h"

typedef struct reservas {
    char *reservation_id;             // número da reserva
    char **flight_ids;                // identificadores de voo (assumindo máximo 10 voos)
    char *document_number;        // documento de identificação do passageiro
    char *seat;                   // número do assento (ex: "12A")
    double price;                     // preço da reserva
    bool extra_luggage;               // bagagem extra incluída
    bool priority_boarding;           // embarque prioritário incluído
    char *qr_code;                // string do código QR
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
    r->qr_code = NULL;
    
    return r;
}

// FUNÇÃO INICIALIZADORA - Inicializar reserva com valores
Reservas* init_reserva(const char *reservation_id, char **flight_ids, 
                      const char *document_number, const char *seat, 
                      double price, bool extra_luggage, bool priority_boarding, 
                      const char *qr_code) {
    Reservas *r = create_reserva();
    if (r == NULL) return NULL;
    
    // Aloca e copia strings simples
    r->reservation_id = reservation_id ? strdup(reservation_id) : NULL;
    r->document_number = document_number ? strdup(document_number) : NULL;
    r->seat = seat ? strdup(seat) : NULL;
    r->qr_code = qr_code ? strdup(qr_code) : NULL;
    
    // Copia array de flight_ids
    if (flight_ids != NULL) {
        // Conta quantos flight_ids existem
        int count = 0;
        while (flight_ids[count] != NULL) count++;
        
        // Aloca array para os ponteiros + NULL terminator
        r->flight_ids = malloc((count + 1) * sizeof(char*));
        if (r->flight_ids != NULL) {
            for (int i = 0; i < count; i++) {
                r->flight_ids[i] = strdup(flight_ids[i]);
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
    char *id1 = get_reservation_id(r1);
    char *id2 = get_reservation_id(r2);
    
    if (id1 == NULL && id2 == NULL) return 0;
    if (id1 == NULL) return -1;
    if (id2 == NULL) return 1;
    
    return strcmp(id1, id2);
}

// FUNÇÃO DE IMPRESSÃO - Mostrar dados da reserva
void print_reserva(const Reservas *r) {
    if (r == NULL) {
        printf("Reserva inválida\n");
        return;
    }
    
    printf("=== RESERVA ===\n");
    printf("ID Reserva: %s\n", get_reservation_id(r) ? get_reservation_id(r) : "N/A");
    printf("Documento: %s\n", get_document_number_reserva(r) ? get_document_number_reserva(r) : "N/A");
    printf("Assento: %s\n", get_seat(r) ? get_seat(r) : "N/A");
    printf("Preço: %.2f\n", get_price(r));
    printf("Bagagem extra: %s\n", get_extra_luggage(r) ? "Sim" : "Não");
    printf("Embarque prioritário: %s\n", get_priority_boarding(r) ? "Sim" : "Não");
    
    // Imprime voos
    char **flights = get_flight_ids(r);
    if (flights != NULL) {
        printf("Voos: ");
        for (int i = 0; flights[i] != NULL; i++) {
            printf("%s%s", flights[i], flights[i+1] ? ", " : "");
        }
        printf("\n");
    } else {
        printf("Voos: N/A\n");
    }
    
    printf("QR Code: %s\n", get_qr_code(r) ? get_qr_code(r) : "N/A");
    printf("===============\n");
}

// FUNÇÃO DESTRUTORA - Libertar toda a memória
void destroy_reserva(Reservas *r) {
    if (r == NULL) return;
    
    // Liberta strings simples
    free(r->reservation_id);
    free(r->document_number);
    free(r->seat);
    free(r->qr_code);
    
    // Liberta array de flight_ids
    if (r->flight_ids != NULL) {
        for (int i = 0; r->flight_ids[i] != NULL; i++) {
            free(r->flight_ids[i]);
        }
        free(r->flight_ids);
    }
    
    // Liberta a estrutura principal
    free(r);
}

// ============================================================================
// GETTERS - Funções para obter valores
// ============================================================================

char* get_reservation_id(const Reservas *r) {
    return (r != NULL) ? r->reservation_id : NULL;
}

char** get_flight_ids(const Reservas *r) {
    return (r != NULL) ? r->flight_ids : NULL;
}

char* get_document_number_reserva(const Reservas *r) {
    return (r != NULL) ? r->document_number : NULL;
}

char* get_seat(const Reservas *r) {
    return (r != NULL) ? r->seat : NULL;
}

double get_price(const Reservas *r) {
    return (r != NULL) ? r->price : 0.0;
}

bool get_extra_luggage(const Reservas *r) {
    return (r != NULL) ? r->extra_luggage : false;
}

bool get_priority_boarding(const Reservas *r) {
    return (r != NULL) ? r->priority_boarding : false;
}

char* get_qr_code(const Reservas *r) {
    return (r != NULL) ? r->qr_code : NULL;
}

// ============================================================================
// SETTERS - Funções para definir valores
// ============================================================================

void set_reservation_id(Reservas *r, const char *id) {
    if (r == NULL) return;
    free(r->reservation_id);
    r->reservation_id = id ? strdup(id) : NULL;
}

void set_flight_ids(Reservas *r, char **flight_ids) {
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

void set_document_number_reserva(Reservas *r, const char *doc) {
    if (r == NULL) return;
    free(r->document_number);
    r->document_number = doc ? strdup(doc) : NULL;
}

void set_seat(Reservas *r, const char *seat) {
    if (r == NULL) return;
    free(r->seat);
    r->seat = seat ? strdup(seat) : NULL;
}

void set_price(Reservas *r, double price) {
    if (r != NULL) r->price = price;
}

void set_extra_luggage(Reservas *r, bool extra) {
    if (r != NULL) r->extra_luggage = extra;
}

void set_priority_boarding(Reservas *r, bool priority) {
    if (r != NULL) r->priority_boarding = priority;
}

void set_qr_code(Reservas *r, const char *qr) {
    if (r == NULL) return;
    free(r->qr_code);
    r->qr_code = qr ? strdup(qr) : NULL;
}

// ============================================================================
// PARSER - Funções para ler dados de ficheiros CSV
// ============================================================================

// Função auxiliar para remover aspas
char* remove_quotes_reserva(char *str) {
    if (str == NULL) return NULL;
    
    int len = strlen(str);
    if (len >= 2 && str[0] == '"' && str[len-1] == '"') {
        str[len-1] = '\0';
        return str + 1;
    }
    return str;
}

// Parse de uma linha CSV para criar uma reserva
Reservas* parse_reserva_from_csv(const char *linha) {
    if (linha == NULL) return NULL;
    
    char *linha_copia = strdup(linha);
    if (linha_copia == NULL) return NULL;
    
    // Array para guardar os campos
    char *campos[8];
    int num_campos = 0;
    
    // Divide a linha pelos delimitadores ';'
    char *token = strtok(linha_copia, ";");
    while (token != NULL && num_campos < 8) {
        campos[num_campos] = remove_quotes_reserva(token);
        num_campos++;
        token = strtok(NULL, ";");
    }
    
    if (num_campos < 8) {
        printf("AVISO: Linha de reserva com apenas %d campos (esperados 8)\n", num_campos);
        free(linha_copia);
        return NULL;
    }
    
    // Parse dos flight_ids (podem ser múltiplos separados por ',')
    char **flight_ids = NULL;
    if (campos[1] != NULL) {
        // Conta quantos voos existem
        int flight_count = 1;
        for (char *p = campos[1]; *p; p++) {
            if (*p == ',') flight_count++;
        }
        
        // Aloca array para os flight_ids
        flight_ids = malloc((flight_count + 1) * sizeof(char*));
        if (flight_ids != NULL) {
            char *flight_token = strtok(campos[1], ",");
            int i = 0;
            while (flight_token != NULL && i < flight_count) {
                flight_ids[i] = strdup(flight_token);
                i++;
                flight_token = strtok(NULL, ",");
            }
            flight_ids[i] = NULL; // Terminator
        }
    }
    
    // Parse dos valores booleanos e numéricos
    double price = campos[4] ? atof(campos[4]) : 0.0;
    bool extra_luggage = (campos[5] && strcmp(campos[5], "1") == 0);
    bool priority_boarding = (campos[6] && strcmp(campos[6], "1") == 0);
    
    // Cria a reserva
    Reservas *r = create_reserva();
    if (r != NULL) {
        set_reservation_id(r, campos[0]);
        set_flight_ids(r, flight_ids);
        set_document_number_reserva(r, campos[2]);
        set_seat(r, campos[3]);
        set_price(r, price);
        set_extra_luggage(r, extra_luggage);
        set_priority_boarding(r, priority_boarding);
        set_qr_code(r, campos[7]);
    }
    
    // Limpa memory temporária
    if (flight_ids != NULL) {
        for (int i = 0; flight_ids[i] != NULL; i++) {
            free(flight_ids[i]);
        }
        free(flight_ids);
    }
    
    free(linha_copia);
    return r;
}

// Validação de reserva
bool validate_reserva(const Reservas *r) {
    if (r == NULL) return false;
    
    // Campos obrigatórios
    if (r->reservation_id == NULL || strlen(r->reservation_id) == 0) return false;
    if (r->document_number == NULL || strlen(r->document_number) == 0) return false;
    if (r->seat == NULL || strlen(r->seat) == 0) return false;
    if (r->flight_ids == NULL || r->flight_ids[0] == NULL) return false;
    if (r->price < 0) return false;
    
    return true;
}

// Carrega reservas de ficheiro CSV
int load_reservas_from_file(const char *filename, Reservas ***reservas, int *count) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("ERRO: Não foi possível abrir o ficheiro %s\n", filename);
        return -1;
    }
    
    int capacity = 100;
    *reservas = malloc(capacity * sizeof(Reservas*));
    *count = 0;
    
    char linha[4096];
    
    // Pula cabeçalho
    if (fgets(linha, sizeof(linha), file) == NULL) {
        fclose(file);
        free(*reservas);
        return -1;
    }
    
    while (fgets(linha, sizeof(linha), file)) {
        linha[strcspn(linha, "\n")] = 0;
        
        Reservas *r = parse_reserva_from_csv(linha);
        if (r != NULL && validate_reserva(r)) {
            if (*count >= capacity) {
                capacity *= 2;
                *reservas = realloc(*reservas, capacity * sizeof(Reservas*));
            }
            
            (*reservas)[*count] = r;
            (*count)++;
        } else if (r != NULL) {
            destroy_reserva(r);
        }
    }
    
    fclose(file);
    printf("Carregadas %d reservas do ficheiro %s\n", *count, filename);
    return 0;
}

// Libertar array de reservas
void free_reservas_array(Reservas **reservas, int count) {
    for (int i = 0; i < count; i++) {
        destroy_reserva(reservas[i]);
    }
    free(reservas);
}