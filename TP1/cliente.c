#include <stdio.h>
#include <stdlib.h>

#include "cliente.h"
#include "encriptador.h"


#define REQUEST_MAX_LEN 64

void cliente_create(Cliente * this, char* ip, char *puerto,
        char *key, char* arch) {
    buffer_crear(&this->buffer, REQUEST_MAX_LEN);
    socket_crear(&this->socket);
    socket_conectar(&this->socket, puerto, ip);
    encriptador_crear(&this->encriptador); 
    encriptador_fase_KSA(&this->encriptador,key);
    this->entrada = fopen(arch, "rb");
}

int cliente_enviar_datos(Cliente *this) {    
    int status;         
    while (!feof(this->entrada)) {
            encriptador_encriptar(&this->encriptador, this);
        status = socket_enviar_datos(&this->socket, &this->buffer);
        if (status) {
            printf("Error al enviar los datos\n");
            return 1;
        }        
    }

    return 0;
}

void cliente_destroy(Cliente *this) {
    socket_destroy(&this->socket);
    buffer_destroy(&this->buffer);
    encriptador_destroy(&encriptador);
    fclose(this->entrada);
}
