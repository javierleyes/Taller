#include "tablero.h"

struct celda {
    bool modificable;
    char valor;
};

struct tablero {
    celda_t *valores_iniciales;
    celda_t *valores_juego;
};

tablero_t *tablero_inicializar(const char *nombre_archivo) {

    tablero_t *tablero = calloc(1, sizeof(tablero_t));
    tablero->valores_iniciales = calloc(81, sizeof(celda_t));
    tablero->valores_juego = calloc(81, sizeof(celda_t));

    FILE *handler_tablero_inicial = fopen(nombre_archivo, "r");

    if (!handler_tablero_inicial) {
        return NULL;
    }

    char valor_inicial;
    int posicion_tablero = 0;

    while ((valor_inicial = fgetc(handler_tablero_inicial)) != EOF) {
        if ( (valor_inicial != ' ') && (valor_inicial != '\n') ) {
//            putchar(valor_inicial);

            if (valor_inicial == '0') {
                tablero->valores_iniciales[posicion_tablero].modificable = true;
            } else {
                tablero->valores_iniciales[posicion_tablero].modificable = false;
            }

//            printf("%d",tablero->valores_iniciales[posicion_tablero].modificable);

            posicion_tablero++;
        }
    }

    fclose(handler_tablero_inicial);

    return tablero;
}

void tablero_get(tablero_t *self) {

    printf("U===========U===========U===========U\n");

    for(int j = 0; j < 81; j = j + 9) {
        for (int i = j; i < (j + 9); i = i + 3) {
            printf("U");
            printf("%1s%1d%1s", " ", self->valores_juego[i].valor, " ");
            printf("|");
            printf("%1s%1d%1s", " ", self->valores_juego[i + 1].valor, " ");
            printf("|");
            printf("%1s%1d%1s", " ", self->valores_juego[i + 2].valor, " ");
        }

        printf("U\n");

        if ((((j + 1) % 19) == 0) || (((j + 1) % 46) == 0) || (((j + 1) % 73) == 0)) {
            printf("U===========U===========U===========U\n");
        } else {
            printf("U---+---+---U---+---+---U---+---+---U\n");
        }
    }
}

void tablero_destruir(tablero_t *self) {
    free(self->valores_iniciales);
    free(self->valores_juego);
    free(self);
}