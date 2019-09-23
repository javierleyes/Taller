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

#define COMANDO_GET "G"
#define COMANDO_VERIFY "V"
#define COMANDO_RESET "R"
#define COMANDO_PUT "P"

#define FUERA_DE_RANGO "Error en el valor ingresado. Rango soportado: [1,9]\n"
#define INDICES_ERROR_RANGO "Error en los indices. Rango soportado: [1,9]\n"
#define MODO_NO_SOPORTADO "Modo no soportado \n"

struct cliente {
    socket_t *socket;
};


// *************************** FUNCIONES PRIVADAS ***************************

static uint32_t _calcular_longitud_mensaje(cliente_t *self) {
    char longitud[LONGITUD_MENSAJE];

    socket_recibir(self->socket, longitud, LONGITUD_MENSAJE);

    uint32_t longitud_mensaje = strtol(longitud, NULL, BASE_HEXADECIMAL);

    uint32_t longitud_buffer = ntohl(longitud_mensaje);

    return longitud_buffer;
}

static void _mostrar_respuesta(cliente_t *self) {
    uint32_t longitud_buffer = _calcular_longitud_mensaje(self);

    char *buffer = calloc(longitud_buffer, sizeof(char));

    socket_recibir(self->socket, buffer, longitud_buffer);

    printf("%s", buffer);

    free(buffer);
}

static void _comando_get(cliente_t *self) {
    socket_enviar(self->socket, (char *) COMANDO_GET, sizeof(char));
    _mostrar_respuesta(self);
}

static void _comando_verify(cliente_t *self) {
    socket_enviar(self->socket, (char *) COMANDO_VERIFY, sizeof(char));
    _mostrar_respuesta(self);
}

static void _comando_reset(cliente_t *self) {
    socket_enviar(self->socket, (char *) COMANDO_RESET, sizeof(char));
    _mostrar_respuesta(self);
}

static void _comando_put(cliente_t *self, char *input) {
    uint8_t valor = input[4];
    uint8_t fila = input[9];
    uint8_t columna = input[11];

    char *buffer = calloc(4, sizeof(char));
    strncpy(buffer, COMANDO_PUT, sizeof(char));

    memset(buffer + 1, valor, sizeof(uint8_t));
    memset(buffer + 2, fila, sizeof(uint8_t));
    memset(buffer + 3, columna, sizeof(uint8_t));

    socket_enviar(self->socket, buffer, 4 * sizeof(char));

    _mostrar_respuesta(self);
}

// ******************************** FUNCIONES ********************************

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
    char *input = calloc(14, sizeof(char));
    char *comando = calloc(8, sizeof(char));
    char *comando_compuesto = calloc(4, sizeof(char));

    fgets(input, 14, stdin);

    while (strcmp(input, INPUT_EXIT) != 0) {
        strncpy(comando, input, 7);

        if (strcmp(comando, INPUT_VERIFY) == 0) {
            _comando_verify(self);
        } else if (strcmp(comando, INPUT_GET) == 0) {
            _comando_get(self);

        } else if (strcmp(comando, INPUT_RESET) == 0) {
            _comando_reset(self);
        } else {
            strncpy(comando_compuesto, input, 3);
            if (strcmp(comando_compuesto, INPUT_PUT) == 0) {
                if ((((input[9] - '0') > 0) && ((input[9] - '0') < 10)) &&
                    (((input[11] - '0') > 0) && ((input[11] - '0') < 10))) {
                    if (((input[4] - '0') > 0) && ((input[4] - '0') < 10)) {
                        _comando_put(self, input);
                    } else {
                        printf("%s", FUERA_DE_RANGO);
                    }
                } else {
                    printf("%s", INDICES_ERROR_RANGO);
                }
            } else {
                printf("%s", MODO_NO_SOPORTADO);
            }
        }

        fgets(input, 14, stdin);
    }

    socket_shutdown(self->socket);

    free(input);
    free(comando);
    free(comando_compuesto);
}
