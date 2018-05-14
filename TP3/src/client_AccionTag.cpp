#include "client_AccionTag.h"
#include <iostream>
#include <string.h>
#include <vector>
#include <exception>
#include <stdexcept>

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

//void AccionTag::agregarHash(char *hash) {    
//    std::string sarasa = std::move(hash);
//    std::cout<<"esto a agregar:"<<sarasa<<std::endl;
////    this->hashes.push_back(std::move(sarasa));
//    this->hashes.push_back(std::move(sarasa));
//}
void AccionTag::agregarHash(std::string &hash) {            
//    this->hashes.push_back(std::move(sarasa));
    std::cout<<"esto a agregar:"<<hash<<std::endl;
    this->hashes.push_back(std::move(hash));
}

int AccionTag::getValorNumerico() {
    return 2;
}

void AccionTag::enviar(Socket* socket) {
    int status;
    status = socket->enviarDatos(&this->data[0], this->getTamanio());
    if (status) {
        throw std::runtime_error("Error al enviar los datos\n");        
    }
    std::vector<unsigned char> dataAEnviar;
    std::cout<<this->hashes.size()<<std::endl;
    for (size_t i = 0; i < this->hashes.size(); ++i){
        unsigned char aux[4];
        int cantidadHash = this->hashes[i].size();
        std::cout<<"tamanio del hash: "<<this->hashes[i].size()<<std::endl;
        memcpy(&aux, &cantidadHash, 4);
        for (unsigned int j = 0; j < 4; ++j) {
            dataAEnviar.push_back(aux[j]);
        }
        
//        for (int j = 0; j < cantidadHash; ++j) {            
//        for (int j = 0; j < 4; ++j) {            
            std::cout<<"este hash:" << this->hashes[i] << std::endl;
//            dataAEnviar.push_back((unsigned char) this->hashes[i][j]);
//     c       std::cout<<"si vos"<<std::endl;
//        }
        socket->enviarDatos(&dataAEnviar[0], (int) dataAEnviar.size());
        dataAEnviar.clear();
    }
    std::cout<<"fin enviar"<<std::endl;
}

int AccionTag::getTamanio() {
    return this->data.size();
}

void AccionTag::responder(Socket* socket) {
    unsigned char tipo = 0;
    socket->recibirDatos(&tipo, 1);
    if (!tipo){
        std::cout<<"Error: tag/hash incorrecto."<<std::endl;
    }
}

AccionTag::~AccionTag() {
}

