#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "validacao_passageiros.h"
#include "passageiros.h"

/*
// ============================================================
// FUNÇÕES INDIVIDUAIS DE VALIDAÇÃO
// ============================================================

// Documento de identificação (alfanumérico, 5–15 caracteres)
int validar_document_number(const char *document_number) {
    if (!document_number) return 0;
    int len = strlen(document_number);
    if (len < 5 || len > 15) return 0;
    for (int i = 0; i < len; i++) {
        if (!isalnum(document_number[i])) return 0;
    }
    return 1;
    
// Primeiro nome (só letras, tamanho 2–50)
int validar_first_name(const char *first_name) {
    if (!first_name) return 0;
    int len = strlen(first_name);
    if (len < 2 || len > 50) return 0;

    for (int i = 0; i < len; i++) {
        if (!isalpha(first_name[i]) && first_name[i] != ' ' && first_name[i] != '-') return 0;
    }
    return 1;
}

// Último nome (mesma regra do primeiro)
int validar_last_name(const char *last_name) {
    return validar_first_name(last_name);
}

// Data de nascimento (formato YYYY-MM-DD)
int validar_dob(const char *dob) {
    if (!dob) return 0;
    if (strlen(dob) != 10) return 0;
    if (dob[4] != '-' || dob[7] != '-') return 0;

    char ano[5], mes[3], dia[3];
    strncpy(ano, dob, 4); ano[4] = '\0';
    strncpy(mes, dob + 5, 2); mes[2] = '\0';
    strncpy(dia, dob + 8, 2); dia[2] = '\0';

    int y = atoi(ano), m = atoi(mes), d = atoi(dia);
    if (y < 1900 || y > 2025) return 0;
    if (m < 1 || m > 12) return 0;
    if (d < 1 || d > 31) return 0;

    return 1;
}

// Nacionalidade (só letras, mínimo 2)
int validar_nationality(const char *nationality) {
    if (!nationality) return 0;
    int len = strlen(nationality);
    if (len < 2) return 0;

    for (int i = 0; i < len; i++) {
        if (!isalpha(nationality[i]) && nationality[i] != ' ') return 0;
    }
    return 1;
}

// Género (M, F, ou outros valores válidos)
int validar_gender(const char *gender) {
    if (!gender) return 0;
    return (
        strcmp(gender, "M") == 0 ||
        strcmp(gender, "F") == 0 ||
        strcasecmp(gender, "Male") == 0 ||
        strcasecmp(gender, "Female") == 0 ||
        strcasecmp(gender, "Other") == 0
    );
}

// Email (deve conter '@' e '.')
int validar_email(const char *email) {
    if (!email) return 0;
    return (strchr(email, '@') && strchr(email, '.'));
}

// Telefone (só números, 9–15 dígitos)
int validar_phone(const char *phone) {
    if (!phone) return 0;
    int len = strlen(phone);
    if (len < 9 || len > 15) return 0;

    for (int i = 0; i < len; i++) {
        if (!isdigit(phone[i]) && phone[i] != '+') return 0;
    }
    return 1;
}

// Morada (não vazia, até 100 chars)
int validar_address(const char *address) {
    if (!address) return 0;
    int len = strlen(address);
    return (len >= 5 && len <= 100);
}

// Caminho da foto (termina com .jpg, .png, .jpeg)
int validar_photo(const char *photo) {
    if (!photo) return 0;
    const char *ext = strrchr(photo, '.');
    if (!ext) return 0;

    return (
        strcasecmp(ext, ".jpg") == 0 ||
        strcasecmp(ext, ".jpeg") == 0 ||
        strcasecmp(ext, ".png") == 0
    );
}
*/

int validar_document_number_passageiro(const char *document_number) {
    if (!document_number || strlen(document_number) != 9 ) return 0;
    for (int i = 0; i < strlen(document_number); i++) {
        if (!isalnum(document_number[i])) return 0;
    }
    return 1;
}

