#include "tablero.h"

#include "Servidor.h"
#include "socket.h"

#define CANTIDAD_CLIENTES 1
#define TAMANIO_TABLERO 722
#define LONGITUD_MENSAJE 8
#define LONGITUD_MENSAJE_OK 3

#define NOMBRE_ARCHIVO_SUDOKU "board.txt"
#define OK "OK\n"
#define ERROR "ERROR\n"
#define CELDA_NO_MODIFICABLE "La celda indicada no es modificable\n"

struct servidor {
    tablero_t *tablero;
    socket_t *socket;
};

// ********************************************* FUNCIONES PRIVADAS *********************************************

static void comando_get(servidor_t *self, socket_t *socket_activo) {

    char *respuesta = calloc (TAMANIO_TABLERO + LONGITUD_MENSAJE, sizeof(char));

    snprintf(respuesta, 4 * sizeof(uint32_t),"%x", htonl(TAMANIO_TABLERO));

    char *tablero = calloc(TAMANIO_TABLERO, sizeof(char));

    tablero_get(self->tablero, tablero);

    strncat(respuesta, tablero, TAMANIO_TABLERO);

    socket_enviar(socket_activo, respuesta, TAMANIO_TABLERO + LONGITUD_MENSAJE);

    free(tablero);
    free(respuesta);
}

static void comando_verify(servidor_t *self, socket_t *socket_activo) {
    char *respuesta;

    if (tablero_verify(self->tablero)) {
        respuesta = calloc (LONGITUD_MENSAJE_OK + LONGITUD_MENSAJE, sizeof(char));

        strncat(respuesta, "0", 1);
        snprintf(respuesta + 1, 4 * sizeof(uint32_t),"%x", htonl(LONGITUD_MENSAJE_OK));

        strncat(respuesta, OK, LONGITUD_MENSAJE_OK);

        socket_enviar(socket_activo, respuesta, LONGITUD_MENSAJE_OK + LONGITUD_MENSAJE);
    } else {
        respuesta = calloc (6 + LONGITUD_MENSAJE, sizeof(char));

        strncat(respuesta, "0", 1);
        snprintf(respuesta + 1, 4 * sizeof(uint32_t),"%x", htonl(6));

        strncat(respuesta, ERROR, 6);

        socket_enviar(socket_activo, respuesta, 6 + LONGITUD_MENSAJE);
    }

    free(respuesta);
}

static void comando_reset(servidor_t *self, socket_t *socket_activo) {
    tablero_resetear(self->tablero);
    comando_get(self, socket_activo);
}

static void comando_put(servidor_t *self, socket_t *socket_activo) {
    char *valor = calloc(1, sizeof(char));
    char *fila = calloc(1, sizeof(char));
    char *columna = calloc(1, sizeof(char));

    socket_recibir(socket_activo, valor, sizeof(char));
    socket_recibir(socket_activo, fila, sizeof(char));
    socket_recibir(socket_activo, columna, sizeof(char));

    if (tablero_put(self->tablero, atoi(valor), atoi(fila), atoi(columna))) {
        comando_get(self, socket_activo);
    } else {
        socket_enviar(socket_activo, CELDA_NO_MODIFICABLE, strlen(CELDA_NO_MODIFICABLE) + 1);
    }
}

// ************************************************** FUNCIONES **************************************************

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

            switch (*comando) {
                case 'G':
                    comando_get(self, socket_activo);
                    break;

                case 'V':
                    comando_verify(self, socket_activo);
                    break;

                case 'R':
                    comando_reset(self, socket_activo);
                    break;

                case 'P':
                    comando_put(self, socket_activo);
                    break;
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

