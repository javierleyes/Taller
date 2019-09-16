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

typedef struct socket socket_t;

socket_t *socket_inicializar();

//int socket_enviar(socket_t *self, const void *buffer, size_t longitud);

//int socket_recibir(socket_t *self, const void *buffer, size_t longitud);

void socket_shutdown(socket_t *self);

void socket_destruir(socket_t *self);

// ************************************************** server **************************************************

int socket_bind_and_listen(socket_t *self, char *service, unsigned short cantidad_clientes);

socket_t *socket_aceptar(socket_t * self);

#endif //SOCKET_SERVER_H

// ************************************************** client **************************************************

//int socket_conectar(socket_t *self, const char *host, const char *service);