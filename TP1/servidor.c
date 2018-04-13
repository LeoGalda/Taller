#define _POSIX_C_SOURCE 200112L

#include <errno.h>
#include <netdb.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "buffer.h"
#include "encriptador.h"
#include "servidor.h"
#include "socket.h"


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

static void servidor_ejecutar_desencriptador(Servidor *this,
        Encriptador *desencriptador, int *prgaI, int *prgaJ, int control) {
    encriptador_crear(desencriptador, this->key);
    if (control == 0) {
        encriptador_fase_KSA(desencriptador);
    }
    encriptador_desencriptar(desencriptador, &this->buffer, prgaI, prgaJ);
    encriptador_salida_estandar(desencriptador);
    encriptador_salida_errores(desencriptador);
}

int servidor_recibir_datos(Servidor *this) {
    int prgaI = 0;
    int prgaJ = 0;
    int control = 0;
    bool corriendo = true;
    Encriptador desencriptador;
    if (socket_configurar(&this->socket, 1)) return 1;
    if (socket_conectar(&this->socket, 1)) return 1;
    socket_aceptar(&this->socket);
    while (corriendo) {
        if (this->socket.peerskt == -1) {
            printf("Error: %s\n", strerror(errno));
            corriendo = false;
        } else {
            corriendo = socket_recibir_datos(&this->socket, &this->buffer);
            servidor_ejecutar_desencriptador(this, &desencriptador,
                    &prgaI, &prgaJ, control);
            encriptador_guardar_en_salida(&desencriptador, this->salida);
            encriptador_destroy(&desencriptador);
            control++;
        }
    }
    return 0;
}

void servidor_destroy(Servidor *this) {
    socket_destroy(&this->socket);
    buffer_destroy(&this->buffer);
    fclose(this->salida);
}