# Makefile
TAR = test
CC = gcc -O6 -Wall
L = -lm
OBJS = main.o isort.o
SHAD = -fPIC -shared
LIB = libisort.so

all : $(TAR) lib
$(TAR): $(OBJS)
	  $(CC) -o $@ $(OBJS) $(L)
clean:
	  rm -f $(OBJS) $(LIB) $(TAR) *~ *.bak

.c.o:	  $(CC) -c $<om

lib:
	$(CC) $(SHAD) -o $(LIB) isort.c $(L)

main.o: main.h isort.o
isort.o: isort.h
