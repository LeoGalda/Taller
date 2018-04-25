#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "servidor.h"
#include "cliente.h"

#define SUCCESS 0
#define ERROR 1

static int errorParametros() {
    fprintf(stderr, "Parámetros incorrectos.");
    return ERROR;
}

int main(int argc, char* argv[]) {
    int cantidadMinimaParametrosCliente = 6;
    int cantidadMinimaParametrosServidor = 4;
    if (argc < cantidadMinimaParametrosServidor) {
        return errorParametros();
    }
    if (strcmp(argv[1], "server") == 0) {
        if (argc != cantidadMinimaParametrosServidor) {
            return errorParametros();
        }
        Servidor servidor;
        servidor_create(&servidor, argv[2], argv[3]);
        servidor_aceptar_clientes(&servidor);
        servidor_destroy(&servidor);
        return SUCCESS;
    } else if (strcmp(argv[1], "client") == 0) {
        if (argc != cantidadMinimaParametrosCliente) {
            return errorParametros();
        }
        Cliente cliente;
        cliente_create(&cliente, argv[2], argv[3], argv[4], argv[5]);
        cliente_enviar_datos(&cliente);
        cliente_destroy(&cliente);
        return SUCCESS;
    } else {
        return errorParametros();
    }
}


