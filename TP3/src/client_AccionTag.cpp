#include "client_AccionTag.h"
#include <iostream>
#include <string.h>

AccionTag::AccionTag(char *version) : version(version) {
}

void AccionTag::ejecutar() {
    unsigned char aux[4];
    this->data.push_back((unsigned char) this->getValorNumerico());
    int cantidadHash = this->hashes.size();
    memcpy(&aux, &cantidadHash, 4);
    for (unsigned int j = 0; j < 4; ++j) {
        this->data.push_back(aux[j]);
        aux[j] = 0;
    }
    int tamanioVersion = this->version.size();
    memcpy(&aux, &tamanioVersion, 4);
    for (unsigned int j = 0; j < 4; ++j) {
        this->data.push_back(aux[j]);
        aux[j] = 0;
    }
    for (int j = 0; j < (int) this->version.size(); ++j) {
        this->data.push_back((unsigned char) this->version[j]);
    }
}

void AccionTag::agregarHash(char *hash) {
    this->hashes.push_back(hash);
}

int AccionTag::getValorNumerico() {
    return 2;
}

void AccionTag::enviar(Socket* socket) {
    int status;
    status = socket->enviarDatos(&this->data[0], this->getTamanio());
    if (status) {
        printf("Error al enviar los datos\n");
        throw -1;
    }
    std::vector<unsigned char> dataAEnviar;
    for (size_t i = 0; i < this->hashes.size(); ++i){
        unsigned char aux[4];
        int cantidadHash = this->hashes[i].size();
        memcpy(&aux, &cantidadHash, 4);
        for (unsigned int j = 0; j < 4; ++j) {
            dataAEnviar.push_back(aux[j]);
        }
        for (int j = 0; j < cantidadHash; ++j) {
            dataAEnviar.push_back((unsigned char) this->hashes[i][j]);
        }
        socket->enviarDatos(&dataAEnviar[0], (int) dataAEnviar.size());
        dataAEnviar.clear();
    }
}

int AccionTag::getTamanio() {
    return this->data.size();
}

void AccionTag::responder(Socket* socket) {
    unsigned char tipo = 0;
    socket->recibirDatos(&tipo, 1);
    if(!tipo){
        std::cout<<"Error: tag/hash incorrecto."<<std::endl;
    }
}

AccionTag::~AccionTag() {
}

