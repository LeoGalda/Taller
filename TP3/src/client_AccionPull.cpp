#include "client_AccionPull.h"
#include "common_File.h"
#include <iostream>
#include <string.h>
#include <string>
#include "common_Conversor.h"

AccionPull::AccionPull(char *hash) : hash(hash) {
}

void AccionPull::ejecutar() {
    unsigned char aux[5];
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


void AccionPull::crearArchivosPull(Socket* socket) {
    int sizeDeUINT = sizeof(unsigned int);
    Conversor convertidor;
    unsigned int tamanioNombreArch[1];
    socket->recibirDatos((unsigned char*) tamanioNombreArch, sizeDeUINT);
    Buffer bufNombreArch(*tamanioNombreArch);
    socket->recibirDatos(bufNombreArch.getData(), bufNombreArch.getTamanio());
     std::string nombre = convertidor.convertirAString(&bufNombreArch);    
    nombre += "." + this->hash;    
    File file((char *)nombre.c_str(), std::ofstream::out | std::ofstream::app);
    unsigned int tamanioContenidoArch[1];
    socket->recibirDatos((unsigned char*) tamanioContenidoArch, sizeDeUINT);
    unsigned int ver = *tamanioContenidoArch;    
    Buffer bufContenidoArch(ver);
    socket->recibirDatos(bufContenidoArch.getData(), 
                         bufContenidoArch.getTamanio());
    std::string dataEscribir = convertidor.convertirAString(&bufContenidoArch);
    file << dataEscribir;
//    file.escribir(dataEscribir);    
}

void AccionPull::responder(Socket* socket) {    
    unsigned char tipo = 0;    
    socket->recibirDatos(&tipo, 1);    
    if (tipo == 1) {
        int sizeDeUINT = sizeof(unsigned int);
        unsigned int cantidadDeArchivos[1];
        socket->recibirDatos((unsigned char*) cantidadDeArchivos, sizeDeUINT);
        for (int i = 0; i < (int) *cantidadDeArchivos; i++) {
            this->crearArchivosPull(socket);
        }
    } else {
        std::cout<<"Error: tag/hash incorrecto."<<std::endl;
    }
}

int AccionPull::getTamanio() {
    return this->data.size();
}


int AccionPull::getValorNumerico() {
    return 3;
}

AccionPull::~AccionPull() {
}

