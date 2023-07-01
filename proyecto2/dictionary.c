#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct TrieNodo {
    struct TrieNodo* hijos[26];
    bool finalPalabra;
    char significado[1000];
};

struct Trie {
    struct TrieNodo* raiz;
};

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

int main() {
    struct Trie* diccionario = (struct Trie*)malloc(sizeof(struct Trie));
    diccionario->raiz = crearNodo();
    char command[10];
    char arg[100];

    printf("Comandos disponibles:\n");
    printf("l nombre - carga el diccionario desde el archivo <nombre>.dic\n");
    printf("s palabra - busca el significado de la palabra <palabra>\n");
    printf("p prefijo - muestra los significados de todas las palabras que comienzan con el prefijo <prefijo>\n");
    printf("h - muestra una breve ayuda\n");
    printf("q - sale de la aplicación\n");

    while (1) {
        printf("Ingrese un comando: ");
        scanf("%s", command);

        if (strcmp(command, "l") == 0) {
            scanf("%s", arg);
            FILE* file = fopen(arg, "r");
            if (file == NULL) {
                printf("No se pudo abrir el archivo %s\n", arg);
            } else {
                char palabra[100];
                char significado[1000];
                while (fscanf(file, "%s %[^\n]s", palabra, significado) != EOF) {
                    insertPalabra(diccionario, palabra, significado);
                    char c;
                    do {
                        c = fgetc(file);
                    } while (c != EOF && c != '\n');
                }
                fclose(file);
                printf("Diccionario cargado exitosamente desde el archivo %s\n", arg);
            }
        } else if (strcmp(command, "s") == 0) {
            scanf("%s", arg);
            const char* significado = getSignificado(diccionario, arg);
            if (strcmp(significado, "") != 0) {
                printf("Significados de la palabra '%s':\n%s\n", arg, significado);
            } else {
                printf("No se encontró el significado de la palabra '%s'\n", arg);
            }
        } else if (strcmp(command, "p") == 0) {
            scanf("%s", arg);
            printf("Palabras que comienzan con el prefijo '%s':\n", arg);
            buscarPrefijo(diccionario, arg);
        } else if (strcmp(command, "h") == 0) {
            printf("Comandos disponibles:\n");
            printf("l nombre - carga el diccionario desde el archivo <nombre>.dic\n");
            printf("s palabra - busca el significado de la palabra <palabra>\n");
            printf("p prefijo - muestra los significados de todas las palabras que comienzan con el prefijo <prefijo>\n");
            printf("h - muestra una breve ayuda\n");
            printf("q - sale de la aplicación\n");
        } else if (strcmp(command, "q") == 0) {
            break;
        } else {
            printf("Comando inválido. Ingrese 'h' para obtener ayuda.\n");
        }
    }

    return 0;
}
