#ifndef TRIE_H
#define TRIE_H

#include <stdbool.h>

struct TrieNodo {
    struct TrieNodo* hijos[26];
    bool finalPalabra;
    char significado[1000];
};

struct Trie {
    struct TrieNodo* raiz;
};

struct TrieNodo* crearNodo();
void insertPalabra(struct Trie* trie, const char* palabra, const char* significado);
bool buscarPalabra(struct Trie* trie, const char* palabra);
void printPalabra(struct TrieNodo* nodo, char* prefijo);
void buscarPrefijo(struct Trie* trie, const char* prefijo);
const char* getSignificado(struct Trie* trie, const char* palabra);

#endif
