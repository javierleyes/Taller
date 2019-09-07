#include "tablero.h"

#include <stdlib.h>
#include <stdio.h>


int main (int argc, char *argv[])
{
    printf("\nPRUEBAS BASICAS\n");

    tablero_t *tablero = tablero_inicializar("board.txt");

    tablero_destruir(tablero);

    return 0;
}


//gcc -Wall -Werror -std=c99 -pedantic -o tp main.c