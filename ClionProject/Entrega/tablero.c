#include "tablero.h"

#define LONGITUD_FILA 38
#define TOTAL_CELDAS 81
#define CANTIDAD_CELDAS_FILA 9

#define BORDE_TABLERO "U===========U===========U===========U\n"
#define SEPARADOR_LINEA "U---+---+---U---+---+---U---+---+---U\n"

struct celda {
    bool modificable;
    int valor;
};

struct tablero {
    celda_t *iniciales;
    celda_t *juego;
};

// *************************** FUNCIONES PRIVADAS ***************************

static bool _hay_valores_repetidos(int *valores) {
    for (int i = 0; i < CANTIDAD_CELDAS_FILA; i++) {
        for (int j = i + 1; j < CANTIDAD_CELDAS_FILA; j++) {
            if ( (valores[i] == valores[j]) && (valores[i] != 0) ) {
                return true;
            }
        }
    }

    return false;
}

static bool _validar_filas(tablero_t * self) {
    int valores[CANTIDAD_CELDAS_FILA];

    for (int j = 0; j < TOTAL_CELDAS; j += CANTIDAD_CELDAS_FILA) {
        for (int i = 0; i < CANTIDAD_CELDAS_FILA; i++) {
            valores[i] = self->juego[j + i].valor;
        }

        if (_hay_valores_repetidos(valores)) {
            return false;
        }
    }

    return true;
}

static bool _validar_columnas(tablero_t *self) {
    int valores[CANTIDAD_CELDAS_FILA];

    for (int j = 0; j < CANTIDAD_CELDAS_FILA; j++) {
        for (int i = 0; i < CANTIDAD_CELDAS_FILA; i++) {
            valores[i] = self->juego[(j + (i * CANTIDAD_CELDAS_FILA))].valor;
        }

        if (_hay_valores_repetidos(valores)) {
            return false;
        }
    }

    return true;
}

static bool _validar_sectores(tablero_t *self) {
    int valores[CANTIDAD_CELDAS_FILA];
    int posicion_tablero = 0;

    for (int i = 0; i < CANTIDAD_CELDAS_FILA; i++) {
        posicion_tablero = (i * 3);

        if ((i > 2) && (i < 6)) {
            posicion_tablero += 18;
        }

        if (i > 5) {
            posicion_tablero += 36;
        }

        for (int j = 0; j < CANTIDAD_CELDAS_FILA; j++) {
            valores[j] = self->juego[posicion_tablero].valor;
            posicion_tablero++;

            if ( (posicion_tablero % 3) == 0 ) {
                posicion_tablero += 6;
            }
        }

        if (_hay_valores_repetidos(valores)) {
            return false;
        }
    }

    return true;
}

// ******************************** FUNCIONES ********************************

tablero_t *tablero_inicializar(const char *nombre_archivo) {
    tablero_t *tablero = calloc(1, sizeof(tablero_t));
    tablero->iniciales = calloc(TOTAL_CELDAS, sizeof(celda_t));
    tablero->juego = calloc(TOTAL_CELDAS, sizeof(celda_t));

    FILE *handler_tablero_inicial = fopen(nombre_archivo, "r");

    if (!handler_tablero_inicial) {
        return NULL;
    }

    char valor_inicial;
    int posicion = 0;

    while ((valor_inicial = fgetc(handler_tablero_inicial)) != EOF) {
        if ((valor_inicial != ' ') && (valor_inicial != '\n')) {
            if (valor_inicial == '0') {
                tablero->iniciales[posicion].modificable = true;
                tablero->juego[posicion].modificable = true;
            } else {
                tablero->iniciales[posicion].modificable = false;
                tablero->juego[posicion].modificable = false;
            }

            tablero->iniciales[posicion].valor = (valor_inicial - '0');
            tablero->juego[posicion].valor = (valor_inicial - '0');

            posicion++;
        }
    }

    fclose(handler_tablero_inicial);

    return tablero;
}

void tablero_get(tablero_t *self, char *resp) {
    int posicion = 0;

    strncpy(resp + posicion, BORDE_TABLERO, LONGITUD_FILA);
    posicion += LONGITUD_FILA;

    for (int j = 0; j < TOTAL_CELDAS; j += CANTIDAD_CELDAS_FILA) {
        for (int i = j; i < (j + CANTIDAD_CELDAS_FILA); i += 3) {
            strncpy(resp + posicion, "U", 1);
            posicion++;

            if (self->juego[i].valor != 0) {
                strncpy(resp + posicion, " ", 1);
                posicion++;

                memset(resp+posicion,(self->juego[i].valor+'0'),sizeof(char));
                posicion++;

                strncpy(resp + posicion, " ", 1);
                posicion++;
            } else {
                strncpy(resp + posicion, "   ", 3);
                posicion += 3;
            }

            strncpy(resp + posicion, "|", 1);
            posicion++;

            if (self->juego[i + 1].valor != 0) {
                strncpy(resp + posicion, " ", 1);
                posicion++;

                memset(resp+posicion,(self->juego[i+1].valor+'0'),sizeof(char));
                posicion++;

                strncpy(resp + posicion, " ", 1);
                posicion++;
            } else {
                strncpy(resp + posicion, "   ", 3);
                posicion += 3;
            }

            strncpy(resp + posicion, "|", 1);
            posicion++;

            if (self->juego[i + 2].valor != 0) {
                strncpy(resp + posicion, " ", 1);
                posicion++;

                memset(resp+posicion,(self->juego[i+2].valor+'0'),sizeof(char));
                posicion++;

                strncpy(resp + posicion, " ", 1);
                posicion++;
            } else {
                strncpy(resp + posicion, "   ", 3);
                posicion += 3;
            }
        }

        strncpy(resp + posicion, "U\n", 2);
        posicion += 2;

        if ((((j+1)%19)==0) || (((j+1)%46)==0) || (((j+1)%73)==0)) {
            strncpy(resp + posicion, BORDE_TABLERO, LONGITUD_FILA);
            posicion += LONGITUD_FILA;
        } else {
            strncpy(resp + posicion, SEPARADOR_LINEA, LONGITUD_FILA);
            posicion += LONGITUD_FILA;
        }
    }
}

bool tablero_put(tablero_t *self, int valor, int fila, int columna) {
    int posicion = (((fila - 1) * CANTIDAD_CELDAS_FILA) + ((columna - 1)));

    if (self->juego[posicion].modificable == false) {
        return false;
    }

    self->juego[posicion].valor = valor;

    return true;
}

bool tablero_verify(tablero_t *self) {
    if (!_validar_filas(self)) {
        return false;
    }

    if (!_validar_columnas(self)) {
        return false;
    }

    if (!_validar_sectores(self)) {
        return false;
    }

    return true;
}

void tablero_resetear(tablero_t *self) {
    for (int i = 0; i < TOTAL_CELDAS; i++) {
        memcpy(&(self->juego[i]).valor,&(self->iniciales[i]).valor,sizeof(int));
    }
}

void tablero_destruir(tablero_t *self) {
    free(self->iniciales);
    free(self->juego);
    free(self);
}

