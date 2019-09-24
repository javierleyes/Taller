#ifndef SOCKET_SERVER_H
#define SOCKET_SERVER_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct socket_tcp socket_tcp_t;

socket_tcp_t *socket_inicializar();

int socket_enviar(socket_tcp_t *self, char *buffer, size_t total);

bool socket_recibir(socket_tcp_t *self, char *buffer, size_t total);

void socket_shutdown(socket_tcp_t *self);

void socket_destruir(socket_tcp_t *self);

// ******************************** server ********************************

bool socket_bind_listen(socket_tcp_t *self, char *port);

socket_tcp_t *socket_aceptar(socket_tcp_t * self);

// ******************************** client ********************************

bool socket_conectar(socket_tcp_t *self, const char *host, const char *port);

#endif //SOCKET_SERVER_H