int validar_email_passageiro(const char *email) {
    if (!email) return 0;
    
    // Verificar se contém exatamente um @
    char *at_pos = strchr(email, '@');
    if (!at_pos || strchr(at_pos + 1, '@')) return 0;
    
    // Separar username e domínio
    int username_len = at_pos - email;
    if (username_len == 0) return 0; // Não pode começar com @
    
    char *domain = at_pos + 1;
    if (strlen(domain) == 0) return 0; // Deve ter domínio
    
    // Validar username: [a-z0-9] e '.'
    for (int i = 0; i < username_len; i++) {
        char c = email[i];
        if (!((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '.')) {
            return 0;
        }
    }
    
    // Validar domínio: deve ter exatamente um ponto
    char *dot_pos = strchr(domain, '.');
    if (!dot_pos || strchr(dot_pos + 1, '.')) return 0;
    
    // Separar lstring e rstring
    int lstring_len = dot_pos - domain;
    char *rstring = dot_pos + 1;
    int rstring_len = strlen(rstring);
    
    // lstring: 1 ou mais caracteres [a-z]
    if (lstring_len < 1) return 0;
    for (int i = 0; i < lstring_len; i++) {
        char c = domain[i];
        if (!(c >= 'a' && c <= 'z')) return 0;
    }
    
    // rstring: 2 ou 3 caracteres [a-z]
    if (rstring_len < 2 || rstring_len > 3) return 0;
    for (int i = 0; i < rstring_len; i++) {
        char c = rstring[i];
        if (!(c >= 'a' && c <= 'z')) return 0;
    }
    
    return 1;
}

int validar_genero_passageiro (const char *gender){
    if (!gender) return 0; // Verifica se o ponteiro é nulo
    if (strcmp(gender, "M") == 0 ||
        strcmp(gender, "F") == 0 ||
        strcmp(gender, "O") == 0) {
        return 1; 
    }
    return 0;

}

int validar_dob_passageiro (const char *dob) {
    if (!dob) return 0;
    if (strlen(dob) != 10) return 0;
    if (dob[4] != '-' || dob[7] != '-') return 0;

    char ano[5], mes[3], dia[3];
    strncpy(ano, dob, 4); ano[4] = '\0';
    strncpy(mes, dob + 5, 2); mes[2] = '\0';
    strncpy(dia, dob + 8, 2); dia[2] = '\0';

    int y = atoi(ano), m = atoi(mes), d = atoi(dia);
    if (y < 1900 || y > 2025) return 0;
    if (m < 1 || m > 12) return 0;
    if (d < 1 || d > 31) return 0;

    return 1;
}





// ============================================================
// VALIDAÇÃO GERAL (com encapsulamento)
// ============================================================
int validar_passageiro(const Passageiros *p) {
    if (!p) return 0;

    return validar_document_number_passageiro(get_document_number_passageiros(p)) &&
           validar_email_passageiro(get_email_passageiros(p)) &&
           validar_genero_passageiro (get_gender_passageiros(p));
}

/*
// ============================================================
// LEITURA DE FICHEIRO E GERAÇÃO DE FICHEIRO DE ERROS
// ============================================================
void processar_ficheiro_passageiros(const char *ficheiro_entrada, const char *ficheiro_erros) {
    FILE *fin = fopen(ficheiro_entrada, "r");
    if (!fin) {
        printf("Erro ao abrir ficheiro de entrada: %s\n", ficheiro_entrada);
        return;
    }

    FILE *ferr = fopen(ficheiro_erros, "w");
    if (!ferr) {
        printf("Erro ao criar ficheiro de erros: %s\n", ficheiro_erros);
        fclose(fin);
        return;
    }

    char linha[1024];
    int linha_num = 0;
    int validos = 0, invalidos = 0;

    // Cabeçalho do ficheiro de erros
    fprintf(ferr, "linha,erro\n");

    while (fgets(linha, sizeof(linha), fin)) {
        linha_num++;

        // Ignorar linha vazia
        if (strlen(linha) < 5) continue;

        // Remover \n do final
        linha[strcspn(linha, "\n")] = '\0';

        // Separar os 10 campos esperados
        char *token = strtok(linha, ",");
        char *campos[10];
        int i = 0;

        while (token && i < 10) {
            campos[i++] = token;
            token = strtok(NULL, ",");
        }

        // Verifica se a linha tem todos os campos
        if (i < 10) {
            fprintf(ferr, "%d,campos insuficientes\n", linha_num);
            invalidos++;
            continue;
        }

        // Criar e inicializar passageiro temporário
        Passageiros *p = init_passageiro(
            campos[0], campos[1], campos[2], campos[3], campos[4],
            campos[5], campos[6], campos[7], campos[8], campos[9]
        );

        if (!validar_passageiro(p)) {
            fprintf(ferr, "%d,campos inválidos\n", linha_num);
            invalidos++;
        } else {
            validos++;
        }

        free_passageiro(p);
    }

    fclose(fin);
    fclose(ferr);

    printf("Validação concluída ✅\n");
    printf("Registos válidos: %d\n", validos);
    printf("Registos inválidos: %d (ver ficheiro '%s')\n", invalidos, ficheiro_erros);
}

*/