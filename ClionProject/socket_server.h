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

typedef struct socket_server socket_server_t;

socket_server_t *socket_server_inicializar();

//int socket_enviar(socket_t *self, const void *buffer, size_t longitud);

//int socket_recibir(socket_t *self, const void *buffer, size_t longitud);

//void socket_shutdown(socket_t *self);

void socket_server_destruir(socket_server_t *self);

// ************************************************** server **************************************************

int socket_bind_and_listen(socket_server_t *self, unsigned short service, unsigned short cantidad_clientes);

socket_server_t *socket_aceptar(socket_server_t * self);

#endif //SOCKET_SERVER_H

// sacar para hacer el socket client
// ************************************************** client **************************************************

//int socket_conectar(socket_t *self, const char *host, const char *service);