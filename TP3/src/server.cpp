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
                corriendo = this->pullea(&peerskt, indice);
            } else {
                std::cout << "tipo erroneo" << std::endl;
            }
        }
    }
}

void Server::enviarInfoDeTags(Socket *peerskt, std::string nomArchivo) {
    std::vector<unsigned char> data;
    unsigned char aux[4];
    unsigned int tamanioNombre = (unsigned int) nomArchivo.size();
    memcpy(&aux, &tamanioNombre, 4);
    for (unsigned int j = 0; j < 4; ++j) {
        data.push_back(aux[j]);
        aux[j] = 0;
    }
    for (unsigned int j = 0; j < tamanioNombre; ++j) {
        data.push_back((unsigned char) nomArchivo[j]);
    }
    File file((char *)nomArchivo.c_str(), std::ofstream::in);
    int tamanioArch = file.getTamanioArch();
    Buffer bufTamanio(tamanioArch);
    file.leer((char *) bufTamanio.getData(), tamanioArch);
    memcpy(&aux, &tamanioArch, 4);
    for (unsigned int j = 0; j < 4; ++j) {
        data.push_back(aux[j]);
        aux[j] = 0;
    }
    for (int i = 0;i < tamanioArch;i++){
        data.push_back(bufTamanio.getDataEnPos(i));
    }
    peerskt->enviarDatos(&data[0],(int) data.size());
    data.clear();
}

int Server::pullea(Socket* peerskt, Indice* indice) {
    int sizeDeUINT = sizeof (unsigned int);
    unsigned int longitudNombreTag[1];
    peerskt->recibirDatos((unsigned char*) longitudNombreTag, sizeDeUINT);
    Buffer bufNombreTag(*longitudNombreTag);
    peerskt->recibirDatos(bufNombreTag.getData(), bufNombreTag.getTamanio());
    unsigned char aux[4];
    std::vector<std::string> archivosTaggeados;
    std::vector<unsigned char> data;
    indice->getArchivosTaggeados(bufNombreTag.getData(), archivosTaggeados);
    unsigned char todoOk;
    if (archivosTaggeados.empty()) {
        todoOk = 0;
        peerskt->enviarDatos(&todoOk, 1);
        return 0;
    }
    todoOk = 1;

    peerskt->enviarDatos(&todoOk, 1);
    unsigned int tamanioHash = (unsigned int) archivosTaggeados.size();
    memcpy(&aux, &tamanioHash, 4);
    for (unsigned int j = 0; j < 4; ++j) {
        data.push_back(aux[j]);
    }
    data.clear();
    peerskt->enviarDatos(&data[0], 4);
    for (size_t i = 0; i < archivosTaggeados.size(); ++i) {
        this->enviarInfoDeTags(peerskt, archivosTaggeados[i]);
    }
    return 0;
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
        peerskt->recibirDatos(bufHash.getData(), bufHash.getTamanio());
        hashes.push_back((char *) bufHash.getData());
    }
    for (size_t w = 0; w < hashes.size(); w++) {
        std::cout << hashes[w] << std::endl;
        indice->agregar((char *) bufVersion.getData(), hashes[w], "t");
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
            (char *) bufHash.getData(), "f");
    return 0;
}

Server::~Server() {
}

