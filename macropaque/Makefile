CC = gcc
CFLAGS = -Wall -fpic -g

SRCDIR = source
INCDIR = include
OBJDIR = objects
LIBDIR = library

SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SOURCES))
TARGET = $(LIBDIR)/liboglist.so

all: $(TARGET)

$(OBJDIR)/%.o: $(SRCDIR)/%.c 
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

$(TARGET): $(OBJECTS)
	@mkdir -p $(LIBDIR)
	$(CC) -shared -o $@ $^

.PHONY: clean
clean:
	rm -rf $(OBJDIR) $(TARGET)

