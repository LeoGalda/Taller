#include <stdio.h>
#include <stdlib.h>

#include "cliente.h"
#include "encriptador.h"


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

static void ejecutarEncriptador(Cliente *this, int *prgaI, int *prgaJ,
            int control, Encriptador *encriptador) {
    encriptador_crear(encriptador, this->key);
    if (control == 0) {
        encriptador_fase_KSA(encriptador);
    }
    encriptador_encriptar(encriptador, this, prgaI, prgaJ);
    encriptador_salida_estandar(encriptador);
    encriptador_salida_errores(encriptador);
}


int cliente_enviar_datos(Cliente *this) {
    int prgaI = 0;
    int prgaJ = 0;
    int control = 0;
    int status;
    Encriptador encriptador;
    if (socket_configurar(&this->socket, 0)) return 1;
    if (socket_conectar(&this->socket, 0)) return 1;
    socket_aceptar(&this->socket);
    while (!feof(this->entrada)) {
        ejecutarEncriptador(this, &prgaI, &prgaJ, control, &encriptador); 
        status = socket_enviar_datos(&this->socket, &this->buffer);
        if (status) {
            printf("Error al enviar los datos\n");
            return 1;
        }
        encriptador_destroy(&encriptador);
        control++;
    }
    return 0;
}

void cliente_destroy(Cliente *this) {
    socket_destroy(&this->socket);
    buffer_destroy(&this->buffer);
    fclose(this->entrada);
}