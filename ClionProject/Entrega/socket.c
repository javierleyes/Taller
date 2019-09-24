#define _POSIX_C_SOURCE 200112L

#include "socket.h"

struct socket_tcp {
    int socket;
};

socket_tcp_t *socket_inicializar() {
    socket_tcp_t *socket_server = calloc(1, sizeof(socket_server));

    socket_server->socket = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_server->socket == -1) {
        socket_destruir(socket_server);
        return NULL;
    }

    return socket_server;
}

int socket_enviar(socket_tcp_t *self, char *buffer, size_t total) {
    int sent = 0;
    int b = 0;
    bool socket_valido = true;

    while (sent < total && socket_valido) {
        b = send(self->socket, &buffer[sent], total - sent, MSG_NOSIGNAL);

        if (b <= 0) {
            socket_valido = false;
        } else {
            sent += b;
        }
    }

    if (socket_valido) {
        return sent;
    }

    return -1;
}

bool socket_recibir(socket_tcp_t *self, char *buffer, size_t total) {
    int recibido = 0;
    int b = 0;
    bool socket_valido = true;

    while (recibido < total && socket_valido) {
        b = recv(self->socket,&buffer[recibido],total-recibido,MSG_NOSIGNAL);

        if (b <= 0) {
            return false;
        } else {
            recibido += b;
        }
    }

    return true;
}

void socket_shutdown(socket_tcp_t *self) {
    shutdown(self->socket, SHUT_RDWR);
    close(self->socket);
}

void socket_destruir(socket_tcp_t *self) {
    free(self);
}

// ******************************** server ********************************

bool socket_bind_listen(socket_tcp_t *self, char *port) {
    int s = 0;
    struct addrinfo hints;
    struct addrinfo *result;
    struct addrinfo *ptr;
    int v;
    bool escuchado = false;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    s = getaddrinfo(NULL, (const char *) port, &hints, &result);

    if (s != 0) {
        return false;
    }

    if (self->socket == -1) {
        freeaddrinfo(result);
        return false;
    }

    // TIME_WAIT
    v = 1;
    s = setsockopt(self->socket, SOL_SOCKET, SO_REUSEADDR, &v, sizeof(v));
    if (s == -1) {
        close(self->socket);
        freeaddrinfo(result);
        return false;
    }

    // BIND
    for (ptr = result; ptr != NULL && escuchado == false; ptr = ptr->ai_next) {
        s = bind(self->socket, ptr->ai_addr, ptr->ai_addrlen);

        if (s != -1) {
            escuchado = true;
        }
    }

    freeaddrinfo(ptr);

    // LISTEN
    s = listen(self->socket, 1);
    if (s == -1) {
        return false;
    }

    return true;
}

socket_tcp_t *socket_aceptar(socket_tcp_t *self) {
    socket_tcp_t *socket = calloc(1, sizeof(socket_tcp_t));

    socket->socket = accept(self->socket, NULL, NULL);

    if (socket->socket < 0) {
        free(socket);
        return NULL;
    }

    return socket;
}

// ******************************** client ********************************

bool socket_conectar(socket_tcp_t *self, const char *host, const char *port) {
    bool conectado = false;
    int status = 0;

    struct addrinfo hints;
    struct addrinfo *result;
    struct addrinfo *ptr;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = 0;

    status = getaddrinfo(host, port, &hints, &result);

    if (status != 0) {
        return 1;
    }

    for (ptr = result; ptr != NULL && conectado == false; ptr = ptr->ai_next) {
        status = connect(self->socket, ptr->ai_addr, ptr->ai_addrlen);

        if (status != -1) {
            conectado = true;
        }
    }

    freeaddrinfo(result);

    return conectado;
}
