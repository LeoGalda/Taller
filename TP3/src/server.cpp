#include <fstream>
#include <iostream>
#include <math.h>
#include <exception>
#include <stdio.h>
#include <string.h>
#include <cstdint>
#include <cstring>
#include <set>
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
        if (socket.isOnError()) {
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
    unsigned char aux[5];
    unsigned int tamanioNombre = (unsigned int) nomArchivo.size();
    memcpy(&aux, &tamanioNombre, 4);
    for (unsigned int j = 0; j < 4; ++j) {
        data.push_back(aux[j]);
        aux[j] = 0;
    }
    for (unsigned int j = 0; j < tamanioNombre; ++j) {
        data.push_back((unsigned char) nomArchivo[j]);
    }
    File file((char *) nomArchivo.c_str(), std::ofstream::in);
    int tamanioArch = file.getTamanioArch();
    Buffer bufTamanio(tamanioArch);
    file.leer((char *) bufTamanio.getData(), tamanioArch);
    memcpy(&aux, &tamanioArch, 4);
    for (unsigned int j = 0; j < 4; ++j) {
        data.push_back(aux[j]);
        aux[j] = 0;
    }
    for (int i = 0; i < tamanioArch; i++) {
        data.push_back(bufTamanio.getDataEnPos(i));
    }
    peerskt->enviarDatos(&data[0], (int) data.size());
    data.clear();
}

int Server::pullea(Socket* peerskt, Indice* indice) {
    int sizeDeUINT = sizeof (unsigned int);
    unsigned int longitudNombreTag[1];
    peerskt->recibirDatos((unsigned char*) longitudNombreTag, sizeDeUINT);
    Buffer bufNombreTag(*longitudNombreTag);
    peerskt->recibirDatos(bufNombreTag.getData(), bufNombreTag.getTamanio());
    unsigned char aux[4];
    std::set<std::string> archivosTaggeados;
    std::vector<unsigned char> data;
    indice->getArchivosTaggeados(&bufNombreTag, archivosTaggeados);
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

    for (std::set<string>::iterator it = archivosTaggeados.begin();
            it != archivosTaggeados.end(); ++it) {
        this->enviarInfoDeTags(peerskt, *it);
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
    unsigned char todoOk = indice->validarVersion(&bufVersion);
    //---------------------------------------------------------
    std::vector<std::string> hashes;    
    Conversor convertidor;
    for (int i = 0; i < (int) *cantidadDeHashes; i++) {
        unsigned int longitudHash[1];
        peerskt->recibirDatos((unsigned char*) longitudHash, sizeDeUINT);
        Buffer bufHash(*longitudHash);
        peerskt->recibirDatos(bufHash.getData(), bufHash.getTamanio());        
        std::string dataHash = convertidor.convertirAString(&bufHash);
        hashes.push_back(dataHash);
        todoOk = todoOk * indice->validarHashExiste(&bufHash);
    }
    if (todoOk) {
        for (size_t w = 0; w < hashes.size(); w++) {
            std::string dataVersion = convertidor.convertirAString(&bufVersion);
            indice->agregar(dataVersion, hashes[w], "t");
        }
    }
    peerskt->enviarDatos(&todoOk, 1);
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

    unsigned char respuesta = indice->validarHashes(&bufNombreArch, &bufHash);
    peerskt->enviarDatos(&respuesta, 1);
    if (!respuesta) return 0;
    //---------------------------------------------------------
    unsigned int longitudArch[1];
    peerskt->recibirDatos((unsigned char*) longitudArch, sizeDeUINT);
    Buffer bufContenidoArch(*longitudArch);
    peerskt->recibirDatos(bufContenidoArch.getData(),
            bufContenidoArch.getTamanio());
    if (*longitudArch < 0) {
        throw -1;
    }
    Conversor convertidor;
    std::string dataHash = convertidor.convertirAString(&bufHash);
    std::string contenido = convertidor.convertirAString(&bufContenidoArch);
    std::string nombreArch = convertidor.convertirAString(&bufNombreArch);
    File file((char *)dataHash.c_str(),std::ofstream::out | std::ofstream::app);    
    file.escribir(contenido);
    indice->agregar(nombreArch,dataHash, "f");
    return 0;
}

Server::~Server() {
}

