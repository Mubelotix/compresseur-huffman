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
# Ajoutez les fichiers pétés dans la liste pour qu'ils soient ignorés
# C'est temporaire!
#EXCLUDE_SRCS = compress.c main.c # Temporary
#SRCS = $(filter-out $(addprefix $(SRCDIR)/, $(EXCLUDE_SRCS)), $(wildcard $(SRCDIR)/*.c)) # Temporary
OBJS = $(patsubst $(SRCDIR)/%.c, $(BINDIR)/%.o, $(SRCS))


EXEC=huffman
TESTEXEC=testHuffman

all: program tests doc

create_directories:
	mkdir -p $(BINDIR) $(LIBDIR) $(TESTBINDIR) $(DOCDIR)

tests: create_directories $(TESTBINDIR)/$(TESTEXEC)
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

program: create_directories $(BINDIR)/$(EXEC)

$(BINDIR)/$(EXEC): $(OBJS)
	$(CC) -o $@ $^

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
	rm -rf doc/html doc/latex

# gcc -o tests/testStatistics src/tests/testStatistics.c -Iinclude -lcunit -Wall -pedantic


# Print variables for debugging
print-%:
	@echo $* = $($*)
