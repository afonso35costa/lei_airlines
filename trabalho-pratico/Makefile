#Compilador usado
CC = gcc

# Flags a usar para compilação
# - Wall: mostrar todos os warnings
# - Iinclude: diretoria para os ficheiros header locais
# - `pkg-config --cflags glib-2.0`: diretorias dos ficheiros header da glib (opcional, só
# necessário se usar glib),→
CFLAGS = -Wall -Iinclude `pkg-config --cflags glib-2.0`

# Flags a usar para linkagem
# - `pkg-config --libs glib-2.0`: biblioteca glib (opcional, só necessário se usar glib)
# - -lm: biblioteca matemática (opcional, só necessário se usar funções matemáticas)
LDFLAGS = `pkg-config --libs glib-2.0` -lm

# Executável chamado 'program'.
#
# Para o gerar, linkamos todos os ficheiros .o e as bibliotecas glib e math.
# Usamos $(NAME) para usar a variável NAME.
# $@ é equivalente ao objetivo. Neste caso, $@ avalia para: program
# $^ significa todos os pré-requisitos: Neste caso, avalia para: src/main.o src/file1.o src/file2.o
# Neste exemplo, temos a seguinte regra:
# gcc `pkg-config --libs glib-2.0` -lm -Wall -Iinclude `pkg-config --cflags glib-2.0` src/main.o
# src/gestor_voos.o -o program
#
# Como esta é a primeira regra, será a que é chamada ao executar 'make' sem argumentos.
# Ou seja, 'make' é equivalente a 'make program'.
#
# EXEMPLO COMPLETO

# Para executar esta regra, o make irá primeiro precisar de executar as regras 'src/main.o',
# 'src/file1.o' e 'src/file2.o', como especificado na lista de pré-requisitos (à direita)
program: src/main.o src/gestor_voos.o
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

# Aqui começam as regras de compilação dos ficheiros fonte.
# Uma regra vazia é equivalente a:
# $(CC) $(CPPFLAGS) $(CFLAGS) -c <left param> <right param>
# Sendo assim, definimos o objetivo (left) como o nome do ficheiro objeto a ser gerado
# e o nome do ficheiro fonte na lista de pré-requisitos (right).

# Esta regra específica é equivalente a:
# gcc -Wall -Iinclude `pkg-config --cflags glib-2.0` -c -o src/main.o src/main.c
src/main.o: src/main.c

# Equivalente à regra acima
# src/main.o: src/main.c
# $(CC) $(CFLAGS) -c -o $@ $<

src/gestor_voos.o: src/gestor_voos.c

# Objetivo padrão que compila tudo
all: program

# A regra de limpeza vai remover o executável ('program') e os ficheiros objeto (*.o).
# Para a executar, devemos usar 'make clean'.
clean:
	rm -f program src/*.o
