#include "client_AccionPull.h"
#include <iostream>
#include <string.h>

AccionPull::AccionPull(char *hash) : hash(hash) {
}

void AccionPull::ejecutar() {
    unsigned char aux[4];
    unsigned int tamanioHash = (unsigned int) this->hash.size();
    this->data.push_back((unsigned char) this->getValorNumerico());
    memcpy(&aux, &tamanioHash, 4);
    for (unsigned int j = 0; j < 4; ++j) {
        this->data.push_back(aux[j]);
    }
    for (unsigned int j = 0; j < (unsigned int) this->hash.size(); ++j) {
        this->data.push_back((unsigned char) this->hash[j]);
    }
}

void AccionPull::enviar(Socket* socket) {
    int status;
    status = socket->enviarDatos(&this->data[0], this->getTamanio());
    if (status) {
        printf("Error al enviar los datos\n");
        throw -1;
    }
}

void AccionPull::responder(Socket* socket) {

}

int AccionPull::getTamanio() {
    return this->data.size();
}


int AccionPull::getValorNumerico() {
    return 3;
}

AccionPull::~AccionPull() {
}

