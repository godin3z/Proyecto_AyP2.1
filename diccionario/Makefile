CC = gcc
CFLAGS = -Wall -Wextra

all: arbol

arbol: arbol.o
	$(CC) $(CFLAGS) -o arbol arbol.o

arbol.o: arbol.c
	$(CC) $(CFLAGS) -c arbol.c

clean:
	rm -f arbol.o arbol
