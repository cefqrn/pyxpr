SHELL = /bin/sh
.SUFFIXES: .o .c
.PHONY: clean remake run rerun

CC=gcc
CFLAGS=-g -Wall -Wextra -O3
LDFLAGS=

bindir=bin
libdir=obj
srcdir=src

exe=$(bindir)/pyxpr

objects=$(libdir)/expression.o $(libdir)/operator.o $(libdir)/hashtable.o $(libdir)/main.o
.SECONDARY: $(objects)

all: $(exe)

$(libdir)/%.o: $(srcdir)/%.c | $(libdir)
	$(CC) -c $(CFLAGS) $< -o $@

$(bindir)/%: $(objects) | $(bindir)
	$(CC) $(LDFLAGS) $^ -o $@

$(libdir):
	mkdir $(libdir)

$(bindir):
	mkdir $(bindir)

clean:
	rm -f $(bindir)/* $(libdir)/*

remake:
	make clean
	make

run: $(exe)
	$(exe)

rerun:
	make clean
	make run