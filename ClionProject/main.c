#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "tablero.h"

int main (int argc, char *argv[])
{
    printf("Sudoku \n");

    tablero_t *tablero = tablero_inicializar("board.txt");

    tablero_get(tablero);

    tablero_put(tablero, 4, 5, 5);

    tablero_resetear(tablero);

    tablero_get(tablero);

    tablero_exit(tablero);

    return 0;
}