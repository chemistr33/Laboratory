# lib/Makefile
# sudo make install - to install the library to /usr/local/lib and run ldconfig

CC = gcc
CFLAGS = -Wall -g -fPIC
LDFLAGS = -shared

SRCDIR = src
INCDIR = inc 
OBJDIR = obj
LIBDIR = lib

SRCFILES = $(wildcard $(SRCDIR)/*.c)
OBJFILES = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCFILES))
INCFILES = $(wildcard $(INCDIR)/*.h)
LIBNAME = libintrusive.so

.phony: all clean

all: $(LIBDIR)/$(LIBNAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCFILES)
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

$(LIBDIR)/$(LIBNAME): $(OBJFILES)
	$(CC) $(LDFLAGS) $^ -o $@

clean:
	rm -f $(LIBDIR)/$(LIBNAME) $(OBJFILES)

install:
	sudo cp -v $(LIBDIR)/$(LIBNAME) /usr/local/lib
	sudo ldconfig 

