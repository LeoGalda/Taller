#include "client_AccionPush.h"
#include "common_ExcpError.h"
#include <iostream>
#include <string.h>
#include <arpa/inet.h>
#include <vector>
#include <string>

AccionPush::AccionPush(char *arch, char *hash) : hash(hash),
                                                file(arch, std::ios::in) {
}

void AccionPush::ejecutar() {
    unsigned char aux[4];
    unsigned int tamanioHash = (unsigned int) this->hash.size();
    unsigned int tamanioNombre = (unsigned int) this->file.getTamanioNombre();
    this->data.push_back((unsigned char) this->getValorNumerico());
    memcpy(&aux, &tamanioNombre, 4);
    for (unsigned int j = 0; j < 4; ++j) {
        this->data.push_back(aux[j]);
        aux[j] = 0;
    }
    std::string nombreArchivo = this->file.getNombreArchivo();
    for (unsigned int j = 0; j < (unsigned int) tamanioNombre; ++j) {
        this->data.push_back((unsigned char) nombreArchivo[j]);
    }
    memcpy(&aux, &tamanioHash, 4);
    for (unsigned int j = 0; j < 4; ++j) {
        this->data.push_back(aux[j]);
    }
    for (unsigned int j = 0; j < (unsigned int) this->hash.size(); ++j) {
        this->data.push_back((unsigned char) this->hash[j]);
    }
}

void AccionPush::enviar(Socket *socket) {
    int status;    
    status = socket->enviarDatos(&this->data[0], this->getTamanio());
    if (status) {
        printf("Error al enviar los datos\n");
        throw -1;
    }
}

void AccionPush::responder(Socket* socket) {
    int status;
    unsigned char tipo = 0;
    status = socket->recibirDatos(&tipo, 1);
    if (status && tipo == 1) {
        int tamanioArch = this->getSizeFile();
        unsigned char envio[4];
        memcpy(&envio, &tamanioArch, sizeof (tamanioArch));
        Buffer buffer(tamanioArch);
        status = socket->enviarDatos(&envio[0], 4);
        this->procesarArch((char *) buffer.getData());
        status = socket->enviarDatos(buffer.getData(), tamanioArch);
    } else {
    }
}

int AccionPush::getValorNumerico() {
    return 1;
}

int AccionPush::getTamanio() {
    return this->data.size();
}

void AccionPush::procesarArch(char *data) {
    int tamanio = this->getSizeFile();
    this->file.leer(data, tamanio);
}

int AccionPush::getSizeFile() {
    return this->file.getTamanioArch();
}

AccionPush::~AccionPush() {
}

