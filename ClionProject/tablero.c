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

bool validar_repetidos(int valores[]) {

    for (int i = 0; i < 9; i++) {

        for (int j = i + 1; j < 9; j++) {

            if ( (valores[i] == valores[j]) && (valores[i] != 0) ) {
                return false;
            }
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

void tablero_put(tablero_t *self, int valor, int coordenada_x, int coordenada_y) {

    printf("%s%d%s%d%s%d%s","\nComando PUT ", valor, " in ", coordenada_x, ",", coordenada_y, "\n");

    int posicion_tablero = (coordenada_x - 1) + ((coordenada_y - 1) * 9);

    if (self->valores_juego[posicion_tablero].modificable == false) {
        printf("La celda no se puede modificar \n");

        return;
    }

    self->valores_juego[posicion_tablero].valor = valor;

    tablero_get(self);
}

bool tablero_verify(tablero_t *self) {

    printf("\nComando verify \n");

    int valores[9];
    bool valido = true;

    // valido filas
    for (int j = 0; j < 81; j += 9) {

        for (int i = 0; i < 9; i++) {
            valores[i] = self->valores_juego[j + i].valor;
        }

        valido = validar_repetidos(valores);

        if (!valido) {
            printf("ERROR\n");
            return false;
        }
    }

    // valido columnas
    for (int j = 0; j < 9; j++) {

        for (int i = 0; i < 9; i++) {
            valores[i] = self->valores_juego[(j + (i * 9))].valor;
        }

        valido = validar_repetidos(valores);

        if (!valido) {
            printf("ERROR\n");
            return false;
        }
    }

    // valido sectores
    int posicion_tablero = 0;

    for (int i = 0; i < 9; i++) {

        for (int j = 0; j < 9; j++) {

            valores[j] = self->valores_juego[posicion_tablero].valor;
            posicion_tablero++;

            if ( (posicion_tablero % 3) == 0 ) {
                posicion_tablero += 6;
            }
        }

        valido = validar_repetidos(valores);

        if (!valido) {
            printf("ERROR\n");
            return false;
        }
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

