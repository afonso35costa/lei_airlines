#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "passageiros.h"

typedef struct passageiros {
    char *document_number; // número do documento de identificação
    char *first_name;      // primeiro nome
    char *last_name;       // apelido
    char *dob;             // data de nascimento (aaaa-mm-dd)
    char *nationality;     // nacionalidade
    char *gender;          // género (M, F, O)
    char *email;           // email
    char *phone;           // número de telefone
    char *address;         // morada
    char *photo;           // fotografia (ficheiro ou URL)
} Passageiros;

// FUNÇÃO CONSTRUTORA - Função para criar um novo passageiro e alocar a memória necessária

Passageiros* create_passageiro(void) {
    Passageiros *p = malloc(sizeof(Passageiros));
    if (p == NULL) {
        return NULL;
    }
    
    // Inicializa todos os ponteiros como NULL
    p->document_number = NULL;
    p->first_name = NULL;
    p->last_name = NULL;
    p->dob = NULL;
    p->nationality = NULL;
    p->gender = NULL;
    p->email = NULL;
    p->phone = NULL;
    p->address = NULL;
    p->photo = NULL;
    
    return p;
}

// FUNÇÃO INICIALIZADORA - Função que inicializa os campos de um passageiro com valores padrão

Passageiros* init_passageiro(const char *document_number, const char *first_name, const char *last_name, 
                             const char *dob, const char *nationality, const char *gender,
                             const char *email, const char *phone, const char *address, const char *photo) {
    Passageiros *p = create_passageiro();
    if (p == NULL) return NULL;
    
    // Aloca e copia cada string (strdup faz malloc + strcpy)
    p->document_number = strdup(document_number);
    p->first_name = strdup(first_name);
    p->last_name = strdup(last_name);
    p->dob = strdup(dob);
    p->nationality = strdup(nationality);
    p->gender = strdup(gender);
    p->email = strdup(email);
    p->phone = strdup(phone);
    p->address = strdup(address);
    p->photo = strdup(photo);

    return p;
}

// FUNÇÃO DE COMPARAÇÃO - comparar dois passageiros (necessária para ordenação e pesquisa nas diferentes estruturas de dados)
int compare_passageiros(const Passageiros *p1, const Passageiros *p2) {
    if (p1 == NULL && p2 == NULL) return 0;
    if (p1 == NULL) return -1;
    if (p2 == NULL) return 1;
    
    // Compara pelo documento (chave única)
    char *doc1 = get_document_number_passageiros(p1);
    char *doc2 = get_document_number_passageiros(p2);
    
    if (doc1 == NULL && doc2 == NULL) return 0;
    if (doc1 == NULL) return -1;
    if (doc2 == NULL) return 1;
    
    return strcmp(doc1, doc2);
}

// FUNÇÃO DE IMPRESSÃO - mostrar dados do passageiro 
void print_passageiro(const Passageiros *p) {
    if (p == NULL) {
        printf("Passageiro inválido\n");
        return;
    }
    
    printf("=== PASSAGEIRO ===\n");
    printf("Documento: %s\n", get_document_number_passageiros(p) ? get_document_number_passageiros(p) : "N/A");
    printf("Nome: %s %s\n", get_first_name_passageiros(p) ? get_first_name_passageiros(p) : "", get_last_name_passageiros(p) ? get_last_name_passageiros(p) : "");
    printf("Data nascimento: %s\n", get_dob_passageiros(p) ? get_dob_passageiros(p) : "N/A");
    printf("Nacionalidade: %s\n", get_nationality_passageiros(p) ? get_nationality_passageiros(p) : "N/A");
    printf("Género: %s\n", get_gender_passageiros(p) ? get_gender_passageiros(p) : "N/A");
    printf("Email: %s\n", get_email_passageiros(p) ? get_email_passageiros(p) : "N/A");
    printf("Telefone: %s\n", get_phone_passageiros(p) ? get_phone_passageiros(p) : "N/A");
    printf("Morada: %s\n", get_address_passageiros(p) ? get_address_passageiros(p) : "N/A");
    printf("Fotografia: %s\n", get_photo_passageiros(p) ? get_photo_passageiros(p) : "N/A");
    printf("==================\n");
}

