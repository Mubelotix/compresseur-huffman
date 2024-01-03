SRCDIR=src
LIBDIR=lib
LIB_NAME = libhuffman.a
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
	./$(TESTBINDIR)/$(TESTEXEC)

byte.o statistics.o runner.o: src/byte.c src/statistics.c src/tests/runner.c
	gcc -c src/byte.c src/statistics.c src/tests/runner.c -I include

libhuffman.a: byte.o statistics.o
	ar rcs libhuffman.a byte.o statistics.o

$(TESTBINDIR)/$(TESTEXEC): runner.o libhuffman.a
	gcc -o $@ byte.o statistics.o runner.o -L. -lhuffman -lcunit

clean :
	rm -rf ./$(BINDIR)/*
	rm -rf ./$(TESTBINDIR)/*
	rm -rf ./$(LIBDIR)/*
	rm -rf ./$(SRCDIR)/*.o

# gcc -o tests/testStatistics src/tests/testStatistics.c -Iinclude -lcunit -Wall -pedantic