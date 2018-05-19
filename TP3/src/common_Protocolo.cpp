#include "common_Protocolo.h"
#include <string.h>
#include <iostream>
#include <string>

Protocolo::Protocolo(Socket *socket) : socket(socket) {
}

std::string Protocolo::recibirYFormatear() const {
    int sizeDeUINT = sizeof(unsigned int);
    unsigned int longitudARecibir[1];
    this->socket->recibirDatos((unsigned char*) longitudARecibir, sizeDeUINT);
    Buffer buffer(ntohl(*longitudARecibir));    
    this->socket->recibirDatos(buffer.getData(), buffer.getTamanio());
    return this->convertirAString(&buffer);
}

std::string Protocolo::convertirAString(Buffer *buffer) const {
    std::string dataString(buffer->getData(), buffer->getData() +
            buffer->getTamanio() / sizeof(buffer->getDataEnPos(0)));
    return dataString;
}

void Protocolo::enviarComando(unsigned char comando) {
    this->socket->enviarDatos(&comando, TAMANIO_DEL_COMANDO);
}

unsigned char Protocolo::recibirComando() {
    unsigned char comando = 0;
    this->socket->recibirDatos(&comando, TAMANIO_DEL_COMANDO);
    return comando;
}

void Protocolo::formatearYEnviarLongitud(int longitud) {
    unsigned char aux[TAMANIO_DEL_ENVIO_LONG];  
    longitud = htonl(longitud);
    memcpy(&aux, &longitud, TAMANIO_DEL_ENVIO_LONG);    
    this->socket->enviarDatos(aux, TAMANIO_DEL_ENVIO_LONG);
}

void Protocolo::enviarData(std::string &data) {
    this->socket->enviarDatos((unsigned char*) data.c_str(), (int) data.size());
}

int Protocolo::recibirLongitud() {
    int sizeDeUINT = sizeof(unsigned int);
    unsigned int longitud[1];
    this->socket->recibirDatos((unsigned char*) longitud, sizeDeUINT);
    return ntohl(*longitud);
}

Protocolo::~Protocolo() {
}

