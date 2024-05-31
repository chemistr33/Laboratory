######################################################################
#                        Author: B3n	                             #
#      Makefile for building a shared library and a binary file		 #
######################################################################

######################
# Compiler and flags #
######################
CC = gcc
CFLAGS = -Wall -Werror -fpic
LDFLAGS = -shared
INCLUDE_DIR = include

#########################
# Directories and files #
#########################
# Default value of SRC_FILE : test.c
# Default value of BIN_FILE : glue
SRC_DIR = src
SRC_FILE ?= test.c 
OBJ_DIR = obj
BIN_DIR = bin
LIBDIR = lib
BIN_FILE ?= glue

# Name of the shared library
LIBNAME = libglue.so

###################################
# Programmatic Makefile Variables #
###################################

# List of source files
SRCS = $(wildcard $(SRC_DIR)/*.c)

# List of object files
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# Path to the library file
LIBPATH = $(LIBDIR)/$(LIBNAME)

# Path to the binary file
BINPATH = $(BIN_DIR)/glue


################
# Make targets #
################

# Default target: build the library
all: $(LIBPATH)

# executable target: build the binary
glue: $(BINPATH)

################
#  Make rules  #
################

# Rule to build an object file
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c -o $@ $<

# Rule to build the shared library
$(LIBPATH): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

# Rule to build the binary
$(BINPATH): $(LIBPATH) $(SRC_DIR)/$(SRC_FILE)
	$(CC) -I$(INCLUDE_DIR) -L$(LIBDIR) -o $@ $^ -lglue 

# Clean rule
clean:
	rm -f $(OBJ_DIR)/*.o $(LIBPATH) $(BINPATH)

