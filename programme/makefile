SRCDIR=src
LIBDIR=lib
BINDIR=bin
TESTDIR=$(SRCDIR)/tests
TESTBINDIR=tests
INCLUDEDIR=include
CC=gcc
AR=ar
CFLAGS=-Wall -pedantic -g -std=gnu99
LDFLAGS=

EXEC=huffman
TESTEXEC=testHuffman

all: $(BINDIR)/$(EXEC)

tests: $(TESTBINDIR)/$(TESTEXEC)

$(BINDIR)/$(EXEC): $(SRCDIR)/main.o $(LIBDIR)/libhuffman.a
	$(CC) $(LDFLAGS) -o $@ $< -lhuffman -Llib

SRC_FILES := $(wildcard $(SRCDIR)/*.c)
OBJ_FILES := $(patsubst $(SRCDIR)/%.c, $(SRCDIR)/%.o, $(SRC_FILES))
$(LIBDIR)/libhuffman.a: $(OBJ_FILES)
	$(AR) -r $@ $^

$(SRCDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -o $@ -c $< $(CFLAGS) -I$(INCLUDEDIR)

TEST_SRC_FILES := $(wildcard $(TESTDIR)/*.c)
TEST_OBJ_FILES := $(patsubst $(TESTDIR)/%.c, $(TESTBINDIR)/%.o, $(TEST_SRC_FILES))
$(TESTBINDIR)/%.o: $(TESTDIR)/%.c
	$(CC) -o $@ -c $< $(CFLAGS) -I$(INCLUDEDIR)

$(TESTBINDIR)/$(TESTEXEC): $(TEST_OBJ_FILES) $(LIBDIR)/libhuffman.a
	$(CC) $(LDFLAGS) -o $@ $^ -lhuffman -Llib -lcunit

clean :
	rm -rf ./$(BINDIR)/*
	rm -rf ./$(TESTBINDIR)/*
	rm -rf ./$(LIBDIR)/*
	rm -rf ./$(SRCDIR)/*.o

# gcc -o tests/testStatistics src/tests/testStatistics.c -Iinclude -lcunit -Wall -pedantic