#ifndef CLIENTE_H
#define CLIENTE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct cliente cliente_t;

cliente_t * cliente_inicializar(char *host, char *service);

void cliente_recibir_comandos(cliente_t *self);

void cliente_destruir(cliente_t *self);

#endif //CLIENTE_H
