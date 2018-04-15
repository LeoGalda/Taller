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

int cliente_enviar_datos(Cliente *this) {    
    int status;    
    if (socket_configurar(&this->socket, 0)) return 1;
    if (socket_conectar(&this->socket, 0)) return 1;
    socket_aceptar(&this->socket);
    Encriptador encriptador;
    encriptador_crear(&encriptador, this->key);    
    encriptador_fase_KSA(&encriptador);
    while (!feof(this->entrada)) {
            encriptador_encriptar(&encriptador, this);
        status = socket_enviar_datos(&this->socket, &this->buffer);
        if (status) {
            printf("Error al enviar los datos\n");
            return 1;
        }        
    }
    encriptador_destroy(&encriptador);
    return 0;
}

void cliente_destroy(Cliente *this) {
    socket_destroy(&this->socket);
    buffer_destroy(&this->buffer);
    fclose(this->entrada);
}
