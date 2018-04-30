#include "client_AccionPush.h"
#include "common_ExcpError.h"
#include <iostream>
#include <string.h>
#include <arpa/inet.h>

AccionPush::AccionPush(char *arch, char *hash) : hash(hash) {
    this->file = new File(arch,std::ios::in);            
}

int AccionPush::ejecutar() {
    unsigned char aux[4];
    unsigned int tamanioHash = (unsigned int) this->hash.size();
    unsigned int tamanioNombre = (unsigned int) this->file->getTamanioNombre();
    tamanioHash = htonl(tamanioHash);
    tamanioNombre = htonl(tamanioNombre);
    this->data.push_back((unsigned char) this->getValorNumerico());
    memcpy(&aux, &tamanioNombre, 4);
    for (unsigned int j = 0; j < 4; ++j) {
        this->data.push_back(aux[j]);
        aux[j] = 0;
    }
    tamanioNombre = htonl(tamanioNombre);
    std::string nombreArchivo = this->file->getNombreArchivo();
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
    return 0;
}

unsigned int AccionPush::getValorNumerico() {
    return 1;
}

std::vector<unsigned char> AccionPush::getData() {
    return this->data;
}

int AccionPush::getTamanio() {
    return this->data.size();
}

unsigned char* AccionPush::getDataEnPos(int pos) {
    return &this->data[pos];
}

void AccionPush::procesarArch(){
    int tamanio = this->file->getTamanioArch();
    printf("tamanio del archivo: %i", tamanio); 
}

//unsigned char* AccionPush::getArchivo() {
//    return &this->arch[0];
//}

AccionPush::~AccionPush() {
    //    delete[] data;
}

