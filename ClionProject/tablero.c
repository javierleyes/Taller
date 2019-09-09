#include "tablero.h"

struct celda {
    bool modificable;
    int valor;
};

struct tablero {
    celda_t *valores_iniciales;
    celda_t *valores_juego;
};

//**************************************************************************************************
//*************************************** FUNCIONES PRIVADAS ***************************************
//**************************************************************************************************

bool hay_valores_repetidos(int *valores) {

    for (int i = 0; i < 9; i++) {

        for (int j = i + 1; j < 9; j++) {

            if ( (valores[i] == valores[j]) && (valores[i] != 0) ) {
                return true;
            }
        }
    }

    return false;
}

bool validar_filas(tablero_t * self) {
    int valores[9];

    for (int j = 0; j < 81; j += 9) {

        for (int i = 0; i < 9; i++) {
            valores[i] = self->valores_juego[j + i].valor;
        }

        if (hay_valores_repetidos(valores)) {
            return false;
        }
    }

    return true;
}

bool validar_columnas(tablero_t *self) {
    int valores[9];

    for (int j = 0; j < 9; j++) {

        for (int i = 0; i < 9; i++) {
            valores[i] = self->valores_juego[(j + (i * 9))].valor;
        }

        if (hay_valores_repetidos(valores)) {
            return false;
        }
    }

    return true;
}

bool validar_sectores(tablero_t *self) {
    int valores[9];
    int posicion_tablero = 0;

    for (int i = 0; i < 9; i++) {

        posicion_tablero = (i * 3);

        if ((i > 2) && (i < 6)) {
            posicion_tablero += 18;
        }

        if (i > 5) {
            posicion_tablero += 36;
        }

        for (int j = 0; j < 9; j++) {

            valores[j] = self->valores_juego[posicion_tablero].valor;
            posicion_tablero++;

            if ( (posicion_tablero % 3) == 0 ) {
                posicion_tablero += 6;
            }
        }

        if (hay_valores_repetidos(valores)) {
            return false;
        }
    }

    return true;
}

//**************************************************************************************************
//*************************************** FUNCIONES ************************************************
//**************************************************************************************************

tablero_t *tablero_inicializar(const char *nombre_archivo) {

    printf("\nFuncion inicializar \n");

    tablero_t *tablero = calloc(1, sizeof(tablero_t));
    tablero->valores_iniciales = calloc(81, sizeof(celda_t));
    tablero->valores_juego = calloc(81, sizeof(celda_t));

    FILE *handler_tablero_inicial = fopen(nombre_archivo, "r");

    if (!handler_tablero_inicial) {
        return NULL;
    }

    char valor_inicial;
    int posicion_tablero = 0;

    while ((valor_inicial = fgetc(handler_tablero_inicial)) != EOF) {

        if ( (valor_inicial != ' ') && (valor_inicial != '\n') ) {
//            putchar(valor_inicial);

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

void tablero_get(tablero_t *self) {

    printf("\nComando GET \n");

    printf("U===========U===========U===========U\n");

    for(int j = 0; j < 81; j += 9) {

        for (int i = j; i < (j + 9); i += 3) {

            printf("U");

            if (self->valores_juego[i].valor != 0) {
                printf("%1s%d%1s", " ", self->valores_juego[i].valor, " ");
            } else {
                printf("%1s%1s%1s", " ", " ", " ");
            }

            printf("|");

            if (self->valores_juego[i + 1].valor != 0) {
                printf("%1s%d%1s", " ", self->valores_juego[i + 1].valor, " ");
            } else {
                printf("%1s%1s%1s", " ", " ", " ");
            }

            printf("|");

            if (self->valores_juego[i + 2].valor != 0) {
                printf("%1s%d%1s", " ", self->valores_juego[i + 2].valor, " ");
            } else {
                printf("%1s%1s%1s", " ", " ", " ");
            }
        }

        printf("U \n");

        if ((((j + 1) % 19) == 0) || (((j + 1) % 46) == 0) || (((j + 1) % 73) == 0)) {
            printf("U===========U===========U===========U\n");
        } else {
            printf("U---+---+---U---+---+---U---+---+---U\n");
        }
    }
}

void tablero_put(tablero_t *self, int valor, int fila, int columna) {

    printf("%s%d%s%d%s%d%s", "\nComando PUT ", valor, " in ", fila, ",", columna, "\n");

    int posicion_tablero = (((fila - 1) * 9) + ((columna - 1)));

    if (self->valores_juego[posicion_tablero].modificable == false) {
        printf("La celda no se puede modificar \n");

        return;
    }

    self->valores_juego[posicion_tablero].valor = valor;

    tablero_get(self);
}

bool tablero_verify(tablero_t *self) {

    printf("\nComando verify \n");

    if (!validar_filas(self)) {
        printf("ERROR\n");
        return false;
    }

    if (!validar_columnas(self)) {
        printf("ERROR\n");
        return false;
    }

    if (!validar_sectores(self)) {
        printf("ERROR\n");
        return false;
    }

    printf("OK\n");
    return true;
}

void tablero_resetear(tablero_t *self) {

    printf("\nComando resetear \n");

    for (int i = 0; i < 81; i++) {
        memcpy(&(self->valores_juego[i]).valor, &(self->valores_iniciales[i]).valor, sizeof(int));
    }
}

void tablero_exit(tablero_t *self) {

    printf("\nComando exito \n");

    // cerrar socket

    tablero_destruir(self);
}

void tablero_destruir(tablero_t *self) {

    printf("\nFuncion destruir \n");

    free(self->valores_iniciales);
    free(self->valores_juego);
    free(self);
}

