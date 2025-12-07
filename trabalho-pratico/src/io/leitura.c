#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leitura.h"

//Função que abre ficheiros para leitura
FILE* abrir_ficheiro_leitura(const char* csv_path, const char* filename) {
    char path[512];
    snprintf(path, sizeof(path), "%s/%s", csv_path, filename);
    FILE *f = fopen(path, "r");
    if (!f) {
        perror(path);
    }
    return f;
}

