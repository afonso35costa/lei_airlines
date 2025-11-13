# Compilador e flags
# ------------------------------
CC = gcc
CFLAGS = -Wall -Wextra -g -DDEBUG
#GLIB_CFLAGS = `pkg-config --cflags glib-2.0`
#GLIB_LIBS = `pkg-config --libs glib-2.0`

#PKG_CONFIG_PATH=/usr/local/lib/pkgconfig
GLIB_CFLAGS = `pkg-config --cflags glib-2.0`
GLIB_LIBS   = `pkg-config --libs glib-2.0`

# ------------------------------
# Diretórios
# ------------------------------
SRCDIR = src
INCDIR = include

# ------------------------------
# Fontes
# ------------------------------
EXISTING_SOURCES = $(SRCDIR)/gestores/gestor_aeroportos.c \
                   $(SRCDIR)/gestores/gestor_aeronaves.c \
                   $(SRCDIR)/gestores/gestor_voos.c \
                   $(SRCDIR)/gestores/queries.c \
				   $(SRCDIR)/utils/datas.c \
				   $(SRCDIR)/utils/parser_utils.c \
				   $(SRCDIR)/validacao/validacao_aeronaves.c \
				   $(SRCDIR)/validacao/validacao_voos.c \
				   $(SRCDIR)/validacao/validacao_aeroportos.c \
				   $(SRCDIR)/validacao/validacao_passageiros.c \
				   $(SRCDIR)/validacao/validacao_reservas.c

ENTITY_SOURCES = $(wildcard $(SRCDIR)/entidades/*.c)
PARSING_SOURCES = $(wildcard $(SRCDIR)/parsing/*.c)

ALL_SOURCES = $(EXISTING_SOURCES) $(ENTITY_SOURCES) $(PARSING_SOURCES)

# ------------------------------
# Executáveis
# ------------------------------
PROGRAM_PRINCIPAL = programa-principal
PROGRAM_TESTES = programa-testes

# ------------------------------
# Includes para subpastas
# ------------------------------
INCLUDE_DIRS = -I$(INCDIR) -I$(INCDIR)/entidades -I$(INCDIR)/gestores -I$(INCDIR)/parsing -I$(INCDIR)/utils -I$(INCDIR)/validacao

# ------------------------------
# Regras principais
# ------------------------------
$(PROGRAM_PRINCIPAL): $(SRCDIR)/main.c $(ALL_SOURCES)
	$(CC) $(CFLAGS) $(GLIB_CFLAGS) $(INCLUDE_DIRS) -o $(PROGRAM_PRINCIPAL) $(SRCDIR)/main.c $(ALL_SOURCES) $(GLIB_LIBS)

$(PROGRAM_TESTES): $(SRCDIR)/main_testes.c $(ALL_SOURCES)
	$(CC) $(CFLAGS) $(GLIB_CFLAGS) $(INCLUDE_DIRS) -o $(PROGRAM_TESTES) $(SRCDIR)/main_testes.c $(ALL_SOURCES) $(GLIB_LIBS)


# ------------------------------
# Limpeza
# ------------------------------
clean:
	rm -f $(PROGRAM_PRINCIPAL) $(PROGRAM_TESTES) *.o
	rm -f resultados/*.csv || true
	rm -f resultados/*.txt || true

# ------------------------------
# Phony
# ------------------------------
.PHONY: check_files clean