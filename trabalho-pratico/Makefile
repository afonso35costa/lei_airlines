# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g -DDEBUG
GLIB_CFLAGS = `pkg-config --cflags glib-2.0`
GLIB_LIBS = `pkg-config --libs glib-2.0`

# Diretórios
SRCDIR = ../src
INCDIR = ../include

# Fontes
EXISTING_SOURCES = $(SRCDIR)/gestores/gestor_aeroportos.c \
                   $(SRCDIR)/gestores/gestor_aeronaves.c \
                   $(SRCDIR)/gestores/gestor_voos.c \
                   $(SRCDIR)/gestores/queries.c

ENTITY_SOURCES = $(wildcard $(SRCDIR)/entidades/*.c)
PARSING_SOURCES = $(wildcard $(SRCDIR)/parsing/*.c)

ALL_SOURCES = $(EXISTING_SOURCES) $(ENTITY_SOURCES) $(PARSING_SOURCES)

# Targets dos executáveis
PROGRAM_PRINCIPAL = programa-principal
PROGRAM_TESTES = programa-testes

# ------------------------------
# Programa Principal
# ------------------------------
$(PROGRAM_PRINCIPAL): main.c $(ALL_SOURCES)
	$(CC) $(CFLAGS) $(GLIB_CFLAGS) -I$(INCDIR) -o $(PROGRAM_PRINCIPAL) main.c $(ALL_SOURCES) $(GLIB_LIBS)

# ------------------------------
# Programa Testes
# ------------------------------
$(PROGRAM_TESTES): main_testes.c $(ALL_SOURCES)
	$(CC) $(CFLAGS) $(GLIB_CFLAGS) -I$(INCDIR) -o $(PROGRAM_TESTES) main_testes.c $(ALL_SOURCES) $(GLIB_LIBS)

# ------------------------------
# Verificação de ficheiros
# ------------------------------
check_files:
	@echo "Verificando ficheiros necessários..."
	@for file in $(ALL_SOURCES); do \
		if [ -f "$$file" ]; then \
			echo "✅ $$file"; \
		else \
			echo "❌ $$file (EM FALTA)"; \
		fi \
	done

# ------------------------------
# Limpeza
# ------------------------------
clean:
	rm -f $(PROGRAM_PRINCIPAL) $(PROGRAM_TESTES) *.o

# Phony
.PHONY: check_files clean