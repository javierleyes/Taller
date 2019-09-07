
#include "tablero.h"

struct tablero {
    char *tablero_inicial;
    char *tabler_juego;
};

tablero_t *tablero_inicializar(const char *nombre_archivo) {
    tablero_t *tablero = calloc(1, sizeof(tablero_t));

    if (!tablero) {
       return NULL;
    }

    return tablero;
}

//void tablero_resetear(tablero_t *self);
//
//void tablero_mostrar(tablero_t *self);

void tablero_destruir(tablero_t *tablero) {
    if (tablero) {
        free(tablero);
    }
}