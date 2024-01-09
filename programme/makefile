SRCDIR=src
TESTDIR=$(SRCDIR)/tests
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
LIBSRCS = $(wildcard $(SRCDIR)/lib/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c, $(SRCDIR)/%.o, $(SRCS))
LIBOBJS = $(patsubst $(SRCDIR)/lib/%.c, $(SRCDIR)/lib/%.o, $(LIBSRCS))

EXEC=huffman
TESTEXEC=testHuffman

all: lib tests program doc pdf

create_directories:
	mkdir -p $(BINDIR) $(LIBDIR) $(TESTBINDIR) $(DOCDIR)

lib: create_directories $(LIBDIR)/$(LIB_NAME)

$(LIBDIR)/$(LIB_NAME): $(LIBOBJS)
	$(AR) rcs $@ $^

$(SRCDIR)/lib/%.o: $(SRCDIR)/lib/%.c
	$(CC) -c $(CFLAGS) $< -o $@

tests: create_directories lib $(TESTBINDIR)/$(TESTEXEC)

$(TESTDIR)/%.o: $(TESTDIR)/%.c
	$(CC) -c $(CFLAGS) $< -o $@

runner.o: $(TESTDIR)/runner.c
	$(CC) -c $(TESTDIR)/runner.c $(CFLAGS)

$(TESTBINDIR)/$(TESTEXEC): runner.o
	$(CC) -o $@ $^ $(LDFLAGS)

program: create_directories lib $(BINDIR)/$(EXEC)

$(BINDIR)/$(EXEC): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

pdf: ../$(LATEXDIR)/rapport.tex
	cd ../$(LATEXDIR) && pdflatex rapport.tex && pdflatex rapport.tex
	rm -f ../$(LATEXDIR)/*.fls ../$(LATEXDIR)/*.fdb_latexmk ../$(LATEXDIR)/*.aux ../$(LATEXDIR)/*.log ../$(LATEXDIR)/*.lof ../$(LATEXDIR)/*.out ../$(LATEXDIR)/*.synctex.gz ../$(LATEXDIR)/*.toc 
	rm -rf ../$(LATEXDIR)/_minted-rapport

#generates the documentation if something in the include folder changes
doc: create_directories $(SRCDIR)/*.c $(SRCDIR)/lib/*.c $(INCLUDEDIR)/*.h
	doxygen Doxyfile
	cd $(DOCDIR)/latex && make

clean:
	rm -rf ./$(BINDIR)/*
	rm -rf ./$(LIBDIR)/*
	rm -rf ./$(SRCDIR)/*.o
	rm -rf ./$(SRCDIR)/lib/*.o
	rm -rf ./*.o
	rm -rf doc/html doc/latex

# gcc -o tests/testStatistics src/tests/testStatistics.c -Iinclude -lcunit -Wall -pedantic


# Print variables for debugging
print-%:
	@echo $* = $($*)
