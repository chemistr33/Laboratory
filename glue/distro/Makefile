#################################################################################
#                        Author: B3n	                                        #
#      Makefile for creating a binary using include/glue.h and lib/libglue.so	#
#################################################################################

CC = gcc
CFLAGS = -Wall -Werror -g
SRC_DIR = $(realpath src)
INC_DIR = $(realpath include)
LIB_DIR = $(realpath lib)
LIB = -lglue
BIN_DIR = $(realpath bin)
SRC_FILE ?= test.c	
BIN_FILE ?= glue

all: $(BIN_DIR)/$(BIN_FILE)

$(BIN_DIR)/$(BIN_FILE): $(SRC_DIR)/$(SRC_FILE)
	$(CC) $(CFLAGS) -I$(INC_DIR) -L$(LIB_DIR) -o $@ $< $(LIB)

clean:
	rm -f $(BIN_DIR)/$(BIN_FILE)


#################################################################################




