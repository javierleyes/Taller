#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "tablero.h"

//**************************************************************************************************
//*************************************** FUNCIONES PRIVADAS ***************************************
//**************************************************************************************************

bool validar_modo_operacion(int argc, char *argv[]) {
    if (argc == 1) {
        printf("Modo no soportado, el primer parametro debe ser server o client\n");
        return 1;
    }

    if (argc == 2) {

        if (strcmp(argv[1],"server") == 0) {
            printf("Uso: ./tp server <puerto>\n");
            return 1;
        }

        if (strcmp(argv[1],"client") == 0) {
            printf("Uso: ./tp client <host> <puerto>\n");
            return 1;
        }

        printf("Modo no soportado, el primer parametro debe ser server o client\n");
        return 1;
    }

    if ((argc == 3) && (strcmp(argv[1],"server") == 0)) {
        printf("Modo server \n");
        return 0;
    }

    if ((argc == 4) && (strcmp(argv[1],"client") == 0)) {
        printf("Modo client \n");
        return 0;
    }

    printf("Modo no soportado, el primer parametro debe ser server o client\n");
    return 1;
}

//**************************************************************************************************

int main (int argc, char *argv[])
{
//    return validar_modo_operacion(argc, argv);

//  comando client

    char *input = calloc(13, sizeof(char));
    char *comando = calloc(7, sizeof(char));
    char *comando_compuesto = calloc(3, sizeof(char));
    char *fila = calloc(1, sizeof(char));
    char *columna = calloc(1, sizeof(char));

    fgets(input, 13, stdin);
    strncpy(comando, input, sizeof(comando));

    if (strcmp(comando, "verify\n") == 0) {
        printf("V");
    }

    if (strcmp(comando, "get\n") == 0) {
        printf("G");
    }

    if (strcmp(comando, "reset\n") == 0) {
        printf("R");
    }

    if (strcmp(comando, "exit\n") == 0) {
        printf("E");
    }

    strncpy(comando_compuesto, input, 3);

    if (strcmp(comando_compuesto, "put") == 0) {

        if ((((input[9]-'0') > 0) && ((input[9]-'0') < 10) ) && (((input[11]-'0') > 0) && ((input[11]-'0') < 10))) {
            printf("Indices validos");
        } else {
            printf("Error en los indices. Rango soportado: [1,9]\n");
        }

        if ( ((input[4] - '0') > 0) && ((input[4] - '0') < 10) ) {
            printf("valor valido");
        } else {
            printf("Error en el valor ingresado. Rango soportado: [1,9]\n");
        }
    }

    free(input);
    free(comando);
    free(comando_compuesto);
    free(fila);
    free(columna);

    printf("Modo no soportado, el primer parametro debe ser server o client\n");






//    printf("Sudoku \n");
//
//    tablero_t *tablero = tablero_inicializar("board.txt");
//
//    tablero_get(tablero);
//
//    tablero_verify(tablero);
//
//    tablero_put(tablero, 7, 5, 8);
//
//    tablero_verify(tablero);
//
//    tablero_resetear(tablero);
//
//    tablero_get(tablero);
//
//    tablero_exit(tablero);

    return 0;
}