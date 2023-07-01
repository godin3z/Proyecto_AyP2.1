CC = gcc
CFLAGS = -Wall -Wextra

all: diccionario

diccionario: main.o trie.o
	$(CC) $(CFLAGS) -o diccionario main.o trie.o

main.o: main.c trie.h
	$(CC) $(CFLAGS) -c main.c

trie.o: trie.c trie.h
	$(CC) $(CFLAGS) -c trie.c

clean:
	rm -f diccionario *.o
