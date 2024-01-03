SRCDIR=src
LIBDIR=lib
LIB_NAME = libhuffman.a
BINDIR=bin
TESTDIR=$(SRCDIR)/tests
TESTBINDIR=tests
INCLUDEDIR=include
CC=gcc
AR=ar
CFLAGS=-Wall -pedantic -g -std=gnu99 -I include
LDFLAGS=-L. -L$(LIBDIR) -lhuffman -lcunit

SRCS = $(wildcard $(SRCDIR)/*.c)
# Ajoutez les fichiers pétés dans la liste pour qu'ils soient ignorés
# C'est temporaire!
EXCLUDE_SRCS = binaryCode.c compress.c main.c priorityQueue.c # Temporary
SRCS = $(filter-out $(addprefix $(SRCDIR)/, $(EXCLUDE_SRCS)), $(wildcard $(SRCDIR)/*.c)) # Temporary
OBJS = $(patsubst $(SRCDIR)/%.c, $(BINDIR)/%.o, $(SRCS))


EXEC=huffman
TESTEXEC=testHuffman

all: $(BINDIR)/$(EXEC)

tests: $(TESTBINDIR)/$(TESTEXEC)
	./$(TESTBINDIR)/$(TESTEXEC)

$(BINDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c $(CFLAGS) $< -o $@

$(BINDIR)/%.o: $(TESTDIR)/%.c
	$(CC) -c $(CFLAGS) $< -o $@

runner.o: src/tests/runner.c
	$(CC) -c src/tests/runner.c $(CFLAGS)

$(LIBDIR)/$(LIB_NAME): $(OBJS)
	$(AR) rcs $@ $^

$(TESTBINDIR)/$(TESTEXEC): runner.o $(LIBDIR)/$(LIB_NAME)
	$(CC) -o $@ $^ $(LDFLAGS)

clean :
	rm -rf ./$(BINDIR)/*
	rm -rf ./$(TESTBINDIR)/*
	rm -rf ./$(LIBDIR)/*
	rm -rf ./$(SRCDIR)/*.o

# gcc -o tests/testStatistics src/tests/testStatistics.c -Iinclude -lcunit -Wall -pedantic


# Print variables for debugging
print-%:
	@echo $* = $($*)
