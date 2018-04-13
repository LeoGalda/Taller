#define _POSIX_C_SOURCE 200112L

#include <errno.h>
#include <netdb.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include "cliente.h"

#define REQUEST_MAX_LEN 64

void cliente_create(Cliente * this, char* ip, char *puerto,
        char *key, char* arch) {
    Buffer buffer;
    Socket socket;
    socket_crear(&socket, puerto, ip);
    buffer_crear(&buffer, REQUEST_MAX_LEN);
    this->socket = socket;
    this->buffer = buffer;
    this->key = key;
    this->entrada = fopen(arch, "r");
}

static void ejecutarEncriptador(Cliente *this,
        int *prgaI, int *prgaJ, int control,
        Encriptador *encriptador) {
    encriptador_crear(encriptador, clave);
    if (control == 0) {
        encriptador_fase_KSA(encriptador);
    }
    encriptador_encriptar(encriptador, input, REQUEST_MAX_LEN, prgaI, prgaJ);
    encriptador_salida_estandar(encriptador);
    encriptador_salida_errores(encriptador);
}

int cliente_enviar_datos(Cliente *this) {
    int prgaI = 0;
    int prgaJ = 0;
    int control = 0;
    Encriptador encriptador;
    if (socket_configurar(&this->socket, 1)) return 1;
    if (socket_conectar(&this->socket, 1)) return 1;
    socket_aceptar(&this->socket);
    while (!feof(this->entrada)) {
        ejecutarEncriptador(this, &prgaI, &prgaJ, control, &encriptador);
        status = socket_enviar_datos(&cliente, &encriptador);
        if (status) {
            printf("Error al enviar los datos\n");
            cliente_destroy(&cliente);
            return 1;
        }
        encriptador_destroy(&desencriptador);
        control++;
    }
    return 0;
}

void cliente_destroy(Cliente *this) {
    socket_destroy(&this->socket);
    buffer_destroy(&this->buffer);
    fclose(this->salida);
}