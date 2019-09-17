#define _POSIX_C_SOURCE 200112L

#include "socket.h"

#define ERROR 1

struct socket {
    int socket_tcp;
};

socket_t *socket_inicializar() {
    socket_t *socket_server = calloc(1, sizeof(socket_server));

    socket_server->socket_tcp = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_server->socket_tcp == -1) {
        printf("socket creation failed...\n");
        socket_destruir(socket_server);
        return NULL;

    } else {
        printf("Socket successfully created..\n");
    }

    return socket_server;
}

int socket_enviar(socket_t *self, char *buffer, size_t longitud) {
    int bytes_enviados = 0;
    int bytes = 0;
    bool socket_valido = true;

    while (bytes_enviados < longitud && socket_valido) {
        bytes = send(self->socket_tcp, &buffer[bytes_enviados], longitud - bytes_enviados, MSG_NOSIGNAL);

        if (bytes <= 0) {
            socket_valido = false;
        } else {
            bytes_enviados += bytes;
        }
    }

    if (socket_valido) {
        return bytes_enviados;
    }

    return -1;
}

int socket_recibir(socket_t *self, char *buffer, size_t longitud) {
    int bytes_recibidos = 0;
    int bytes = 0;
    bool socket_valido = true;

    while (bytes_recibidos < longitud && socket_valido) {
        bytes = recv(self->socket_tcp, &buffer[bytes_recibidos], longitud - bytes_recibidos, MSG_NOSIGNAL);

        if (bytes <= 0) {
            socket_valido = false;
        } else {
            bytes_recibidos += bytes;
        }
    }

    if (socket_valido) {
        return bytes_recibidos;
    }

    return -1;
}

// ************************************************** server **************************************************

int socket_bind_and_listen(socket_t *self, char *service, unsigned short cantidad_clientes) {
    int status = 0;
    struct addrinfo hints;
    struct addrinfo *ptr;
    int val;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    status = getaddrinfo(NULL, (const char *) service, &hints, &ptr);
    if (status != 0) {
        return ERROR;
    }

    if (self->socket_tcp == -1) {
        printf("Error: %s\n", strerror(errno));
        freeaddrinfo(ptr);
        return ERROR;
    }

    // TIME_WAIT
    val = 1;
    status = setsockopt(self->socket_tcp, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
    if (status == -1) {
        printf("Error: %s\n", strerror(errno));
        close(self->socket_tcp);
        freeaddrinfo(ptr);
        return ERROR;
    }

    // BIND
    status = bind(self->socket_tcp, ptr->ai_addr, ptr->ai_addrlen);
    if (status == -1) {
        printf("Error: %s\n", strerror(errno));
        close(self->socket_tcp);
        freeaddrinfo(ptr);
        return ERROR;
    }

    freeaddrinfo(ptr);

    printf("Socket successfully binded..\n");

    // LISTEN
    status = listen(self->socket_tcp, cantidad_clientes);
    if (status == -1) {
        printf("Error: %s\n", strerror(errno));
        close(self->socket_tcp);
        return ERROR;
    }

    printf("Server listening..\n");

    return 0;
}

socket_t *socket_aceptar(socket_t *self) {
    socket_t *socket = calloc(1, sizeof(socket_t));

    socket->socket_tcp = accept(self->socket_tcp, NULL, NULL);

    if (socket->socket_tcp < 0) {
        printf("server acccept failed...\n");
        free(socket);
        return NULL;
    }

    printf("server acccept the client...\n");
    return socket;
}

void socket_shutdown(socket_t *self) {
    shutdown(self->socket_tcp, SHUT_RDWR);
    close(self->socket_tcp);
}

void socket_destruir(socket_t *self) {
    close(self->socket_tcp);
    free(self);
}
