#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "passageiros.h"
#include "gestor_passageiros.h"

// Estrutura do gestor de passageiros
typedef struct gestor_passageiros {
    Passageiros **passageiros;     // Array dinâmico de passageiros
    int count;                     // Número atual de passageiros
    int capacity;                  // Capacidade atual do array
    bool sorted;                   // Flag se está ordenado
} GestorPassageiros;

// =============================================================================================
// FUNÇÕES DE GESTÃO DE MEMÓRIA
// ===========================================

GestorPassageiros* create_gestor_passageiros(void) {
    GestorPassageiros *gestor = malloc(sizeof(GestorPassageiros));
    if (gestor == NULL) return NULL;
    
    gestor->capacity = 100;  // Capacidade inicial
    gestor->passageiros = malloc(gestor->capacity * sizeof(Passageiros*));
    if (gestor->passageiros == NULL) {
        free(gestor);
        return NULL;
    }
    
    gestor->count = 0;
    gestor->sorted = true;  // Array vazio está "ordenado"
    
    return gestor;
}

void destroy_gestor_passageiros(GestorPassageiros *gestor) {
    if (gestor == NULL) return;
    
    // Liberta todos os passageiros
    for (int i = 0; i < gestor->count; i++) {
        destroy_passageiro(gestor->passageiros[i]);
    }
    
    // Liberta o array e o gestor
    free(gestor->passageiros);
    free(gestor);
}

// ===========================================
// FUNÇÕES DE MANIPULAÇÃO
// ===========================================

// Redimensiona o array se necessário
static bool resize_if_needed(GestorPassageiros *gestor) {
    if (gestor->count >= gestor->capacity) {
        int new_capacity = gestor->capacity * 2;
        Passageiros **new_array = realloc(gestor->passageiros, 
                                         new_capacity * sizeof(Passageiros*));
        if (new_array == NULL) return false;
        
        gestor->passageiros = new_array;
        gestor->capacity = new_capacity;
    }
    return true;
}

bool add_passageiro(GestorPassageiros *gestor, Passageiros *passageiro) {
    if (gestor == NULL || passageiro == NULL) return false;
    
    // Verifica se já existe (evita duplicados)
    if (find_passageiro_by_document(gestor, get_document_number(passageiro)) != NULL) {
        printf("AVISO: Passageiro com documento %s já existe\n", 
               get_document_number(passageiro));
        return false;
    }
    
    // Redimensiona se necessário
    if (!resize_if_needed(gestor)) return false;
    
    // Adiciona o passageiro
    gestor->passageiros[gestor->count] = passageiro;
    gestor->count++;
    gestor->sorted = false;  // Array já não está ordenado
    
    return true;
}

