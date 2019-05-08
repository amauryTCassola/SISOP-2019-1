#
# Makefile de EXEMPLO
#
# OBRIGATÓRIO ter uma regra "all" para geração da biblioteca e de uma
# regra "clean" para remover todos os objetos gerados.
#
# É NECESSARIO ADAPTAR ESSE ARQUIVO de makefile para suas necessidades.
#  1. Cuidado com a regra "clean" para não apagar o "support.o"
#
# OBSERVAR que as variáveis de ambiente consideram que o Makefile está no diretótio "cthread"
# 

CC=gcc
LIB_DIR=./lib
INC_DIR=./include
BIN_DIR=./bin
SRC_DIR=./src
OBJS= $(BIN_DIR)/support.o $(BIN_DIR)/utils.o $(BIN_DIR)/lib.o 

all: regra1 regra2 regraLib

regra1: #dependências para a regra1
	$(CC) -c  $(SRC_DIR)/utils.c -o $(BIN_DIR)/utils.o -Wall

regra2: #dependências para a regra2
	$(CC) -c $(SRC_DIR)/lib.c -o $(BIN_DIR)/lib.o -Wall

regraLib: #dependências para a regraLib
	ar crs $(LIB_DIR)/libcthread.a $(OBJS)

clean:
	find $(BIN_DIR)/*.o ! -name 'support.o' -type f -exec rm -f {} +
	rm -rf $(LIB_DIR)/*.a


