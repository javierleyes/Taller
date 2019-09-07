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

            printf("%d",tablero->valores_iniciales[posicion_tablero].modificable);

            posicion_tablero++;
        }
    }

    fclose(handler_tablero_inicial);

    return tablero;
}

void tablero_destruir(tablero_t *self) {
    free(self->valores_iniciales);
    free(self->valores_juego);
    free(self);
}