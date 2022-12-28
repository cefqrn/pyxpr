SHELL = /bin/sh
.SUFFIXES: .o .c
.PHONY: clean run rerun

CC=gcc
CFLAGS=-g -Wall -O3
LDFLAGS=

bindir=bin
libdir=obj
srcdir=src

exe=$(bindir)/pyxpr

objects=$(libdir)/operator.o $(libdir)/expression.o $(libdir)/list.o $(libdir)/parameters.o $(libdir)/main.o
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

run: $(exe)
	$(exe)

rerun:
	make clean
	make run