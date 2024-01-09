SRCDIR=src
TESTDIR=tests
INCLUDEDIR=include
LIBDIR=lib
BINDIR=bin
TESTBINDIR=tests
DOCDIR=doc
LATEXDIR=rapport

LIB_NAME = libhuffman.a
CC=gcc
AR=ar
CFLAGS=-Wall -pedantic -g -std=gnu99 -I $(INCLUDEDIR)
LDFLAGS=-L. -L$(LIBDIR) -lhuffman -lcunit

SRCS = $(wildcard $(SRCDIR)/*.c)
LIBSRCS = $(wildcard $(LIBDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c, $(SRCDIR)/%.o, $(SRCS))
LIBOBJS = $(patsubst $(LIBDIR)/%.c, $(LIBDIR)/%.o, $(LIBSRCS))

EXEC=huffman
TESTEXEC=testHuffman

all: program tests doc

create_directories:
	mkdir -p $(BINDIR) $(LIBDIR) $(TESTBINDIR) $(DOCDIR)

lib: create_directories $(LIBDIR)/$(LIB_NAME)

$(LIBDIR)/$(LIB_NAME): $(LIBOBJS)
	$(AR) rcs $@ $^

$(LIBDIR)/%.o: $(LIBDIR)/%.c
	$(CC) -c $(CFLAGS) $< -o $@

tests: create_directories $(TESTBINDIR)/$(TESTEXEC)

$(TESTDIR)/%.o: $(TESTDIR)/%.c
	$(CC) -c $(CFLAGS) $< -o $@

runner.o: $(TESTDIR)/runner.c
	$(CC) -c $(TESTDIR)/runner.c $(CFLAGS)

$(TESTBINDIR)/$(TESTEXEC): runner.o $(LIBDIR)/$(LIB_NAME)
	$(CC) -o $@ $^ $(LDFLAGS)

program: create_directories lib $(BINDIR)/$(EXEC)

$(BINDIR)/$(EXEC): $(patsubst $(SRCDIR)/%.c, $(SRCDIR)/%.o, $(SRCS))
	$(CC) -o $@ $^ $(LDFLAGS)

pdf: ../$(LATEXDIR)/rapport.tex
	cd ../$(LATEXDIR) && pdflatex rapport.tex && pdflatex rapport.tex
	rm -f ../$(LATEXDIR)/*.fls ../$(LATEXDIR)/*.fdb_latexmk ../$(LATEXDIR)/*.aux ../$(LATEXDIR)/*.log ../$(LATEXDIR)/*.lof ../$(LATEXDIR)/*.out ../$(LATEXDIR)/*.synctex.gz ../$(LATEXDIR)/*.toc 
	rm -rf ../$(LATEXDIR)/_minted-rapport

#generates the documentation if something in the include folder changes
doc: create_directories $(SRCDIR)/*.c $(INCLUDEDIR)/*.h
	doxygen Doxyfile
	cd $(DOCDIR)/latex && make

clean :
	rm -rf ./$(BINDIR)/*
	rm -rf ./$(LIBDIR)/*
	rm -rf ./$(SRCDIR)/*.o
	rm -rf ./*.o
	rm -rf doc/html doc/latex

# gcc -o tests/testStatistics src/tests/testStatistics.c -Iinclude -lcunit -Wall -pedantic


# Print variables for debugging
print-%:
	@echo $* = $($*)
