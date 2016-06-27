BINDIR=bin
INCDIR=include
SRCDIR=src
TESTDIR=test

CC=gcc
CFLAGS=-I$(INCDIR)

HEADERS=$(wildcard $(INCDIR)/*.h)
SOURCES=$(wildcard $(SRCDIR)/*.c)

TESTEX=

all: core

$(BINDIR):
	mkdir $(BINDIR)

core: $(HEADERS) $(SOURCES)

test:


clean:
	rm -f $(BINDIR)/*.hzx $(SRCDIR)/*~ $(INCDIR)/*~ $(TESTDIR)/*~

.PHONY: all clean core test
