#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "tablero.h"

int main (int argc, char *argv[])
{
    printf("Sudoku \n");

    tablero_t *tablero = tablero_inicializar("board.txt");

    tablero_get(tablero);

    tablero_put(tablero, 4, 1, 2);

    tablero_destruir(tablero);

    return 0;
}