#include "tablero.h"

#define LONGITUD_FILA 38
#define TOTAL_CELDAS 81
#define CANTIDAD_CELDAS_FILA 9

struct celda {
    bool modificable;
    int valor;
};

struct tablero {
    celda_t *valores_iniciales;
    celda_t *valores_juego;
};

// ************************************************ FUNCIONES PRIVADAS ************************************************

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
            valores[i] = self->valores_juego[j + i].valor;
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
            valores[i] = self->valores_juego[(j + (i * CANTIDAD_CELDAS_FILA))].valor;
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

            valores[j] = self->valores_juego[posicion_tablero].valor;
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

// ************************************************ FUNCIONES ************************************************

tablero_t *tablero_inicializar(const char *nombre_archivo) {
    tablero_t *tablero = calloc(1, sizeof(tablero_t));
    tablero->valores_iniciales = calloc(TOTAL_CELDAS, sizeof(celda_t));
    tablero->valores_juego = calloc(TOTAL_CELDAS, sizeof(celda_t));

    FILE *handler_tablero_inicial = fopen(nombre_archivo, "r");

    if (!handler_tablero_inicial) {
        return NULL;
    }

    char valor_inicial;
    int posicion_tablero = 0;

    while ((valor_inicial = fgetc(handler_tablero_inicial)) != EOF) {

        if ( (valor_inicial != ' ') && (valor_inicial != '\n') ) {

            tablero->valores_iniciales[posicion_tablero].modificable = (valor_inicial == '0') ? true : false;
            tablero->valores_iniciales[posicion_tablero].valor = (valor_inicial - '0');

            tablero->valores_juego[posicion_tablero].modificable = (valor_inicial == '0') ? true : false;
            tablero->valores_juego[posicion_tablero].valor = (valor_inicial - '0');

            posicion_tablero++;
        }
    }

    fclose(handler_tablero_inicial);

    return tablero;
}

void tablero_get(tablero_t *self, char *response) {
    int posicion_tablero = 0;

    strncpy(response + posicion_tablero, "U===========U===========U===========U\n", LONGITUD_FILA);
    posicion_tablero += LONGITUD_FILA;

    for(int j = 0; j < TOTAL_CELDAS; j += CANTIDAD_CELDAS_FILA) {

        for (int i = j; i < (j + CANTIDAD_CELDAS_FILA); i += 3) {

            strncpy(response + posicion_tablero, "U", 1);
            posicion_tablero++;

            if (self->valores_juego[i].valor != 0) {
                strncpy(response + posicion_tablero, " ", 1);
                posicion_tablero++;

                memset(response + posicion_tablero, (self->valores_juego[i].valor + '0'), sizeof(char));
                posicion_tablero++;

                strncpy(response + posicion_tablero, " ", 1);
                posicion_tablero++;
            } else {
                strncpy(response + posicion_tablero, "   ", 3);
                posicion_tablero += 3;
            }

            strncpy(response + posicion_tablero, "|", 1);
            posicion_tablero++;

            if (self->valores_juego[i + 1].valor != 0) {
                strncpy(response + posicion_tablero, " ", 1);
                posicion_tablero++;

                memset(response + posicion_tablero, (self->valores_juego[i + 1].valor + '0'), sizeof(char));
                posicion_tablero++;

                strncpy(response + posicion_tablero, " ", 1);
                posicion_tablero++;
            } else {
                strncpy(response + posicion_tablero, "   ", 3);
                posicion_tablero += 3;
            }

            strncpy(response + posicion_tablero, "|", 1);
            posicion_tablero++;

            if (self->valores_juego[i + 2].valor != 0) {
                strncpy(response + posicion_tablero, " ", 1);
                posicion_tablero++;

                memset(response + posicion_tablero, (self->valores_juego[i + 2].valor + '0'), sizeof(char));
                posicion_tablero++;

                strncpy(response + posicion_tablero, " ", 1);
                posicion_tablero++;
            } else {
                strncpy(response + posicion_tablero, "   ", 3);
                posicion_tablero += 3;
            }
        }

        strncpy(response + posicion_tablero, "U\n", 2);
        posicion_tablero += 2;

        if ((((j + 1) % 19) == 0) || (((j + 1) % 46) == 0) || (((j + 1) % 73) == 0)) {
            strncpy(response + posicion_tablero, "U===========U===========U===========U\n", LONGITUD_FILA);
            posicion_tablero += LONGITUD_FILA;
        } else {
            strncpy(response + posicion_tablero, "U---+---+---U---+---+---U---+---+---U\n", LONGITUD_FILA);
            posicion_tablero += LONGITUD_FILA;
        }
    }
}

bool tablero_put(tablero_t *self, int valor, int fila, int columna) {
    printf("%s%d%s%d%s%d%s", "\nComando PUT ", valor, " in ", fila, ",", columna, "\n");

    int posicion_tablero = (((fila - 1) * CANTIDAD_CELDAS_FILA) + ((columna - 1)));

    if (self->valores_juego[posicion_tablero].modificable == false) {
        printf("La celda no se puede modificar \n");

        return false;
    }

    self->valores_juego[posicion_tablero].valor = valor;

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
        memcpy(&(self->valores_juego[i]).valor, &(self->valores_iniciales[i]).valor, sizeof(int));
    }
}

void tablero_destruir(tablero_t *self) {
    free(self->valores_iniciales);
    free(self->valores_juego);
    free(self);
}

