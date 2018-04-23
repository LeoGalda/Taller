#include "cliente.h"

Cliente::Cliente(char *ip, char *puerto) : socket(puerto, ip),
                                           buffer(REQUEST_MAX_LEN) {
}


int Cliente::ejecutar(Accion *accion) {
    int status;
    if (socket.configurar(0)) return 1;
    if (socket.conectar(0)) return 1;
    if (buffer.almacenarDatos(accion->ejecutar())) return 1;    
    cantidad = accion->ejecutar();
//agregar el data al buffer y enviar los datos    
    this->buffer.setUsado(cantidad);
    status = socket.enviarDatos(&this->socket, &this->buffer);
    if (status) {
        printf("Error al enviar los datos\n");
        return 1;
    }
    return 0;
}

Cliente::~Cliente() {
}

