#ifndef RESERVAS_H
#define RESERVAS_H

#include <stdbool.h>

// Forward declaration da struct
typedef struct reservas Reservas;

// ===========================================
// FUNÇÕES DE GESTÃO DE MEMÓRIA
// ===========================================

// Cria uma nova reserva e aloca memória
Reservas* create_reserva(void);

// Inicializa uma reserva com dados
Reservas* init_reserva(const char *reservation_id, char **flight_ids, 
                      const char *document_number, const char *seat, 
                      double price, bool extra_luggage, bool priority_boarding, 
                      const char *qr_code);

// Compara duas reservas por ID
int compare_reservas(const Reservas *r1, const Reservas *r2);

// Mostra dados da reserva
void print_reserva(const Reservas *r);

// Liberta toda a memória associada a uma reserva
void destroy_reserva(Reservas *r);


// ===========================================
// GETTERS - Funções para obter valores
// ===========================================

char* get_reservation_id(const Reservas *r);
char** get_flight_ids(const Reservas *r);
char* get_document_number_reserva(const Reservas *r);
char* get_seat(const Reservas *r);
double get_price(const Reservas *r);
bool get_extra_luggage(const Reservas *r);
bool get_priority_boarding(const Reservas *r);
char* get_qr_code(const Reservas *r);

// ===========================================
// SETTERS - Funções para definir valores
// ===========================================

void set_reservation_id(Reservas *r, const char *id);
void set_flight_ids(Reservas *r, char **flight_ids);
void set_document_number_reserva(Reservas *r, const char *doc);
void set_seat(Reservas *r, const char *seat);
void set_price(Reservas *r, double price);
void set_extra_luggage(Reservas *r, bool extra);
void set_priority_boarding(Reservas *r, bool priority);
void set_qr_code(Reservas *r, const char *qr);

// ===========================================
// PARSER - Funções para ler dados
// ===========================================

// Função auxiliar para remover aspas
char* remove_quotes(char *str);

// Parse de uma linha CSV para reserva
Reservas* parse_reserva_from_csv(const char *linha);

// Funçaõ de validação de reserva
bool validate_reserva(const Reservas *r);

// Carrega reservas de ficheiro CSV
int load_reservas_from_file(const char *filename, Reservas ***reservas, int *count);

// Liberta array de reservas
void free_reservas_array(Reservas **reservas, int count);

#endif
