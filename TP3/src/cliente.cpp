#include "cliente.h"    
#include "common_FormatoComu.h"

Cliente::Cliente(char *ip, char *puerto) {
    this->socket.conectar(puerto, ip);
}

int Cliente::ejecutar(Accion *accion) {
    int status;
    status = 0;
    accion->ejecutar();
    status = socket.enviarDatos(accion->getDataEnPos(0), accion->getTamanio());
    if (status) {
        printf("Error al enviar los datos\n");
        return 1;
    }
    if (accion->getValorNumerico() != 2) {
        unsigned char tipo = 0;
        status = socket.recibirDatos(&tipo, 1);
        if (status && tipo == 1) {            
            accion->procesarArch();
//          status = socket.enviarDatos(accion->getArchivo(),accion->getTamanioArch);
        } else {
            printf("error en status???");
        }
    }
    return status;
}

Cliente::~Cliente() {
}

