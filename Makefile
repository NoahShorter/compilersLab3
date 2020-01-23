#################################
# Makefile for Compilers lab03
#
# Author: Noah Shorter
# noah.shorter@oit.edu
#

COPTS=-Wall -g -c -O0 -std=c++11
OBJS=main.o \
     calclex.o \
     parse.o \
     utils.o

all: calc

clean:
	rm -f $(OBJS)
	rm -f calclex.c
	rm -f calc
	rm -f out

.c.o:
	g++ $(COPTS) $? -o $@

.cpp.o:
	g++ $(COPTS) $? -o $@

main.o: main.cpp calclex.c
	g++ $(COPTS) main.cpp -o main.o

parse.o: parse.cpp
	g++ $(COPTS) parse.cpp -o parse.o

utils.o: utils.cpp
	g++ $(COPTS) utils.cpp -o utils.o

calclex.c: calc.l
	flex -o calclex.c calc.l

calclex.o: calclex.c
	g++ $(COPTS) -Wno-sign-compare $? -o $@

calc: $(OBJS)
	g++ $(OBJS) -o calc
