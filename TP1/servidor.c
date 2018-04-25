#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "encriptador.h"
#include "servidor.h"

#define RESPONSE_MAX_LEN 50

void servidor_create(Servidor *this, char *puerto, char *key) {
    buffer_crear(&this->buffer, RESPONSE_MAX_LEN);
    socket_crear(&this->socket);
    socket_bind(&this->socket, puerto);
    socket_listen(&this->socket);
    encriptador_crear(&this->desencriptador);
    encriptador_fase_KSA(&this->desencriptador, key);
    this->salida = fopen("./out", "wb");
}

int servidor_aceptar_clientes(Servidor *this) {
    Socket peerskt;
    socket_aceptar(&this->socket, &peerskt);
    int corriendo = 1;
    while (corriendo) {
        if (socket_get_FD(&this->socket) == -1) {
            printf("Error: %s\n", strerror(errno));
            corriendo = 0;
        } else {
            corriendo = socket_recibir_datos(&peerskt, &this->buffer);
            encriptador_desencriptar(&this->desencriptador, this->salida,
                    &this->buffer);
            fwrite(buffer_get_data(&this->buffer), sizeof(unsigned char),
                    buffer_get_usado(&this->buffer),
                    this->salida);
        }
    }
    socket_destroy(&peerskt);
    return 0;
}

void servidor_destroy(Servidor *this) {
    socket_destroy(&this->socket);
    buffer_destroy(&this->buffer);
    encriptador_destroy(&this->desencriptador);
    fclose(this->salida);
}
