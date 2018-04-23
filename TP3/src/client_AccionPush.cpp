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
    this->data = new unsigned char[64];
}

int AccionPush::ejecutar() {
    unsigned char aux[4];
    unsigned int tamanioHash = (unsigned int) this->hash.size();
    unsigned int tamanioNombre = (unsigned int) this->nombreArchivo.size();
    if (!this->getEndiannes()) {
        tamanioHash = htonl(tamanioHash);
        tamanioNombre = htonl(tamanioNombre);
    }
    int cantidad = 0;
    data[cantidad] = (unsigned char) this->getValorNumerico();

    memcpy(&aux, &tamanioNombre, 4);
    for (unsigned int j = 0; j < 4; ++j) {
        cantidad++;
        data[cantidad] = aux[j];
        aux[j] = 0;
    }
    for (unsigned int j = 0; j < (unsigned int) this->nombreArchivo.size(); ++j) {
        cantidad++;
        data[cantidad] = (unsigned char) this->nombreArchivo[j];
    }
    memcpy(&aux, &tamanioHash, 4);
    for (unsigned int j = 0; j < 4; ++j) {
        cantidad++;
        data[cantidad] = aux[j];
    }
    for (unsigned int j = 0; j < (unsigned int) this->hash.size(); ++j) {
        cantidad++;
        data[cantidad] = (unsigned char) this->hash[j];
    }
    return cantidad;
}

unsigned int AccionPush::getValorNumerico() {
    return 1;
}

AccionPush::~AccionPush() {
    this->archivo.close();
    delete[] data;
}

