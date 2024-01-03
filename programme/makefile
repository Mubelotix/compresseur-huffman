SRCDIR=src
LIBDIR=lib
BINDIR=bin
TESTDIR=$(SRCDIR)/tests
TESTBINDIR=tests
INCLUDEDIR=include
CC = gcc
AR = ar
CFLAGS=-Wall -pedantic -g -std=gnu99
LDFLAGS=

EXEC=huffman

all : $(BINDIR)/$(EXEC)

tests: $(TEST_EXECUTABLES)

$(BINDIR)/$(EXEC) : $(SRCDIR)/main.o $(LIBDIR)/libhuffman.a
	$(CC) $(LDFLAGS) -o $@ $< -lhuffman -Llib

SRC_FILES := $(wildcard $(SRCDIR)/*.c)
OBJ_FILES := $(patsubst $(SRCDIR)/%.c, $(SRCDIR)/%.o, $(SRC_FILES))
$(LIBDIR)/libhuffman.a : $(OBJ_FILES)
	$(AR) -r $@ $^

$(SRCDIR)/%.o : $(SRCDIR)/%.c
	$(CC) -o $@ -c $< $(CFLAGS) -I$(INCLUDEDIR)

TEST_SRC_FILES := $(wildcard $(TESTDIR)/*.c)
TEST_EXECUTABLES := $(patsubst $(TESTDIR)/%.c, $(TESTDIR)/%.o, $(TEST_SRC_FILES))
$(TESTDIR)/%.o : $(TESTDIR)/%.c
	$(CC) -o $@ -c $< $(CFLAGS) -I$(INCLUDEDIR)

$(TESTBINDIR)/$(TESTEXEC) : $(TEST_EXECUTABLES) $(LIBDIR)/libhuffman.a
	$(CC) $(LDFLAGS) -o $@ $^ -lhuffman -Llib -lcunit

clean :
	rm -rf ./$(BINDIR)/*
	rm -rf ./$(TESTBINDIR)/*
	rm -rf ./$(LIBDIR)/*
	rm -rf ./$(SRCDIR)/*.o

# gcc -o tests/testStatistics src/tests/testStatistics.c -Iinclude -lcunit -Wall -pedantic