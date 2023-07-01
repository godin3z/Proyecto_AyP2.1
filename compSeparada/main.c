#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trie.h"

void cargarDiccionario(struct Trie* diccionario, const char* nombreArchivo) {
    FILE* file = fopen(nombreArchivo, "r");
    if (file == NULL) {
        printf("No se pudo abrir el archivo %s\n", nombreArchivo);
        return;
    }

    char linea[1100];
    while (fgets(linea, sizeof(linea), file)) {
        char palabra[100];
        char significado[1000];
        sscanf(linea, "%s %[^\n]", palabra, significado);

        if (palabra[0] == '+') {
            insertPalabra(diccionario, palabra + 1, significado);
        } else {
            insertPalabra(diccionario, palabra, significado);
        }
    }

    fclose(file);
    printf("Diccionario cargado exitosamente desde el archivo %s\n", nombreArchivo);
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
            cargarDiccionario(diccionario, arg);
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
