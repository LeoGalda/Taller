#include "cliente.h"

Cliente::Cliente(char *ip, char *puerto) : buffer(REQUEST_MAX_LEN) {    
    this->socket.conectar(puerto, ip);
}

int Cliente::ejecutar(Accion *accion) {
//    int status;
    //    if (buffer.almacenarDatos(accion->ejecutar())) return 1;    
    int cantidad = accion->ejecutar();
    //agregar el data al buffer y enviar los datos    
//    this->buffer.setUsado(cantidad);
//    status = socket.enviarDatos(&this->socket, &this->buffer);
//    if (status) {
//        printf("Error al enviar los datos\n");
//        return 1;
//    }
    return cantidad;
}

Cliente::~Cliente() {
}

