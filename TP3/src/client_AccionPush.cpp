#include "client_AccionPush.h"
#include "common_ExcpError.h"
#include <iostream>
#include <string.h>
#include <arpa/inet.h>

AccionPush::AccionPush(char *arch, char *hash) : nombreArchivo(arch), hash(hash) {
    this->archivo.open(arch);
    if (this->archivo.fail()) {
        int linea = -1;
        std::string error = "Error al abrir archivo de ejecucion PUSH";
        throw new ExcpError(error, linea);
    }
}

int AccionPush::ejecutar() {
    unsigned char aux[4];
    unsigned int tamanioHash = (unsigned int) this->hash.size();
    unsigned int tamanioNombre = (unsigned int) this->nombreArchivo.size();
    tamanioHash = htonl(tamanioHash);
    tamanioNombre = htonl(tamanioNombre);
    this->data.push_back((unsigned char) this->getValorNumerico());    

    memcpy(&aux, &tamanioNombre, 4);
    for (unsigned int j = 0; j < 4; ++j) {
        this->data.push_back(aux[j]);
        aux[j] = 0;
    }
    for (unsigned int j = 0; j < (unsigned int) this->nombreArchivo.size(); ++j) {
        this->data.push_back((unsigned char) this->nombreArchivo[j]);
    }
    memcpy(&aux, &tamanioHash, 4);
    for (unsigned int j = 0; j < 4; ++j) {
        this->data.push_back(aux[j]);
    }
    for (unsigned int j = 0; j < (unsigned int) this->hash.size(); ++j) {
        this->data.push_back((unsigned char) this->hash[j]);
    }
    return 0;
}

unsigned int AccionPush::getValorNumerico() {
    return 1;
}

std::string AccionPush::getNombreArchivo() const{
    return this->nombreArchivo;
}

std::vector<unsigned char> AccionPush::getData() const{
    return this->data;
}

int AccionPush::getTamanio(){
    return this->data.size();
}

AccionPush::~AccionPush() {
    this->archivo.close();
//    delete[] data;
}

