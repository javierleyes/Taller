#define _POSIX_C_SOURCE 200112L

#include "socket.h"

struct socket {
    int socket_tcp;
};

socket_t *socket_inicializar() {
    socket_t *socket_server = calloc(1, sizeof(socket_server));

    socket_server->socket_tcp = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_server->socket_tcp == -1) {
        socket_destruir(socket_server);
        return NULL;
    }

    return socket_server;
}

int socket_enviar(socket_t *self, char *buffer, size_t total) {
    int enviados = 0;
    int bytes = 0;
    bool socket_valido = true;

    while (enviados < total && socket_valido) {
        bytes = send(self->socket_tcp,&buffer[enviados],total-enviados,MSG_NOSIGNAL);

        if (bytes <= 0) {
            socket_valido = false;
        } else {
            enviados += bytes;
        }
    }

    if (socket_valido) {
        return enviados;
    }

    return -1;
}

bool socket_recibir(socket_t *self, char *buffer, size_t total) {
    int recibidos = 0;
    int bytes = 0;
    bool socket_valido = true;

    while (recibidos < total && socket_valido) {
        bytes = recv(self->socket_tcp,&buffer[recibidos],total-recibidos,MSG_NOSIGNAL);

        if (bytes <= 0) {
            return false;
        } else {
            recibidos += bytes;
        }
    }

    return true;
}

void socket_shutdown(socket_t *self) {
    shutdown(self->socket_tcp, SHUT_RDWR);
    close(self->socket_tcp);
}

void socket_destruir(socket_t *self) {
    free(self);
}

// ******************************** server ********************************

bool socket_bind_listen(socket_t *self, char *port, unsigned short cantidad) {
    int s = 0;
    struct addrinfo hints;
    struct addrinfo *result;
    struct addrinfo *ptr;
    int val;
    bool escuchado = false;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    s = getaddrinfo(NULL, (const char *) port, &hints, &result);

    if (s != 0) {
        return false;
    }

    if (self->socket_tcp == -1) {
        freeaddrinfo(result);
        return false;
    }

    // TIME_WAIT
    val = 1;
    s = setsockopt(self->socket_tcp, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
    if (s == -1) {
        close(self->socket_tcp);
        freeaddrinfo(result);
        return false;
    }

    // BIND
    for (ptr = result; ptr != NULL && escuchado == false; ptr = ptr->ai_next) {
        s = bind(self->socket_tcp, ptr->ai_addr, ptr->ai_addrlen);

        if (s != -1) {
            escuchado = true;
        }
    }

    freeaddrinfo(ptr);

    // LISTEN
    s = listen(self->socket_tcp, cantidad);
    if (s == -1) {
        return false;
    }

    return true;
}

socket_t *socket_aceptar(socket_t *self) {
    socket_t *socket = calloc(1, sizeof(socket_t));

    socket->socket_tcp = accept(self->socket_tcp, NULL, NULL);

    if (socket->socket_tcp < 0) {
        free(socket);
        return NULL;
    }

    return socket;
}

// ******************************** client ********************************

bool socket_conectar(socket_t *self, const char *host, const char *service) {
    bool conectado = false;
    int status = 0;

    struct addrinfo hints;
    struct addrinfo *resultado;
    struct addrinfo *ptr;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = 0;

    status = getaddrinfo(host, service, &hints, &resultado);

    if (status != 0) {
        return 1;
    }

    for (ptr = resultado; ptr != NULL && conectado == false; ptr = ptr->ai_next) {
        status = connect(self->socket_tcp, ptr->ai_addr, ptr->ai_addrlen);

        if (status != -1) {
            conectado = true;
        }
    }

    freeaddrinfo(resultado);

    return conectado;
}

