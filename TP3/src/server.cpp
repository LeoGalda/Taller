#include <fstream>
#include <iostream>
#include <math.h>
#include <exception>
#include <stdio.h>
#include <string.h>
#include <cstdint>
#include <cstring>
#include "server.h"
#include "common_ExcpError.h"
#include "common_File.h"

Server::Server(char *puerto) {
    this->socket.doBind(puerto);
    this->socket.doListen();
}

void Server::aceptarClientes(Indice *indice) {
    Socket peerskt;
    this->socket.aceptar(&peerskt);
    int corriendo = 1;
    while (corriendo) {
        if (this->socket.getFD() == -1) {
            printf("Error en socket\n");
            corriendo = 0;
        } else {
            unsigned char tipo = 0;
            corriendo = peerskt.recibirDatos(&tipo, 1);
            if (!corriendo) {
                std::cout << "error al recibir dato " << std::endl;
                return;
            }
            if (tipo == 1) {
                corriendo = this->pushea(&peerskt, indice);
            } else if (tipo == 2) {
                corriendo = this->tagea(&peerskt, indice);
            } else if (tipo == 3) {
            } else {
                std::cout << "tipo errorneo" << std::endl;
            }
        }
    }
}

int Server::tagea(Socket* peerskt, Indice* indice) {
    int sizeDeUINT = sizeof (unsigned int);
    unsigned int cantidadDeHashes[1];
    peerskt->recibirDatos((unsigned char*) cantidadDeHashes, sizeDeUINT);
    //----------------------------------------------------------    
    unsigned int longitudVersion[1];
    peerskt->recibirDatos((unsigned char*) longitudVersion, sizeDeUINT);
    Buffer bufVersion(*longitudVersion);
    peerskt->recibirDatos(bufVersion.getData(), bufVersion.getTamanio());
    //---------------------------------------------------------
    std::vector<std::string> hashes;
    for (int i = 0; i < (int) *cantidadDeHashes; i++) {
        unsigned int longitudHash[1];
        peerskt->recibirDatos((unsigned char*) longitudHash, sizeDeUINT);
        Buffer bufHash(*longitudHash);
        peerskt->recibirDatos(bufHash.getData(),bufHash.getTamanio());
        hashes.push_back((char *)bufHash.getData());
    }
    for(size_t w = 0; w < hashes.size(); w++){
        std::cout<< hashes[w] <<std::endl;
        indice->agregar((char *) bufVersion.getData(),hashes[w],"t");
    }
    return 0;
}

int Server::pushea(Socket *peerskt, Indice *indice) {
    int sizeDeUINT = sizeof (unsigned int);
    unsigned int longitudNomArch[1];
    peerskt->recibirDatos((unsigned char*) longitudNomArch, sizeDeUINT);
    if (*longitudNomArch < 0) {
        throw -1;
    }
    Buffer bufNombreArch(*longitudNomArch);
    peerskt->recibirDatos(bufNombreArch.getData(), bufNombreArch.getTamanio());
    //----------------------------------------------------------    
    unsigned int longitudHash[1];
    peerskt->recibirDatos((unsigned char*) longitudHash, sizeDeUINT);
    if (*longitudHash < 0) {
        throw -1;
    }
    Buffer bufHash(*longitudHash);
    peerskt->recibirDatos(bufHash.getData(), bufHash.getTamanio());

    unsigned char respuesta = 1;
    peerskt->enviarDatos(&respuesta, 1);
    //---------------------------------------------------------
    unsigned int longitudArch[1];
    peerskt->recibirDatos((unsigned char*) longitudArch, sizeDeUINT);
    Buffer bufContenidoArch(*longitudArch);
    peerskt->recibirDatos(bufContenidoArch.getData(),
            bufContenidoArch.getTamanio());
    if (*longitudArch < 0) {
        throw -1;
    }
    // en esta parte al usar  los buffer valgrind me da error y
    // no puedo solucionarlo  
    File file((char *) bufHash.getData(),
            std::ofstream::out | std::ofstream::app);
    file.escribir(bufContenidoArch.getData());
    indice->agregar((char *) bufNombreArch.getData(),
            (char *) bufHash.getData(),"f");
    return 0;
}

Server::~Server() {
}

