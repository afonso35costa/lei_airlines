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
    p->document_number = document_number ? strdup(document_number) : NULL;
    p->first_name = first_name ? strdup(first_name) : NULL;
    p->last_name = last_name ? strdup(last_name) : NULL;
    p->dob = dob ? strdup(dob) : NULL;
    p->nationality = nationality ? strdup(nationality) : NULL;
    p->gender = gender ? strdup(gender) : NULL;
    p->email = email ? strdup(email) : NULL;
    p->phone = phone ? strdup(phone) : NULL;
    p->address = address ? strdup(address) : NULL;
    p->photo = photo ? strdup(photo) : NULL;
    
    return p;
}

// FUNÇÃO DE COMPARAÇÃO - comparar dois passageiros (necessária para ordenação e pesquisa nas diferentes estruturas de dados)
int compare_passageiros(const Passageiros *p1, const Passageiros *p2) {
    if (p1 == NULL && p2 == NULL) return 0;
    if (p1 == NULL) return -1;
    if (p2 == NULL) return 1;
    
    // Compara pelo documento (chave única)
    char *doc1 = get_document_number(p1);
    char *doc2 = get_document_number(p2);
    
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
    printf("Documento: %s\n", get_document_number(p) ? get_document_number(p) : "N/A");
    printf("Nome: %s %s\n", get_first_name(p) ? get_first_name(p) : "", get_last_name(p) ? get_last_name(p) : "");
    printf("Data nascimento: %s\n", get_dob(p) ? get_dob(p) : "N/A");
    printf("Nacionalidade: %s\n", get_nationality(p) ? get_nationality(p) : "N/A");
    printf("Género: %s\n", get_gender(p) ? get_gender(p) : "N/A");
    printf("Email: %s\n", get_email(p) ? get_email(p) : "N/A");
    printf("Telefone: %s\n", get_phone(p) ? get_phone(p) : "N/A");
    printf("Morada: %s\n", get_address(p) ? get_address(p) : "N/A");
    printf("Fotografia: %s\n", get_photo(p) ? get_photo(p) : "N/A");
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

char* get_document_number(const Passageiros *p) {
    return (p != NULL) ? p->document_number : NULL;
}

char* get_first_name(const Passageiros *p) {
    return (p != NULL) ? p->first_name : NULL;
}

char* get_last_name(const Passageiros *p) {
    return (p != NULL) ? p->last_name : NULL;
}

char* get_dob(const Passageiros *p) {
    return (p != NULL) ? p->dob : NULL;
}

char* get_nationality(const Passageiros *p) {
    return (p != NULL) ? p->nationality : NULL;
}

char* get_gender(const Passageiros *p) {
    return (p != NULL) ? p->gender : NULL;
}

char* get_email(const Passageiros *p) {
    return (p != NULL) ? p->email : NULL;
}

char* get_phone(const Passageiros *p) {
    return (p != NULL) ? p->phone : NULL;
}

char* get_address(const Passageiros *p) {
    return (p != NULL) ? p->address : NULL;
}

char* get_photo(const Passageiros *p) {
    return (p != NULL) ? p->photo : NULL;
}

// ===========================================================================================
// SETTERS - Funções para definir valores
// ===========================================================================================

void set_document_number(Passageiros *p, const char *doc) {
    if (p == NULL) return;
    free(p->document_number);
    p->document_number = doc ? strdup(doc) : NULL;
}

void set_first_name(Passageiros *p, const char *name) {
    if (p == NULL) return;
    free(p->first_name);
    p->first_name = name ? strdup(name) : NULL;
}

void set_last_name(Passageiros *p, const char *name) {
    if (p == NULL) return;
    free(p->last_name);
    p->last_name = name ? strdup(name) : NULL;
}

void set_dob(Passageiros *p, const char *birth) {
    if (p == NULL) return;
    free(p->dob);
    p->dob = birth ? strdup(birth) : NULL;
}

void set_nationality(Passageiros *p, const char *nat) {
    if (p == NULL) return;
    free(p->nationality);
    p->nationality = nat ? strdup(nat) : NULL;
}

void set_gender(Passageiros *p, const char *gen) {
    if (p == NULL) return;
    free(p->gender);
    p->gender = gen ? strdup(gen) : NULL;
}

void set_email(Passageiros *p, const char *mail) {
    if (p == NULL) return;
    free(p->email);
    p->email = mail ? strdup(mail) : NULL;
}

void set_phone(Passageiros *p, const char *tel) {
    if (p == NULL) return;
    free(p->phone);
    p->phone = tel ? strdup(tel) : NULL;
}

void set_address(Passageiros *p, const char *addr) {
    if (p == NULL) return;
    free(p->address);
    p->address = addr ? strdup(addr) : NULL;
}

void set_photo(Passageiros *p, const char *pic) {
    if (p == NULL) return;
    free(p->photo);
    p->photo = pic ? strdup(pic) : NULL;
}


// ===========================================================================================
// PARSER - Funções para ler dados de ficheiros (datas em CSV)
// ===========================================================================================

// Função auxiliar para remover aspas de uma string
char* remove_quotes(char *str) {
    if (str == NULL) return NULL;
    
    int len = strlen(str);
    if (len >= 2 && str[0] == '"' && str[len-1] == '"') {
        str[len-1] = '\0';  // Remove a última aspa
        return str + 1;     // Retorna ponteiro após a primeira aspa
    }
    return str;
}

// Parse de uma linha CSV para criar um passageiro
Passageiros* parse_passageiro_from_csv(const char *linha) {
    if (linha == NULL) return NULL;
    
    // Copia a linha para poder modificá-la
    char *linha_copia = strdup(linha);
    if (linha_copia == NULL) return NULL;
    
    // Array para guardar os campos
    char *campos[10];
    int num_campos = 0;
    
    // Divide a linha pelos delimitadores ','
    char *token = strtok(linha_copia, ",");                     
    while (token != NULL && num_campos < 10) {
        campos[num_campos] = remove_quotes(token);
        num_campos++;
        token = strtok(NULL, ",");
    }
    
    // Verifica se tem todos os 10 campos
    if (num_campos < 10) {
        printf("AVISO: Linha com apenas %d campos (esperados 10)\n", num_campos);
        free(linha_copia);
        return NULL;
    }
    
    // Cria o passageiro com os dados
    Passageiros *p = init_passageiro(
        campos[0],  // document_number
        campos[1],  // first_name
        campos[2],  // last_name
        campos[3],  // dob
        campos[4],  // nationality
        campos[5],  // gender
        campos[6],  // email
        campos[7],  // phone
        campos[8],  // address
        campos[9]   // photo
    );
    
    free(linha_copia);
    return p;
}

// Carrega passageiros de um ficheiro CSV
int load_passageiros_from_file(const char *filename, Passageiros ***passageiros, int *count) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("ERRO: Não foi possível abrir o ficheiro %s\n", filename);
        return -1;
    }
    
    // Array dinâmico para guardar os passageiros
    int capacity = 100;  // Capacidade inicial
    *passageiros = malloc(capacity * sizeof(Passageiros*));
    *count = 0;
    
    char linha[4096];  // Buffer maior para linhas com fotos Base64
    
    // Pula a primeira linha (cabeçalho)
    if (fgets(linha, sizeof(linha), file) == NULL) {
        fclose(file);
        free(*passageiros);
        return -1;
    }
    
    // Lê linha por linha
    while (fgets(linha, sizeof(linha), file)) {
        // Remove o '\n' no final
        linha[strcspn(linha, "\n")] = 0;
        
        // Parse da linha
        Passageiros *p = parse_passageiro_from_csv(linha);
        if (p != NULL && validate_passageiro(p)) {
            // Aumenta o array se necessário
            if (*count >= capacity) {
                capacity *= 2;
                *passageiros = realloc(*passageiros, capacity * sizeof(Passageiros*));
            }
            
            (*passageiros)[*count] = p;
            (*count)++;
        } else if (p != NULL) {
            destroy_passageiro(p);  // Liberta passageiro inválido
        }
    }
    
    fclose(file);
    printf("Carregados %d passageiros do ficheiro %s\n", *count, filename);
    return 0;
}

// Função para libertar array de passageiros
void free_passageiros_array(Passageiros **passageiros, int count) {
    for (int i = 0; i < count; i++) {
        destroy_passageiro(passageiros[i]);
    }
    free(passageiros);
}