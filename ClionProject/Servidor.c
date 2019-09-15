#include "tablero.h"

#include "Servidor.h"

struct servidor {
    tablero_t *tablero;
};

servidor_t *servidor_inicializar() {
    servidor_t *servidor = calloc(1, sizeof(servidor_t));

    servidor->tablero = tablero_inicializar("board.txt");

    return servidor;
}

void servidor_destruir(servidor_t *self) {
    tablero_destruir(self->tablero);

    free(self);
}

//    tablero_t *tablero = tablero_inicializar("board.txt");
//    tablero_get(tablero);
//    tablero_put(tablero, 7, 5, 8);
//    tablero_verify(tablero);
//    tablero_resetear(tablero);