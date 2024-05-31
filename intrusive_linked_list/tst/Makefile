# tst/Makefile
CC = gcc
CFLAGS = -Wall -g -fPIC -I../inc
LDFLAGS = -L/usr/local/lib -Wl,-rpath,/usr/local/lib -lintrusive

SRCDIR = .
BUILDDIR = .
INCDIR = ../inc
OBJDIR = ../obj
LIBDIR = ../lib

SRCFILES = $(wildcard $(SRCDIR)/*.c)
OBJFILES = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCFILES))
INCFILES = $(wildcard $(INCDIR)/*.h)
LIBNAME = libintrusive.so
EXENAME = test

all: $(BUILDDIR)/$(EXENAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCFILES)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILDDIR)/$(EXENAME): $(OBJFILES)
	$(CC) $^ $(LDFLAGS) -o $@

clean:
	rm -f $(BUILDDIR)/$(EXENAME) $(OBJFILES)

.phony: all clean
