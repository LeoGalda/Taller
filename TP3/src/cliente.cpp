#include "cliente.h"    
#include <stdio.h>
#include <string.h>

Cliente::Cliente(char *ip, char *puerto) {
    this->socket.conectar(puerto, ip);
}

int Cliente::ejecutar(Accion *accion) {
    Protocolo protocolo(&this->socket);
    accion->ejecutar(&protocolo);
    accion->enviar(&protocolo);
    accion->responder(&protocolo);
    return 0;
}
//int Cliente::ejecutar(Accion *accion) {    
//    try{
//        accion->ejecutar();
//        accion->enviar(&this->socket);
//        accion->responder(&this->socket);
//    }catch(...){
//        printf("error");
//    }   
//    return 0;
//}

Cliente::~Cliente() {
}

