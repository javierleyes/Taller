#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "tablero.h"

int main (int argc, char *argv[])
{
    printf("\nPRUEBAS BASICAS\n");

    tablero_t *tablero = tablero_inicializar("board.txt");

    tablero_destruir(tablero);

    return 0;
}
