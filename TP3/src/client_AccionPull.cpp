#include "client_AccionPull.h"
#include "common_File.h"
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


void AccionPull::crearArchivosPull(Socket* socket) {
    int sizeDeUINT = sizeof (unsigned int);
    unsigned int tamanioNombreArch[1];
    socket->recibirDatos((unsigned char*) tamanioNombreArch, sizeDeUINT);
    Buffer bufNombreArch(*tamanioNombreArch);
    socket->recibirDatos(bufNombreArch.getData(), bufNombreArch.getTamanio());
    std::string nombre = (char *) bufNombreArch.getData() + this->hash; 
    File file((char *)nombre.c_str(), std::ofstream::out | std::ofstream::app);
    unsigned int tamanioContenidoArch[1];
    socket->recibirDatos((unsigned char*) tamanioContenidoArch, sizeDeUINT);
    Buffer bufContenidoArch(*tamanioContenidoArch);
    socket->recibirDatos(bufContenidoArch.getData(), bufContenidoArch.getTamanio());
    file.escribir(bufContenidoArch.getData());    
}

void AccionPull::responder(Socket* socket) {    
    unsigned char tipo = 0;
    int status;
    status = socket->recibirDatos(&tipo, 1);
    if (status && tipo == 1) {
        int sizeDeUINT = sizeof (unsigned int);
        unsigned int cantidadDeArchivos[1];
        socket->recibirDatos((unsigned char*) cantidadDeArchivos, sizeDeUINT);
        for (int i = 0; i < (int) *cantidadDeArchivos; i++) {
            this->crearArchivosPull(socket);
        }
    } else {
        printf("algo mal al recibir la data de responder");
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

