#include "Cliente.h"
#include "socket.h"

struct cliente {
    socket_t *socket;
};

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

    printf("Modo client \n");

    char *input = calloc(13, sizeof(char));
    char *comando = calloc(8, sizeof(char));
    char *comando_compuesto = calloc(4, sizeof(char));

    fgets(input, 13, stdin);

    while(strcmp(input, "exit\n") != 0) {

        strncpy(comando, input, (7 * sizeof(char)));

        if (strcmp(comando, "verify\n") == 0) {
            printf("V\n");
        } else if (strcmp(comando, "get\n") == 0) {
            printf("G\n");

            int test = socket_enviar(self->socket, (char *)"G", sizeof(char));
            printf("%s%d","resultado", test);

        } else if (strcmp(comando, "reset\n") == 0) {
            printf("R\n");
        } else {
            strncpy(comando_compuesto, input, 3);

            if (strcmp(comando_compuesto, "put") == 0) {

                if ((((input[9] - '0') > 0) && ((input[9] - '0') < 10)) &&
                    (((input[11] - '0') > 0) && ((input[11] - '0') < 10))) {
//            printf("Indices validos");

                    if (((input[4] - '0') > 0) && ((input[4] - '0') < 10)) {
                        printf("P\n");
//                printf("valor valido");
                    } else {
                        printf("Error en el valor ingresado. Rango soportado: [1,9]\n");
                    }

                } else {
                    printf("Error en los indices. Rango soportado: [1,9]\n");
                }
            } else {
                printf("Modo no soportado \n");
            }
        }

        fgets(input, 13, stdin);
    }

    free(input);
    free(comando);
    free(comando_compuesto);
}
