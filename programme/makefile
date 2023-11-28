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

all :  $(BINDIR)/$(EXEC)

tests:  $(TESTDIR)/testHuffman.o $(LIBDIR)/libhuffman.a
	$(CC) $(LDFLAGS) -o $(TESTBINDIR)/testHuffman $(TESTDIR)/testHuffman.o -lhuffman -Llib -lcunit

$(BINDIR)/$(EXEC) : $(SRCDIR)/main.o $(LIBDIR)/libhuffman.a
	$(CC) $(LDFLAGS) -o $@ $< -lhuffman -Llib

SRC_FILES := $(wildcard $(SRCDIR)/*.c)
OBJ_FILES := $(patsubst $(SRCDIR)/%.c, $(SRCDIR)/%.o, $(SRC_FILES))
$(LIBDIR)/libhuffman.a : $(OBJ_FILES)
	$(AR) -r $@ $^

$(LIBDIR)/lib%.a : $(SRCDIR)/%.o
	$(AR)  -r $@  $^

$(SRCDIR)/%.o : $(SRCDIR)/%.c
	$(CC) -o $@ -c $< $(CFLAGS) -I$(INCLUDEDIR)  

$(TESTDIR)/%.o : $(TESTDIR)/%.c
	$(CC) -o $@ -c $< $(CFLAGS) -I$(INCLUDEDIR)

clean :
	rm -rf $(BINDIR)/*
	rm -rf $(TESTBINDIR)/*
	rm -rf $(LIBDIR)/*
	rm -rf $(SRCDIR)/*.o