// FUNÇÃO DESTRUTORA -Função que liberta toda a memória associada a um passageiro 

void destroy_passageiro(Passageiros *p) {
    if (p == NULL) return;
    
    // Liberta cada string alocada
    free(p->document_number);
    free(p->first_name);
    free(p->last_name);
    free(p->dob);
    free(p->nationality);
    free(p->gender);
    free(p->email);
    free(p->phone);
    free(p->address);
    free(p->photo);
    
    // Liberta a estrutura principal
    free(p);
}


// ============================================================================================================================================
// GETTERS - Funções para obter valores
// ============================================================================================================================================

char* get_document_number_passageiros(const Passageiros *p) {
    return (p != NULL) ? p->document_number : NULL;
}

char* get_first_name_passageiros(const Passageiros *p) {
    return (p != NULL) ? p->first_name : NULL;
}

char* get_last_name_passageiros(const Passageiros *p) {
    return (p != NULL) ? p->last_name : NULL;
}

char* get_dob_passageiros(const Passageiros *p) {
    return (p != NULL) ? p->dob : NULL;
}

char* get_nationality_passageiros(const Passageiros *p) {
    return (p != NULL) ? p->nationality : NULL;
}

char* get_gender_passageiros(const Passageiros *p) {
    return (p != NULL) ? p->gender : NULL;
}

char* get_email_passageiros(const Passageiros *p) {
    return (p != NULL) ? p->email : NULL;
}

char* get_phone_passageiros(const Passageiros *p) {
    return (p != NULL) ? p->phone : NULL;
}

char* get_address_passageiros(const Passageiros *p) {
    return (p != NULL) ? p->address : NULL;
}

char* get_photo_passageiros(const Passageiros *p) {
    return (p != NULL) ? p->photo : NULL;
}

// ===========================================================================================
// SETTERS - Funções para definir valores
// ===========================================================================================

void set_document_number_passageiros(Passageiros *p, const char *doc) {
    if (p == NULL) return;
    free(p->document_number);
    p->document_number = doc ? strdup(doc) : NULL;
}

void set_first_name_passageiros(Passageiros *p, const char *name) {
    if (p == NULL) return;
    free(p->first_name);
    p->first_name = name ? strdup(name) : NULL;
}

void set_last_name_passageiros(Passageiros *p, const char *name) {
    if (p == NULL) return;
    free(p->last_name);
    p->last_name = name ? strdup(name) : NULL;
}

void set_dob_passageiros(Passageiros *p, const char *birth) {
    if (p == NULL) return;
    free(p->dob);
    p->dob = birth ? strdup(birth) : NULL;
}

void set_nationality_passageiros(Passageiros *p, const char *nat) {
    if (p == NULL) return;
    free(p->nationality);
    p->nationality = nat ? strdup(nat) : NULL;
}

void set_gender_passageiros(Passageiros *p, const char *gen) {
    if (p == NULL) return;
    free(p->gender);
    p->gender = gen ? strdup(gen) : NULL;
}

void set_email_passageiros(Passageiros *p, const char *mail) {
    if (p == NULL) return;
    free(p->email);
    p->email = mail ? strdup(mail) : NULL;
}

void set_phone_passageiros(Passageiros *p, const char *tel) {
    if (p == NULL) return;
    free(p->phone);
    p->phone = tel ? strdup(tel) : NULL;
}

void set_address_passageiros(Passageiros *p, const char *addr) {
    if (p == NULL) return;
    free(p->address);
    p->address = addr ? strdup(addr) : NULL;
}

void set_photo_passageiros(Passageiros *p, const char *pic) {
    if (p == NULL) return;
    free(p->photo);
    p->photo = pic ? strdup(pic) : NULL;
}
