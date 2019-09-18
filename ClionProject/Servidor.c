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

    while (continuar_escuchando) {

        if (socket_activo == NULL) {
            printf("Error: %s\n", strerror(errno));
            continuar_escuchando = false;
        } else {
            printf("New client\n");

            char *buffer = calloc(1, sizeof(char));

            socket_esta_activo = socket_recibir(socket_activo, buffer, sizeof(char));

            printf("%s%s","valor recibido: ", buffer);

            if (!socket_esta_activo) {
                continuar_escuchando = false;
            }

//            memset(small_buf, 0, MAX_SMALL_BUF_LEN);
//            conexion_valida = socket_recibir(socket_activo, small_buf, MAX_SMALL_BUF_LEN - 1);

//            len = atoi(small_buf);
//            printf("Echo %i bytes\n", len);

//            if (len == 0) {
//                printf("Zero bytes. Bye!\n");
//                continuar_escuchando = false;
//            } else {
//                printf("Received %i/%i bytes\n", socket_recibir(socket_activo, tmp, len), len);
//                printf("Sent %i/%i bytes\n\n", socket_enviar(socket_activo, tmp, len), len);
//            }
        }
    }

    socket_shutdown(socket_activo);
    socket_shutdown(self->socket);
}

void servidor_destruir(servidor_t *self) {
    socket_destruir(self->socket);
    tablero_destruir(self->tablero);
    free(self);
}

