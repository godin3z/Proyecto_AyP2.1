#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define CHAR_INT(caracter) ((char)caracter - (int)'a')  
#define LONGITUD_ALFABETO (26)

struct nodo_trie {
    struct nodo_trie* hijo[LONGITUD_ALFABETO];
    char* definicion;
    bool fin_palabra;
};

struct nodo_trie* crear_nodo()
{
    struct nodo_trie* puntero_nodo = NULL;
    if((puntero_nodo = (struct nodo_trie*)malloc(sizeof(struct nodo_trie))) == NULL) {
        fprintf(stderr, "nodo_trie: error en malloc\n");
        exit(1);
    }  
    puntero_nodo->fin_palabra = false;
    for(int i = 0; i < LONGITUD_ALFABETO; i++)
        puntero_nodo->hijo[i] = NULL;
    return puntero_nodo;
}

void insertar(struct nodo_trie* raiz, char clave_definicion[])
{
    char* resto = clave_definicion;
    char* clave = strtok_r(resto, " ", &resto);
    int posicion_letra, indice, longitud_clave = strlen(clave);
    struct nodo_trie* puntero_buscador = raiz;
    for(posicion_letra = 0; posicion_letra < longitud_clave; posicion_letra++) {
        indice = CHAR_INT(clave[posicion_letra]);
        if(!puntero_buscador->hijo[indice])
            puntero_buscador->hijo[indice] = crear_nodo();
        puntero_buscador = puntero_buscador->hijo[indice];
    }
    int longitud = strlen(resto);
    puntero_buscador->definicion = malloc(longitud + 1);
    strncpy(puntero_buscador->definicion, resto, longitud);
    puntero_buscador->fin_palabra = true;
}

void buscar(struct nodo_trie* raiz, const char clave[])
{
    int posicion_letra, indice, longitud_clave = strlen(clave);
    struct nodo_trie* puntero_buscador = raiz;
    for(posicion_letra = 0; posicion_letra < longitud_clave; posicion_letra++) {
        indice = CHAR_INT(clave[posicion_letra]);
        if(!puntero_buscador->hijo[indice]) {
            puts("Palabra no encontrada");
            return;
        }
        puntero_buscador = puntero_buscador->hijo[indice];
    }
    if(puntero_buscador->fin_palabra == false) {
        puts("Palabra no encontrada");
        return;
    }
    printf("%s\n", puntero_buscador->definicion);
}

void imprimir_palabra(struct nodo_trie* nodo, char* prefijo)
{
    if(nodo->fin_palabra) {
        printf("%s: %s\n", prefijo, nodo->definicion);
    }
    for(int i = 0; i < LONGITUD_ALFABETO; i++) {
        if (nodo->hijo[i] != NULL) {
            prefijo[strlen(prefijo)] = 'a' + i;
            prefijo[strlen(prefijo) + 1] = '\0';
            imprimir_palabra(nodo->hijo[i], prefijo);
            prefijo[strlen(prefijo) - 1] = '\0';
        }
    }
}

void buscar_prefijo(struct nodo_trie* raiz, const char* prefijo) {
    struct nodo_trie* curr = raiz;
    int index;
    for(int i = 0; prefijo[i] != '\0'; i++) {
        index = prefijo[i] - 'a';
        if(curr->hijo[index] == NULL) {
            printf("No se encontraron palabras con el prefijo '%s'\n", prefijo);
            return;
        }
        curr = curr->hijo[index];
    }
    if (curr != NULL) {
        char palabra[100];
        strcpy(palabra, prefijo);
        imprimir_palabra(curr, palabra);
    }
}

char* leer_archivo(char direccion_archivo[])
{
    char* buffer = 0;
    long longitud;
    FILE* archivo;
    if((archivo = fopen(direccion_archivo, "rb")) == NULL) {
        fprintf(stderr, "leer_archivo: error en fopen\n");
        exit(1);
    }
    if(archivo) {
        fseek(archivo, 0, SEEK_END);
        longitud = ftell(archivo);
        fseek(archivo, 0, SEEK_SET);
        buffer = malloc(longitud);
        if(buffer)
            fread(buffer, 1, longitud, archivo);
    }
    for(int i = 0; buffer[i]; i++)
        buffer[i] = tolower(buffer[i]);
    fclose(archivo);
    return buffer;
}

void delimitar(char* diccionario)
{
    for(int i = 0; diccionario[i] != '\0'; i++)
        if(diccionario[i] == '\n' && diccionario[i + 1] != '+')
            diccionario[i] = '@';
}

void enter()
{
    puts("(Presione enter para continuar)");
    while(getchar() != '\n');
        getchar();
}

void main()
{
    int i;    
    char opcion;
    bool bandera = false;
    struct nodo_trie* raiz = crear_nodo();

    while(opcion != 'q' && opcion != 'Q') {

        system("clear");
        puts("[l] Cargar archivo");
        puts("[s] Buscar definicion");
        puts("[p] Buscar por prefijo");
        puts("[h] Ayuda");
        puts("[q] Salir");
        puts("Ingrese una opcion:");
        scanf("%c", &opcion);

        if(opcion == 'l' || opcion == 'L') {
            if(bandera == false) {
                char direccion_archivo[50];
                printf("Ingrese la direccion del archivo: ");
                scanf("%s", direccion_archivo);
                char* diccionario = leer_archivo(direccion_archivo);
                delimitar(diccionario);  
                char* token;
                char* resto = diccionario;    
                while((token = strtok_r(resto, "@", &resto)))
                    insertar(raiz, token);
                bandera = true;
                puts("Archivo cargado exitosamente");
                enter();
            }
            else {
                puts("Debe reiniciar el programa si desea cargar otro archivo");
                enter();
            }
        }

        if(opcion == 's' || opcion == 'S') {
            if(bandera == true) {
                char palabra[30];
                printf("Ingrese la definicion a buscar: ");
                scanf("%s", palabra);
                for(i = 0; palabra[i]; i++)
                    palabra[i] = tolower(palabra[i]);
                buscar(raiz, palabra);
                enter();
            }
            else {
                puts("Debe cargar un archivo primero");
                enter();
            }
        }

        if(opcion == 'p' || opcion == 'P') {
            if(bandera == true) {
                char prefijo[20];
                printf("Ingrese el prefijo a buscar: ");
                scanf("%s", prefijo);
                for(i = 0; prefijo[i]; i++)
                    prefijo[i] = tolower(prefijo[i]);
                buscar_prefijo(raiz, prefijo);
                enter();
            }
            else {
                puts("Debe cargar un archivo primero");
                enter();
            }
        }

        if(opcion == 'h' || opcion == 'H') {
            puts("Escoja [l] para cargar la direccion de su diccionario");
            puts("Escoja [s] para buscar la definicion de una palabra");
            puts("Escoja [p] para buscar todas las palabras con igual prefijo");
            puts("Escoja [q] para salir del programa");
            enter();
        }
    }
}

