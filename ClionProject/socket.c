#include "socket.h"

#define ERROR 1

struct socket {
    int aceptador;
};

socket_t *socket_inicializar() {
    socket_t *socket_server = calloc(1, sizeof(socket_server));

    socket_server->aceptador = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_server->aceptador == -1) {
        printf("socket creation failed...\n");
        socket_destruir(socket_server);
        return NULL;

    } else {
        printf("Socket successfully created..\n");
    }

    return socket_server;
}

int socket_bind_and_listen(socket_t *self, unsigned short service, unsigned short cantidad_clientes) {
    struct sockaddr_in direccion;

    direccion.sin_family = AF_INET;
    direccion.sin_addr.s_addr = htonl(INADDR_ANY);
    direccion.sin_port = htons(service);

    if ((bind(self->aceptador, (const struct sockaddr *) &direccion, sizeof(direccion))) != 0) {
        printf("socket bind failed...\n");
        return ERROR;
    } else {
        printf("Socket successfully binded..\n");
    }

    if ((listen(self->aceptador, cantidad_clientes)) != 0) {
        printf("Listen failed...\n");
        return ERROR;
    } else {
        printf("Server listening..\n");
    }

    return 0;
}

socket_t *socket_aceptar(socket_t *self) {
    int socket_activo = accept(self->aceptador, NULL, NULL);

    if (socket_activo < 0) {
        printf("server acccept failed...\n");
        return NULL;
    }

    printf("server acccept the client...\n");
    return self;
}

void socket_shutdown(socket_t *self) {
    shutdown(self->aceptador, SHUT_RDWR);
    close(self->aceptador);
}

void socket_destruir(socket_t *self) {
    free(self);
}
