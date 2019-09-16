#include "tablero.h"

#include "Servidor.h"
#include "socket.h"

#define CANTIDAD_CLIENTES 1
#define NOMBRE_ARCHIVO "board.txt"

struct servidor {
    tablero_t *tablero;
    socket_t *socket;
};

servidor_t *servidor_inicializar(unsigned short service) {
    servidor_t *servidor = calloc(1, sizeof(servidor_t));

    servidor->tablero = tablero_inicializar(NOMBRE_ARCHIVO);

    if (servidor->tablero == NULL) {
        return NULL;
    }

    servidor->socket = socket_inicializar();

    if (servidor->socket == NULL) {
        return NULL;
    }

    socket_bind_and_listen(servidor->socket, service, CANTIDAD_CLIENTES);

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