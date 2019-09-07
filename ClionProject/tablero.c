
#include "tablero.h"

struct tablero {
    char *tablero_inicial;
    char *tabler_juego;
};

tablero_t *tablero_inicializar(const char *nombre_archivo) {

    // poner esto en una funcion
    tablero_t *tablero = calloc(1, sizeof(tablero_t));
    tablero->tablero_inicial = calloc(741, sizeof(char));
    tablero->tabler_juego = calloc(741, sizeof(char));

    char *valores = calloc(700, sizeof(char));

    if (!tablero) {
        return NULL;
    }

    FILE *tablero_txt;

    char caracter;

    tablero_txt = fopen(nombre_archivo, "r");

    if ( tablero_txt == NULL )
    {
        printf("ERROR \n");
        return 1;
    }




    putchar(valores[0]);

    while ((caracter = fgetc(tablero_txt)) != EOF) {

        //int j = 0;

        if ( (caracter != ' ') && (caracter != '\n') ){

            putchar(caracter);


            //  j++;
        }

    }


    int posicion_actual = 0;

    // Principal

    tablero->tablero_inicial[posicion_actual] = 'U';
    posicion_actual = posicion_actual + 1;

    int i = posicion_actual;
    for (i; i < (posicion_actual + 11); i++)
    {
        tablero->tablero_inicial[i] = '=';
    }
    posicion_actual = posicion_actual + 11;

    tablero->tablero_inicial[posicion_actual] = 'U';
    posicion_actual = posicion_actual + 1;

    i = posicion_actual;
    for (i; i < (posicion_actual + 11); i++)
    {
        tablero->tablero_inicial[i] = '=';
    }
    posicion_actual = posicion_actual + 11;

    tablero->tablero_inicial[posicion_actual] = 'U';
    posicion_actual = posicion_actual + 1;

    i = posicion_actual;
    for (i; i < (posicion_actual + 11); i++)
    {
        tablero->tablero_inicial[i] = '=';
    }
    posicion_actual = posicion_actual + 11;

    tablero->tablero_inicial[posicion_actual] = 'U';
    posicion_actual = posicion_actual + 1;

    tablero->tablero_inicial[posicion_actual] = '\n';
    posicion_actual = posicion_actual + 1;


    for(int k = 0; k < 3; k++) {

        // Valores

        tablero->tablero_inicial[posicion_actual] = 'U';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = ' ';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = 'X';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = ' ';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = '|';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = ' ';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = 'X';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = ' ';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = '|';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = ' ';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = 'X';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = ' ';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = 'U';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = ' ';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = 'X';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = ' ';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = '|';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = ' ';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = 'X';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = ' ';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = '|';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = ' ';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = 'X';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = ' ';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = 'U';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = ' ';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = 'X';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = ' ';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = '|';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = ' ';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = 'X';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = ' ';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = '|';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = ' ';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = 'X';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = ' ';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = 'U';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = '\n';
        posicion_actual = posicion_actual + 1;

        // Separador

        tablero->tablero_inicial[posicion_actual] = 'U';
        posicion_actual = posicion_actual + 1;

        i = posicion_actual;
        for (i; i < (posicion_actual + 3); i++)
        {
            tablero->tablero_inicial[i] = '-';
        }
        posicion_actual = posicion_actual + 3;

        tablero->tablero_inicial[posicion_actual] = '+';
        posicion_actual = posicion_actual + 1;

        i = posicion_actual;
        for (i; i < (posicion_actual + 3); i++)
        {
            tablero->tablero_inicial[i] = '-';
        }
        posicion_actual = posicion_actual + 3;

        tablero->tablero_inicial[posicion_actual] = '+';
        posicion_actual = posicion_actual + 1;

        i = posicion_actual;
        for (i; i < (posicion_actual + 3); i++)
        {
            tablero->tablero_inicial[i] = '-';
        }
        posicion_actual = posicion_actual + 3;

        tablero->tablero_inicial[posicion_actual] = 'U';
        posicion_actual = posicion_actual + 1;

        i = posicion_actual;
        for (i; i < (posicion_actual + 3); i++)
        {
            tablero->tablero_inicial[i] = '-';
        }
        posicion_actual = posicion_actual + 3;

        tablero->tablero_inicial[posicion_actual] = '+';
        posicion_actual = posicion_actual + 1;

        i = posicion_actual;
        for (i; i < (posicion_actual + 3); i++)
        {
            tablero->tablero_inicial[i] = '-';
        }
        posicion_actual = posicion_actual + 3;

        tablero->tablero_inicial[posicion_actual] = '+';
        posicion_actual = posicion_actual + 1;

        i = posicion_actual;
        for (i; i < (posicion_actual + 3); i++)
        {
            tablero->tablero_inicial[i] = '-';
        }
        posicion_actual = posicion_actual + 3;

        tablero->tablero_inicial[posicion_actual] = 'U';
        posicion_actual = posicion_actual + 1;

        i = posicion_actual;
        for (i; i < (posicion_actual + 3); i++)
        {
            tablero->tablero_inicial[i] = '-';
        }
        posicion_actual = posicion_actual + 3;

        tablero->tablero_inicial[posicion_actual] = '+';
        posicion_actual = posicion_actual + 1;

        i = posicion_actual;
        for (i; i < (posicion_actual + 3); i++)
        {
            tablero->tablero_inicial[i] = '-';
        }
        posicion_actual = posicion_actual + 3;

        tablero->tablero_inicial[posicion_actual] = '+';
        posicion_actual = posicion_actual + 1;

        i = posicion_actual;
        for (i; i < (posicion_actual + 3); i++)
        {
            tablero->tablero_inicial[i] = '-';
        }
        posicion_actual = posicion_actual + 3;

        tablero->tablero_inicial[posicion_actual] = 'U';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = '\n';
        posicion_actual = posicion_actual + 1;

        // Valores

        tablero->tablero_inicial[posicion_actual] = 'U';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = ' ';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = 'X';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = ' ';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = '|';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = ' ';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = 'X';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = ' ';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = '|';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = ' ';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = 'X';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = ' ';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = 'U';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = ' ';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = 'X';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = ' ';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = '|';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = ' ';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = 'X';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = ' ';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = '|';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = ' ';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = 'X';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = ' ';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = 'U';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = ' ';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = 'X';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = ' ';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = '|';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = ' ';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = 'X';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = ' ';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = '|';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = ' ';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = 'X';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = ' ';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = 'U';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = '\n';
        posicion_actual = posicion_actual + 1;

        // Separador

        tablero->tablero_inicial[posicion_actual] = 'U';
        posicion_actual = posicion_actual + 1;

        i = posicion_actual;
        for (i; i < (posicion_actual + 3); i++)
        {
            tablero->tablero_inicial[i] = '-';
        }
        posicion_actual = posicion_actual + 3;

        tablero->tablero_inicial[posicion_actual] = '+';
        posicion_actual = posicion_actual + 1;

        i = posicion_actual;
        for (i; i < (posicion_actual + 3); i++)
        {
            tablero->tablero_inicial[i] = '-';
        }
        posicion_actual = posicion_actual + 3;

        tablero->tablero_inicial[posicion_actual] = '+';
        posicion_actual = posicion_actual + 1;

        i = posicion_actual;
        for (i; i < (posicion_actual + 3); i++)
        {
            tablero->tablero_inicial[i] = '-';
        }
        posicion_actual = posicion_actual + 3;

        tablero->tablero_inicial[posicion_actual] = 'U';
        posicion_actual = posicion_actual + 1;

        i = posicion_actual;
        for (i; i < (posicion_actual + 3); i++)
        {
            tablero->tablero_inicial[i] = '-';
        }
        posicion_actual = posicion_actual + 3;

        tablero->tablero_inicial[posicion_actual] = '+';
        posicion_actual = posicion_actual + 1;

        i = posicion_actual;
        for (i; i < (posicion_actual + 3); i++)
        {
            tablero->tablero_inicial[i] = '-';
        }
        posicion_actual = posicion_actual + 3;

        tablero->tablero_inicial[posicion_actual] = '+';
        posicion_actual = posicion_actual + 1;

        i = posicion_actual;
        for (i; i < (posicion_actual + 3); i++)
        {
            tablero->tablero_inicial[i] = '-';
        }
        posicion_actual = posicion_actual + 3;

        tablero->tablero_inicial[posicion_actual] = 'U';
        posicion_actual = posicion_actual + 1;

        i = posicion_actual;
        for (i; i < (posicion_actual + 3); i++)
        {
            tablero->tablero_inicial[i] = '-';
        }
        posicion_actual = posicion_actual + 3;

        tablero->tablero_inicial[posicion_actual] = '+';
        posicion_actual = posicion_actual + 1;

        i = posicion_actual;
        for (i; i < (posicion_actual + 3); i++)
        {
            tablero->tablero_inicial[i] = '-';
        }
        posicion_actual = posicion_actual + 3;

        tablero->tablero_inicial[posicion_actual] = '+';
        posicion_actual = posicion_actual + 1;

        i = posicion_actual;
        for (i; i < (posicion_actual + 3); i++)
        {
            tablero->tablero_inicial[i] = '-';
        }
        posicion_actual = posicion_actual + 3;

        tablero->tablero_inicial[posicion_actual] = 'U';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = '\n';
        posicion_actual = posicion_actual + 1;

        // Valores

        tablero->tablero_inicial[posicion_actual] = 'U';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = ' ';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = 'X';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = ' ';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = '|';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = ' ';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = 'X';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = ' ';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = '|';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = ' ';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = 'X';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = ' ';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = 'U';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = ' ';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = 'X';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = ' ';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = '|';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = ' ';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = 'X';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = ' ';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = '|';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = ' ';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = 'X';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = ' ';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = 'U';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = ' ';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = 'X';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = ' ';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = '|';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = ' ';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = 'X';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = ' ';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = '|';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = ' ';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = 'X';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = ' ';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = 'U';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = '\n';
        posicion_actual = posicion_actual + 1;

        // Principal

        tablero->tablero_inicial[posicion_actual] = 'U';
        posicion_actual = posicion_actual + 1;

        int i = posicion_actual;
        for (i; i < (posicion_actual + 11); i++)
        {
            tablero->tablero_inicial[i] = '=';
        }
        posicion_actual = posicion_actual + 11;

        tablero->tablero_inicial[posicion_actual] = 'U';
        posicion_actual = posicion_actual + 1;

        i = posicion_actual;
        for (i; i < (posicion_actual + 11); i++)
        {
            tablero->tablero_inicial[i] = '=';
        }
        posicion_actual = posicion_actual + 11;

        tablero->tablero_inicial[posicion_actual] = 'U';
        posicion_actual = posicion_actual + 1;

        i = posicion_actual;
        for (i; i < (posicion_actual + 11); i++)
        {
            tablero->tablero_inicial[i] = '=';
        }
        posicion_actual = posicion_actual + 11;

        tablero->tablero_inicial[posicion_actual] = 'U';
        posicion_actual = posicion_actual + 1;

        tablero->tablero_inicial[posicion_actual] = '\n';
        posicion_actual = posicion_actual + 1;

    }


    for (int i = 0; i < 722; i++)
    {
        putchar(tablero->tablero_inicial[i]);
    }


    fclose(tablero_txt);

    printf("Termino correctamente la lectura del archivo! \n");

    return tablero;
}

//void tablero_resetear(tablero_t *self);
//
//void tablero_mostrar(tablero_t *self);

//void tablero_destruir(tablero_t *tablero) {
//    if (tablero) {
//        free(tablero);
//    }
//}
