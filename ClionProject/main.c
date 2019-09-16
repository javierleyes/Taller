#include <stdio.h>
#include <string.h>

#include "tablero.h"
#include "Cliente.h"
#include "Servidor.h"

#define MODO_SERVER "server"
#define MODO_CLIENT "client"

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("Modo no soportado, el primer parametro debe ser server o client\n");
        return 1;
    }

    if (argc == 2) {

        if (strcmp(argv[1], "server") == 0) {
            printf("Uso: ./tp server <puerto>\n");
            return 1;
        }

        if (strcmp(argv[1], "client") == 0) {
            printf("Uso: ./tp client <host> <puerto>\n");
            return 1;
        }

        printf("Modo no soportado, el primer parametro debe ser server o client\n");
        return 1;
    }

    if ((argc == 3) && (strcmp(argv[1], MODO_SERVER) == 0)) {
        servidor_t *server = servidor_inicializar(strtoul(argv[2], NULL, 0));
        servidor_destruir(server);
        return 0;
    }

    if ((argc == 4) && (strcmp(argv[1], MODO_CLIENT) == 0)) {
        cliente_inicializar();
        return 0;
    }

    printf("Modo no soportado, el primer parametro debe ser server o client\n");
    return 1;
}