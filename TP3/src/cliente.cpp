#include "cliente.h"    
#include "common_FormatoComu.h"
#include <stdio.h>
#include <string.h>

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
            int tamanioArch = accion->getSizeFile();
            unsigned char envio[4];
            int tam = tamanioArch;
            tamanioArch = htonl(tamanioArch);
            memcpy(&envio, &tamanioArch, sizeof (tam));
            Buffer buffer(tam);
            status = socket.enviarDatos(&envio[0], 4);
            accion->procesarArch((char *)buffer.getData());
            status = socket.enviarDatos(buffer.getData(), tam);
        } else {
            printf("error en status???");
        }
    }
    return status;
}

Cliente::~Cliente() {
}

