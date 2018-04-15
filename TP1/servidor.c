#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "encriptador.h"
#include "servidor.h"

#define RESPONSE_MAX_LEN 50

void servidor_create(Servidor *this, char *puerto, char *key) {
    Buffer buffer;
    Socket socket;
    socket_crear(&socket, puerto, NULL);
    buffer_crear(&buffer, RESPONSE_MAX_LEN);
    this->socket = socket;
    this->buffer = buffer;
    this->key = key;
    this->salida = fopen("./out", "wg");
}

int servidor_recibir_datos(Servidor *this) {
    bool corriendo = true;
    if (socket_configurar(&this->socket, 1)) return 1;
    if (socket_conectar(&this->socket, 1)) return 1;
    socket_aceptar(&this->socket);
    Encriptador desencriptador;
    encriptador_crear(&desencriptador, this->key);
    encriptador_fase_KSA(&desencriptador);
    while (corriendo) {
        if (this->socket.peerskt == -1) {
            printf("Error: %s\n", strerror(errno));
            corriendo = false;
        } else {
            corriendo = socket_recibir_datos(&this->socket, &this->buffer);
            encriptador_desencriptar(&desencriptador, this);
        }
    }
    encriptador_destroy(&desencriptador);
    return 0;
}

void servidor_destroy(Servidor *this) {
    socket_destroy(&this->socket);
    buffer_destroy(&this->buffer);
    fclose(this->salida);
}
