#include "tablero.h"

#include "Servidor.h"
#include "socket.h"

#define CANTIDAD_CLIENTES 1
#define NOMBRE_ARCHIVO_SUDOKU "board.txt"

struct servidor {
    tablero_t *tablero;
    socket_t *socket;
};

servidor_t *servidor_inicializar(char *service) {
    servidor_t *servidor = calloc(1, sizeof(servidor_t));

    if (servidor == NULL) {
        return NULL;
    }

    servidor->tablero = tablero_inicializar(NOMBRE_ARCHIVO_SUDOKU);

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

void servidor_escuchar(servidor_t *self) {
    socket_t *socket_activo;
    bool continuar_escuchando = true;
    bool socket_esta_activo = true;

    socket_activo = socket_aceptar(self->socket);

//    unsigned int longitud = 0;

    char *comando_recibido = calloc(1, sizeof(char));

    while (continuar_escuchando) {

        if (socket_activo == NULL) {
            printf("Error: %s\n", strerror(errno));
            continuar_escuchando = false;
        } else {

            // recibo el comando
            socket_esta_activo = socket_recibir(socket_activo, comando_recibido, sizeof(char));
            printf("%s%s", "comando recibido: ", comando_recibido);

            char *response = calloc(722, sizeof(char));
            tablero_get(self->tablero, response);

            socket_enviar(socket_activo, response, 722 * sizeof(char));

            free(response);


            if (!socket_esta_activo) {
                continuar_escuchando = false;
            }
        }
    }

    free(comando_recibido);

    socket_shutdown(socket_activo);
    socket_shutdown(self->socket);
}

void servidor_destruir(servidor_t *self) {
    socket_destruir(self->socket);
    tablero_destruir(self->tablero);
    free(self);
}

