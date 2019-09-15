#include "socket.h"

#define CANTIDAD_CLIENTES 1
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
    }
    else
        printf("Socket successfully created..\n");

    return socketP;
}

void socket_destruir(socket_t *self) {
    free(self);
}

// ************************************************** server **************************************************

int socket_bind_and_listen(socket_t *self, unsigned short service) {
    struct sockaddr_in direccion;

    direccion.sin_family = AF_INET;
    direccion.sin_addr.s_addr = htonl(INADDR_ANY);
    direccion.sin_port = htons(service);

    if ((bind(self->socket, (struct sockaddr_in*) &direccion, sizeof(direccion))) != 0) {
        printf("socket bind failed...\n");
        return ERROR;
    }
    else
    {
        printf("Socket successfully binded..\n");
    }

    if ((listen(self->socket, CANTIDAD_CLIENTES)) != 0) {
        printf("Listen failed...\n");
        exit(0);
    }
    else {
        printf("Server listening..\n");
    }

    return 0;
}

