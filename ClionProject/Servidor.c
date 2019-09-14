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