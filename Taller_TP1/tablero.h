#ifndef TABLERO_H
#define TABLERO_H

#include <stdlib.h>
#include <stdio.h>

typedef struct tablero tablero_t;

tablero_t *tablero_inicializar(const char *nombre_archivo);

//void tablero_resetear(tablero_t *self);

//void tablero_mostrar(tablero_t *self);

void tablero_destruir(tablero_t *self);

#endif //TABLERO_H
