#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "tablero.h"

int main (int argc, char *argv[])
{
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

    printf("Sudoku \n");

    tablero_t *tablero = tablero_inicializar("board.txt");

    tablero_get(tablero);

    tablero_verify(tablero);

    tablero_put(tablero, 7, 5, 8);

    tablero_verify(tablero);

    tablero_resetear(tablero);

    tablero_get(tablero);

    tablero_exit(tablero);

    return 0;
}