#ifndef TABLERO_H
#define TABLERO_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct celda celda_t;

typedef struct tablero tablero_t;

tablero_t *tablero_inicializar(const char *nombre_archivo);

void tablero_get(tablero_t *self, char *resp);

bool tablero_put(tablero_t *self, int valor, int fila, int columna);

void tablero_destruir(tablero_t *self);

void tablero_resetear(tablero_t *self);

bool tablero_verify(tablero_t *self);

#endif //TABLERO_H
