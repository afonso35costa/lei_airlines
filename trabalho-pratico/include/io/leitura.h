#ifndef LEITURA_H
#define LEITURA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Função que abre ficheiros para leitura
FILE* abrir_ficheiro_leitura(const char* csv_path, const char* filename);

#endif