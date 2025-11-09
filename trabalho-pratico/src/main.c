#include "sistema.h"

int main() {
    Sistema *s = criar_sistema();

    carregar_tudo(s, "dados"); // pasta onde tens os .csv

    // aqui no futuro fazemos as QUERIES ⚡

    libertar_sistema(s);
    return 0;
}
