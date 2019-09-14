#include "Cliente.h"

void cliente_inicializar() {

    printf("Modo client \n");

    char *input = calloc(13, sizeof(char));
    char *comando = calloc(7, sizeof(char));
    char *comando_compuesto = calloc(3, sizeof(char));
    char *fila = calloc(1, sizeof(char));
    char *columna = calloc(1, sizeof(char));

    do {
        fgets(input, 13, stdin);

        strncpy(comando, input, (7 * sizeof(char)));

        if (strcmp(comando, "exit\n") == 0) {
            printf("E");
            break;
        }

        if (strcmp(comando, "verify\n") == 0) {
            printf("V");
            continue;
        }

        if (strcmp(comando, "get\n") == 0) {
            printf("G");
            continue;
        }

        if (strcmp(comando, "reset\n") == 0) {
            printf("R");
            continue;
        }

        strncpy(comando_compuesto, input, 3);

        if (strcmp(comando_compuesto, "put") == 0) {

            if ((((input[9] - '0') > 0) && ((input[9] - '0') < 10)) &&
                (((input[11] - '0') > 0) && ((input[11] - '0') < 10))) {
//            printf("Indices validos");

                if (((input[4] - '0') > 0) && ((input[4] - '0') < 10)) {
                    printf("P");
                    continue;
//                printf("valor valido");
                } else {
                    printf("Error en el valor ingresado. Rango soportado: [1,9]\n");
                    continue;
                }

            } else {
                printf("Error en los indices. Rango soportado: [1,9]\n");
                continue;
            }
        }

        printf("Modo no soportado \n");

    } while (strcmp(comando, "exit\n") != 0);

    free(input);
    free(comando);
    free(comando_compuesto);
    free(fila);
    free(columna);
}
