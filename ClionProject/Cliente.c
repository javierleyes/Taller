#include "Cliente.h"
#include "socket.h"

#define TAMANIO_TABLERO 722
#define LONGITUD_MENSAJE 8
#define BASE_HEXADECIMAL 16

#define INPUT_EXIT "exit\n"
#define INPUT_VERIFY "verify\n"
#define INPUT_GET "get\n"
#define INPUT_RESET "reset\n"
#define INPUT_PUT "put"

#define COMANDO_GET_SERVIDOR "G"
#define COMANDO_VERIFY_SERVIDOR "V"
#define COMANDO_RESET_SERVIDOR "R"

#define VALOR_FUERA_DE_RANGO "Error en el valor ingresado. Rango soportado: [1,9]\n"
#define INDICES_FUERA_DE_RANGO "Error en los indices. Rango soportado: [1,9]\n"
#define MODO_NO_SOPORTADO "Modo no soportado \n"

struct cliente {
    socket_t *socket;
};

//*************************************** FUNCIONES PRIVADAS ***************************************

static void comando_get(cliente_t *self) {
    socket_enviar(self->socket, (char *) COMANDO_GET_SERVIDOR, sizeof(char));

    char *longitud = calloc(LONGITUD_MENSAJE, sizeof(char));

    socket_recibir(self->socket, longitud, LONGITUD_MENSAJE);

    uint32_t longitud_mensaje = strtol(longitud, NULL, BASE_HEXADECIMAL);

    uint32_t longitud_buffer = ntohl(longitud_mensaje);

    char *buffer = calloc(longitud_buffer, sizeof(char));

    socket_recibir(self->socket, buffer, longitud_buffer * sizeof(char));

    printf("%s", buffer);

    free(longitud);
    free(buffer);
}

static void comando_verify(cliente_t *self) {
    socket_enviar(self->socket, (char *) COMANDO_VERIFY_SERVIDOR, sizeof(char));

    char *buffer = calloc(6, sizeof(char));

    socket_recibir(self->socket, buffer, 6 * sizeof(char));

    printf("%s", buffer);

    free(buffer);
}

static void comando_reset(cliente_t *self) {
    socket_enviar(self->socket, (char *) COMANDO_RESET_SERVIDOR, sizeof(char));

    char *buffer = calloc(TAMANIO_TABLERO, sizeof(char));

    socket_recibir(self->socket, buffer, TAMANIO_TABLERO * sizeof(char));

    printf("%s", buffer);

    free(buffer);
}

//*************************************** FUNCIONES ************************************************

cliente_t *cliente_inicializar(char *host, char *service) {
    bool esta_conectado = false;

    cliente_t *cliente = calloc(1, sizeof(cliente_t));

    if (cliente == NULL) {
        return NULL;
    }

    cliente->socket = socket_inicializar();

    if (cliente->socket == NULL) {
        return NULL;
    }

    esta_conectado = socket_conectar(cliente->socket, host, service);

    if (!esta_conectado) {
        cliente_destruir(cliente);
        return NULL;
    }

    return cliente;
}

void cliente_destruir(cliente_t *self) {
    socket_shutdown(self->socket);
    socket_destruir(self->socket);
    free(self);
}

void cliente_recibir_comandos(cliente_t *self) {

    char *input = calloc(13, sizeof(char));
    char *comando = calloc(8, sizeof(char));
    char *comando_compuesto = calloc(4, sizeof(char));

    fgets(input, 13, stdin);

    while (strcmp(input, INPUT_EXIT) != 0) {

        strncpy(comando, input, (7 * sizeof(char)));

        if (strcmp(comando, INPUT_VERIFY) == 0) {

            comando_verify(self);

        } else if (strcmp(comando, INPUT_GET) == 0) {

            comando_get(self);

        } else if (strcmp(comando, INPUT_RESET) == 0) {

            comando_reset(self);

        } else {
            strncpy(comando_compuesto, input, 3);

            if (strcmp(comando_compuesto, INPUT_PUT) == 0) {

                if ((((input[9] - '0') > 0) && ((input[9] - '0') < 10)) &&
                    (((input[11] - '0') > 0) && ((input[11] - '0') < 10))) {

                    if (((input[4] - '0') > 0) && ((input[4] - '0') < 10)) {

                        uint8_t valor = input[4];
                        uint8_t fila = input[9];
                        uint8_t columna = input[11];

                        char *buffer = calloc(4, sizeof(char));
                        strncpy(buffer, "P", sizeof(char));
                        memset(buffer + 1, valor, sizeof(uint8_t));
                        memset(buffer + 2, fila, sizeof(uint8_t));
                        memset(buffer + 3, columna, sizeof(uint8_t));

                        socket_enviar(self->socket, buffer, 4 * sizeof(char));

                        char *respuesta = calloc(TAMANIO_TABLERO, sizeof(char));

                        socket_recibir(self->socket, respuesta, TAMANIO_TABLERO * sizeof(char));

                        printf("%s", respuesta);

                        free(buffer);
                        free(respuesta);

                    } else {
                        printf(VALOR_FUERA_DE_RANGO);
                    }

                } else {
                    printf(INDICES_FUERA_DE_RANGO);
                }
            } else {
                printf(MODO_NO_SOPORTADO);
            }
        }

        fgets(input, 13, stdin);
    }

    socket_shutdown(self->socket);

    free(input);
    free(comando);
    free(comando_compuesto);
}
