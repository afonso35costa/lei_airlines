#ifndef LEITURA_H
#define LEITURA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Função que abre ficheiros para leitura
 * 
 * @param csv_path Caminho para o diretório dos ficheiros CSV
 * @param filename Nome do ficheiro a ser aberto
 * 
 * @return Ponteiro para o ficheiro aberto (FILE*)
 */
FILE* abrir_ficheiro_leitura(const char* csv_path, const char* filename);

#endif