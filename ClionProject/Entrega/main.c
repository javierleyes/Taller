#include <stdio.h>
#include <string.h>

#include "Cliente.h"
#include "Servidor.h"

#define MODO_SERVER "server"
#define MODO_CLIENT "client"

#define USO "Modo no soportado, el primer parametro debe ser server o client\n"

#define MODO_USO_SERVER "Uso: ./tp server <puerto>\n"
#define MODO_USO_CLIENT "Uso: ./tp client <host> <puerto>\n"

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("%s", USO);
        return 1;
    }

    if (argc == 2) {
        if (strcmp(argv[1], MODO_SERVER) == 0) {
            printf("%s", MODO_USO_SERVER);
            return 1;
        }
        if (strcmp(argv[1], MODO_CLIENT) == 0) {
            printf("%s", MODO_USO_CLIENT);
            return 1;
        }
        printf("%s", USO);
        return 1;
    }

    if ((argc == 3) && (strcmp(argv[1], MODO_SERVER) == 0)) {
        servidor_t *server = servidor_inicializar(argv[2]);
        servidor_escuchar(server);
        servidor_destruir(server);
        return 0;
    }

    if ((argc == 4) && (strcmp(argv[1], MODO_CLIENT) == 0)) {
        cliente_t *client = cliente_inicializar(argv[2], argv[3]);
        cliente_recibir_comandos(client);
        cliente_destruir(client);
        return 0;
    }

    printf("%s", USO);
    return 1;
}
