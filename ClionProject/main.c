#include <stdio.h>
#include <string.h>

#include "tablero.h"
#include "Cliente.h"
#include "Servidor.h"

#define MODO_SERVER "server"
#define MODO_CLIENT "client"

//**************************************************************************************************
//*************************************** FUNCIONES PRIVADAS ***************************************
//**************************************************************************************************

static bool determinar_modo_operacion(int argc, char **argv) {
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

//**************************************************************************************************

int main(int argc, char *argv[]) {
    determinar_modo_operacion(argc, argv);


//    int socketFd = -1;
//
//    const char* hostname = "fi.uba.ar";
//    const char* servicename = "http";
//
//    // Utilizamos hints para "filtrar" las direcciones que me interesan
//    struct addrinfo hints;
//    // ai_list será la lista de address info, ptr mi iterados
//    struct addrinfo *ai_list, *ptr;
//
//    // Limpio hints
//    memset(&hints, 0, sizeof(struct addrinfo));
//    hints.ai_family = AF_INET;       /* IPv4 (or AF_INET6 for IPv6)     */
//    hints.ai_socktype = SOCK_STREAM; /* TCP  (or SOCK_DGRAM for UDP)    */
//    hints.ai_flags = 0;              /* None (or AI_PASSIVE for server) */
//
//    // El servicio se obtiene consultando el archivo /etc/service
//    int s = getaddrinfo(hostname, servicename, &hints, &ai_list);
//
//    // chequeo error
//    if (s != 0) {
//        printf("Error in getaddrinfo: %s\n", gai_strerror(s));
//        return 1;
//    }
//
//    // Ahora conectamos el socket
//    bool are_we_connected = false;
//    for (ptr = ai_list; ptr != NULL && are_we_connected == false; ptr = ptr->ai_next) {
//
//        // creo el socket
//        socketFd = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
//
//        if (socketFd == -1) {
//            printf("socket creation failed...\n");
//            exit(0);
//        } else {
//            printf("Socket successfully created..\n");
//        }
//
//        // conectamos el socket
//        int res = connect(socketFd, ptr->ai_addr, ptr->ai_addrlen);
//        if (res == -1) {
//            printf("Error: %s\n", strerror(errno));
//            close(socketFd);
//        }
//
//        are_we_connected = (s != -1); // nos conectamos?
//    }
//
//    freeaddrinfo(ai_list);
//
//    if (are_we_connected == false) {
//        return 1; // nos quedamos sin direcciones validas y no nos pudimos conectar :(
//    }
//
//    // mensaje
//
//    close(socketFd);
//
//    tablero_exit(tablero);

    return 0;
}