bool remove_passageiro(GestorPassageiros *gestor, const char *document_number) {
    if (gestor == NULL || document_number == NULL) return false;
    
    // Procura o passageiro
    for (int i = 0; i < gestor->count; i++) {
        if (strcmp(get_document_number(gestor->passageiros[i]), document_number) == 0) {
            // Liberta o passageiro
            destroy_passageiro(gestor->passageiros[i]);
            
            // Move todos os elementos para trás
            for (int j = i; j < gestor->count - 1; j++) {
                gestor->passageiros[j] = gestor->passageiros[j + 1];
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

Passageiros* find_passageiro_by_document(GestorPassageiros *gestor, const char *document_number) {
    if (gestor == NULL || document_number == NULL) return NULL;
    
    for (int i = 0; i < gestor->count; i++) {
        char *doc = get_document_number(gestor->passageiros[i]);
        if (doc != NULL && strcmp(doc, document_number) == 0) {
            return gestor->passageiros[i];
        }
    }
    
    return NULL;
}

Passageiros** find_passageiros_by_name(GestorPassageiros *gestor, const char *name, int *found_count) {
    if (gestor == NULL || name == NULL || found_count == NULL) return NULL;
    
    *found_count = 0;
    Passageiros **results = malloc(gestor->count * sizeof(Passageiros*));
    if (results == NULL) return NULL;
    
    for (int i = 0; i < gestor->count; i++) {
        char *first_name = get_first_name(gestor->passageiros[i]);
        char *last_name = get_last_name(gestor->passageiros[i]);
        
        if ((first_name && strstr(first_name, name) != NULL) ||
            (last_name && strstr(last_name, name) != NULL)) {
            results[*found_count] = gestor->passageiros[i];
            (*found_count)++;
        }
    }
    
    if (*found_count == 0) {
        free(results);
        return NULL;
    }
    
    return results;
}

Passageiros** find_passageiros_by_nationality(GestorPassageiros *gestor, const char *nationality, int *found_count) {
    if (gestor == NULL || nationality == NULL || found_count == NULL) return NULL;
    
    *found_count = 0;
    Passageiros **results = malloc(gestor->count * sizeof(Passageiros*));
    if (results == NULL) return NULL;
    
    for (int i = 0; i < gestor->count; i++) {
        char *nat = get_nationality(gestor->passageiros[i]);
        if (nat != NULL && strcmp(nat, nationality) == 0) {
            results[*found_count] = gestor->passageiros[i];
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

void sort_passageiros(GestorPassageiros *gestor) {
    if (gestor == NULL || gestor->sorted) return;
    
    // Bubble sort (simples para começar)
    for (int i = 0; i < gestor->count - 1; i++) {
        for (int j = 0; j < gestor->count - i - 1; j++) {
            if (compare_passageiros(gestor->passageiros[j], gestor->passageiros[j + 1]) > 0) {
                // Troca
                Passageiros *temp = gestor->passageiros[j];
                gestor->passageiros[j] = gestor->passageiros[j + 1];
                gestor->passageiros[j + 1] = temp;
            }
        }
    }
    
    gestor->sorted = true;
}

// ===========================================
// FUNÇÕES DE CARREGAMENTO
// ===========================================

bool load_passageiros_to_gestor(GestorPassageiros *gestor, const char *filename) {
    if (gestor == NULL || filename == NULL) return false;
    
    Passageiros **passageiros_array;
    int count;
    
    // Carrega do ficheiro CSV
    if (load_passageiros_from_file(filename, &passageiros_array, &count) != 0) {
        return false;
    }
    
    // Adiciona cada passageiro ao gestor
    int added = 0;
    for (int i = 0; i < count; i++) {
        if (add_passageiro(gestor, passageiros_array[i])) {
            added++;
        } else {
            destroy_passageiro(passageiros_array[i]);  // Liberta se não conseguiu adicionar
        }
    }
    
    free(passageiros_array);  // Liberta só o array, não os passageiros
    
    printf("Adicionados %d/%d passageiros ao gestor\n", added, count);
    return added > 0;
}

// ===========================================
// FUNÇÕES DE INFORMAÇÃO
// ===========================================

int get_passageiros_count(GestorPassageiros *gestor) {
    return (gestor != NULL) ? gestor->count : 0;
}

void print_all_passageiros(GestorPassageiros *gestor) {
    if (gestor == NULL) {
        printf("Gestor inválido\n");
        return;
    }
    
    printf("=== LISTA DE PASSAGEIROS (%d total) ===\n", gestor->count);
    for (int i = 0; i < gestor->count; i++) {
        printf("\n--- Passageiro %d ---\n", i + 1);
        print_passageiro(gestor->passageiros[i]);
    }
    printf("================================\n");
}

void print_passageiros_summary(GestorPassageiros *gestor) {
    if (gestor == NULL) {
        printf("Gestor inválido\n");
        return;
    }
    
    printf("=== RESUMO DE PASSAGEIROS ===\n");
    printf("Total: %d passageiros\n", gestor->count);
    printf("Capacidade: %d\n", gestor->capacity);
    printf("Ordenado: %s\n", gestor->sorted ? "Sim" : "Não");
    
    // Conta por nacionalidade
    // TODO: Implementar estatísticas mais detalhadas
    
    printf("============================\n");
}

// ===========================================
// FUNÇÕES DE VALIDAÇÃO
// ===========================================

bool validate_all_passageiros(GestorPassageiros *gestor) {
    if (gestor == NULL) return false;
    
    bool all_valid = true;
    for (int i = 0; i < gestor->count; i++) {
        if (!validate_passageiro(gestor->passageiros[i])) {
            printf("ERRO: Passageiro %d inválido\n", i + 1);
            all_valid = false;
        }
    }
    
    return all_valid;
}