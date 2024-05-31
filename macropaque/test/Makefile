# Compiler
CC = gcc

# Directories
SRC_DIR = ../source
INCLUDE_DIR = ../include
LIB_DIR = ../library
OBJ_DIR = ../objects
TEST_DIR = .

# Compiler flags
CFLAGS = -Wall -I$(INCLUDE_DIR) -fpic -g

# Libraries
LIBS = -L$(LIB_DIR) -loglist

# Source and Object files
SRC = $(TEST_DIR)/main.c
OBJ = $(OBJ_DIR)/main.o

# Output binary
OUT = $(TEST_DIR)/test_app

.PHONY: all clean

all: $(OUT)

$(OUT): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $@

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OUT) $(OBJ)
