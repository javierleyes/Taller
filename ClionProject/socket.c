#include "socket.h"

//hacer socket server y client
//struct socket_server {
//    int aceptador;
//    int activo
//};

#define ERROR 1

struct socket {
    int socket;
};

socket_t *socket_inicializar() {
    socket_t *socketP = calloc(1, sizeof(socket_t));

    if (!socketP) {
        return NULL;
    }

    socketP->socket = socket(AF_INET, SOCK_STREAM, 0);

    if (socketP->socket == -1) {
        printf("socket creation failed...\n");

        socket_destruir(socketP);

        return NULL;
    } else
        printf("Socket successfully created..\n");

    return socketP;
}

void socket_destruir(socket_t *self) {
    close(self->socket);
    free(self);
}

// ************************************************** server **************************************************

int socket_bind_and_listen(socket_t *self, unsigned short service, unsigned short cantidad_clientes) {
    struct sockaddr_in direccion;

    direccion.sin_family = AF_INET;
    direccion.sin_addr.s_addr = htonl(INADDR_ANY);
    direccion.sin_port = htons(service);

    if ((bind(self->socket, (const struct sockaddr *) &direccion, sizeof(direccion))) != 0) {
        printf("socket bind failed...\n");
        return ERROR;
    } else {
        printf("Socket successfully binded..\n");
    }

    if ((listen(self->socket, cantidad_clientes)) != 0) {
        printf("Listen failed...\n");
        return ERROR;
    } else {
        printf("Server listening..\n");
    }

    return 0;
}

socket_t *socket_aceptar(socket_t *self) {
    self->socket = accept(self->socket, NULL, NULL);

    if (self->socket < 0) {
        printf("server acccept failed...\n");
        return NULL;
    }

    printf("server acccept the client...\n");
    return self;
}

