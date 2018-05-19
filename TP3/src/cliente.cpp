#include "cliente.h"    
#include <stdio.h>
#include <string.h>

Cliente::Cliente(char *ip, char *puerto) {
    this->socket.conectar(puerto, ip);
}

int Cliente::ejecutar(Accion *accion) {
    Protocolo protocolo(&this->socket);
    accion->ejecutar(&protocolo);
    accion->responder(&protocolo);
    return 0;
}

Cliente::~Cliente() {
}

