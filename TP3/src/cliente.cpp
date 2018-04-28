#include "cliente.h"
#include "common_FormatoComu.h"

Cliente::Cliente(char *ip, char *puerto) : buffer(REQUEST_MAX_LEN) {    
    this->socket.conectar(puerto, ip);
}

int Cliente::ejecutar(Accion *accion) {
    int status;   
    status = 0;
    accion->ejecutar();  
    FormatoComu formato;
    formato.parsear(accion->getData());
//    formato.mostrar();
    status = socket.enviarDatos(&formato);
    if (status) {
        printf("Error al enviar los datos\n");
        return 1;
    }
    return 0;
}

Cliente::~Cliente() {
}

