CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g -DDEBUG
GLIB_CFLAGS = `pkg-config --cflags glib-2.0`
GLIB_LIBS = `pkg-config --libs glib-2.0`

# Diretórios corretos (assumindo que tests/ está na raiz do projeto)
SRCDIR = ../src
INCDIR = ../include

# Só incluir ficheiros que existem
EXISTING_SOURCES = ../src/gestores/gestor_aeroportos.c \
                  ../src/gestores/gestor_aeronaves.c \
                  ../src/gestores/gestor_voos.c \
                  ../src/gestores/queries.c

# Assumindo que as entidades podem não estar completas
ENTITY_SOURCES = $(wildcard ../src/entidades/*.c)

# Parsing se existir
PARSING_SOURCES = $(wildcard ../src/parsing/*.c)

ALL_SOURCES = $(EXISTING_SOURCES) $(ENTITY_SOURCES) $(PARSING_SOURCES)

# Regra principal
test_queries: test_queries.c $(ALL_SOURCES)
    $(CC) $(CFLAGS) $(GLIB_CFLAGS) -I$(INCDIR) -o test_queries test_queries.c $(ALL_SOURCES) $(GLIB_LIBS)

# Regra mais segura que verifica ficheiros
test_safe: test_queries.c
    @echo "Compilando apenas ficheiros que existem..."
    $(CC) $(CFLAGS) $(GLIB_CFLAGS) -I$(INCDIR) -o test_queries test_queries.c $(wildcard $(ALL_SOURCES)) $(GLIB_LIBS) 2>/dev/null || echo "Alguns ficheiros podem estar em falta"

run_tests: test_queries
    @echo "Executando testes das queries..."
    ./test_queries

# Lista ficheiros que faltam
check_files:
    @echo "Verificando ficheiros necessários..."
    @for file in $(ALL_SOURCES); do \
        if [ -f "$$file" ]; then \
            echo "✅ $$file"; \
        else \
            echo "❌ $$file (EM FALTA)"; \
        fi \
    done

clean:
    rm -f test_queries

.PHONY: run_tests test_safe check_files clean