#include "tablero.h"

#include "Servidor.h"
#include "socket.h"

#define CANTIDAD_CLIENTES 1
#define NOMBRE_ARCHIVO_SUDOKU "board.txt"
#define TAMANIO_TABLERO 722

struct servidor {
    tablero_t *tablero;
    socket_t *socket;
};

//*************************************** FUNCIONES PRIVADAS ***************************************

static void comando_get(servidor_t *self, socket_t *socket_activo) {
    char *response;

    response = calloc(TAMANIO_TABLERO, sizeof(char));

    tablero_get(self->tablero, response);

    socket_enviar(socket_activo, response, TAMANIO_TABLERO * sizeof(char));

    free(response);
}

static void comando_verify(servidor_t *self, socket_t *socket_activo) {
    char *response;
    bool tablero_valido;

    tablero_valido = tablero_verify(self->tablero);

    if (tablero_valido) {
        response = calloc(6, sizeof(char));
        strncpy(response, "OK\n", 6 * sizeof(char));

        socket_enviar(socket_activo, response, 6 * sizeof(char));

    } else {
        response = calloc(6, sizeof(char));
        strncpy(response, "ERROR\n", 6 * sizeof(char));

        socket_enviar(socket_activo, response, 6 * sizeof(char));
    }

    free(response);
}

static void comando_reset(servidor_t *self) {
    tablero_resetear(self->tablero);
}

//*************************************** FUNCIONES ************************************************

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

    char *comando = calloc(1, sizeof(char));

    while (continuar_escuchando) {

        if (socket_activo == NULL) {
            printf("Error: %s\n", strerror(errno));
            continuar_escuchando = false;
        } else {

            socket_esta_activo = socket_recibir(socket_activo, comando, sizeof(char));

            switch(*comando) {
                case 'G':
                    comando_get(self, socket_activo);
                    break;

                case 'V':
                    comando_verify(self, socket_activo);
                    break;

                case 'R':
                    comando_reset(self);
                    comando_get(self, socket_activo);
                    break;

                    //case 'P':
//                    break;
            }

            if (!socket_esta_activo) {
                continuar_escuchando = false;
            }
        }
    }

    free(comando);

    socket_shutdown(socket_activo);
    socket_shutdown(self->socket);
}

void servidor_destruir(servidor_t *self) {
    socket_destruir(self->socket);
    tablero_destruir(self->tablero);
    free(self);
}

