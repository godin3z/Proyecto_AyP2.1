#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "trie.h"

struct TrieNodo* crearNodo() {
    struct TrieNodo* newNodo = (struct TrieNodo*)malloc(sizeof(struct TrieNodo));
    newNodo->finalPalabra = false;
    for (int i = 0; i < 26; i++) {
        newNodo->hijos[i] = NULL;
    }
    return newNodo;
}

void insertPalabra(struct Trie* trie, const char* palabra, const char* significado) {
    struct TrieNodo* curr = trie->raiz;
    int index;
    for (int i = 0; palabra[i] != '\0'; i++) {
        index = palabra[i] - 'a';
        if (curr->hijos[index] == NULL) {
            curr->hijos[index] = crearNodo();
        }
        curr = curr->hijos[index];
    }
    curr->finalPalabra = true;
    strcpy(curr->significado, significado);
}

bool buscarPalabra(struct Trie* trie, const char* palabra) {
    struct TrieNodo* curr = trie->raiz;
    int index;
    for (int i = 0; palabra[i] != '\0'; i++) {
        index = palabra[i] - 'a';
        if (curr->hijos[index] == NULL) {
            return false;
        }
        curr = curr->hijos[index];
    }
    return curr->finalPalabra;
}

void printPalabra(struct TrieNodo* nodo, char* prefijo) {
    if (nodo->finalPalabra) {
        printf("%s: %s\n", prefijo, nodo->significado);
    }
    for (int i = 0; i < 26; i++) {
        if (nodo->hijos[i] != NULL) {
            prefijo[strlen(prefijo)] = 'a' + i;
            prefijo[strlen(prefijo) + 1] = '\0';
            printPalabra(nodo->hijos[i], prefijo);
            prefijo[strlen(prefijo) - 1] = '\0';
        }
    }
}

void buscarPrefijo(struct Trie* trie, const char* prefijo) {
    struct TrieNodo* curr = trie->raiz;
    int index;
    for (int i = 0; prefijo[i] != '\0'; i++) {
        index = prefijo[i] - 'a';
        if (curr->hijos[index] == NULL) {
            printf("No se encontraron palabras con el prefijo '%s'\n", prefijo);
            return;
        }
        curr = curr->hijos[index];
    }
    if (curr != NULL) {
        char palabra[100];
        strcpy(palabra, prefijo);
        printPalabra(curr, palabra);
    }
}

const char* getSignificado(struct Trie* trie, const char* palabra) {
    struct TrieNodo* curr = trie->raiz;
    int index;
    for (int i = 0; palabra[i] != '\0'; i++) {
        index = palabra[i] - 'a';
        if (curr->hijos[index] == NULL) {
            return "";
        }
        curr = curr->hijos[index];
    }
    return curr->significado;
}
