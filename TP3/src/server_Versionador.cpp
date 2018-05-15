#include <fstream>
#include <iostream>
#include <math.h>
#include <exception>
#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>
#include <cstdint>
#include <cstring>
#include <set>
#include "common_File.h"
#include "server_Versionador.h"
#include "common_Protocolo.h"

#define MAX_TAMANIO_BUFFER 50

Versionador::Versionador(Socket &socket, Indice *indice) :
socket(std::move(socket)), indice(std::move(indice)) {
}

void Versionador::run() {
    unsigned char tipo = 0;
    int corriendo;
    corriendo = this->socket.recibirDatos(&tipo, 1);
    if (!corriendo) {
        return;
    }
    if (tipo == 1) {
        corriendo = this->pushea();
    } else if (tipo == 2) {
        corriendo = this->tagea();
    } else if (tipo == 3) {
        corriendo = this->pullea();
    } else {
        throw std::runtime_error("tipo erroneo");
    }
}

int Versionador::enviarDataDeArchivo(int tamanio, File *file,
                                      Protocolo *protocolo) {
    int bytesAEnviar = 0;
    if (tamanio < MAX_TAMANIO_BUFFER) {
        bytesAEnviar = tamanio;
    } else {
        bytesAEnviar = MAX_TAMANIO_BUFFER;
    }
    if (bytesAEnviar > 0) {
        Buffer buffer(bytesAEnviar);
        file->leer((char *) buffer.getData(), bytesAEnviar);
        std::string data;
        data = protocolo->convertirAString(&buffer);
        protocolo->enviarData(data);      
    }
    return bytesAEnviar;
}

void Versionador::enviarInfoDeTags(const std::string nomArchivo,
                                    Protocolo *protocolo) {
    protocolo->formatearYEnviarLongitud((int)nomArchivo.size());
    std::string nombre = nomArchivo;
    protocolo->enviarData(nombre);
    File file((char *) nomArchivo.c_str(), std::ofstream::in);    
    int tamanioArch = file.getTamanioArch();
    protocolo->formatearYEnviarLongitud(tamanioArch);
    
    int cantDeBytesDelArchivoEnviado = 0;
    int tamanio = tamanioArch;
    while (cantDeBytesDelArchivoEnviado < tamanioArch) {
        int enviados = this->enviarDataDeArchivo(tamanio, &file,protocolo);
        cantDeBytesDelArchivoEnviado += enviados;
        tamanio -= enviados;
    }
}
//void Versionador::enviarInfoDeTags(const std::string nomArchivo,
//                                    Protocolo *protocolo) {    
//    std::vector<unsigned char> data;
//    unsigned char aux[5];
//    unsigned int tamanioNombre = (unsigned int) nomArchivo.size();
//    memcpy(&aux, &tamanioNombre, 4);
//    for (unsigned int j = 0; j < 4; ++j) {
//        data.push_back(aux[j]);
//        aux[j] = 0;
//    }
//    for (unsigned int j = 0; j < tamanioNombre; ++j) {
//        data.push_back((unsigned char) nomArchivo[j]);
//    }
//    File file((char *) nomArchivo.c_str(), std::ofstream::in);
//    int tamanioArch = file.getTamanioArch();
//    memcpy(&aux, &tamanioArch, 4);
//    for (unsigned int j = 0; j < 4; ++j) {
//        data.push_back(aux[j]);
//        aux[j] = 0;
//    }
//    this->socket.enviarDatos(&data[0], (int) data.size());
//    data.clear();
//    int cantDeBytesDelArchivoEnviado = 0;
//    int tamanio = tamanioArch;
//    while (cantDeBytesDelArchivoEnviado < tamanioArch) {
//        int enviados = this->enviarDataDeArchivo(tamanio, &file);
//        cantDeBytesDelArchivoEnviado += enviados;
//        tamanio -= enviados;
//    }
//}

int Versionador::pullea() {
    Protocolo protocolo(&this->socket);
    std::string nombreTag = protocolo.recibirYFormatear();
    std::set<std::string> archivosTaggeados;
    this->indice->getArchivosTaggeados(nombreTag, archivosTaggeados);
    unsigned char todoOk = 0;
    if (archivosTaggeados.empty()) {
        protocolo.enviarComando(todoOk);
    } else {
        todoOk = 1;
        protocolo.enviarComando(todoOk);
        protocolo.formatearYEnviarLongitud((int)archivosTaggeados.size());
        for (std::set<string>::iterator it = archivosTaggeados.begin();
                it != archivosTaggeados.end(); ++it) {
            this->enviarInfoDeTags(*it,&protocolo);
        }
    }
    return 0;
}
//int Versionador::pullea() {
//    int sizeDeUINT = sizeof (unsigned int);
//    unsigned int longitudNombreTag[1];
//    this->socket.recibirDatos((unsigned char*) longitudNombreTag, sizeDeUINT);
//    Buffer bufNombreTag(*longitudNombreTag);
//    this->socket.recibirDatos(bufNombreTag.getData(),
//            bufNombreTag.getTamanio());
//    unsigned char aux[4];
//    std::set<std::string> archivosTaggeados;
//    std::vector<unsigned char> data;
//    this->indice->getArchivosTaggeados(&bufNombreTag, archivosTaggeados);
//    unsigned char todoOk;
//    if (archivosTaggeados.empty()) {
//        todoOk = 0;
//        this->socket.enviarDatos(&todoOk, 1);
//        return 0;
//    }
//    todoOk = 1;
//    this->socket.enviarDatos(&todoOk, 1);
//    unsigned int tamanioHash = (unsigned int) archivosTaggeados.size();
//    memcpy(&aux, &tamanioHash, 4);
//    for (unsigned int j = 0; j < 4; ++j) {
//        data.push_back(aux[j]);
//    }
//    data.clear();
//    this->socket.enviarDatos(&data[0], 4);
//
//    for (std::set<string>::iterator it = archivosTaggeados.begin();
//            it != archivosTaggeados.end(); ++it) {
//        this->enviarInfoDeTags(*it);
//    }
//    return 0;
//}

int Versionador::tagea() {
    Protocolo protocolo(&this->socket);
    int cantidadDeHashes;
    cantidadDeHashes = (int) protocolo.recibirComando();
    std::string version = protocolo.recibirYFormatear();
    unsigned char todoOk = this->indice->validarVersion(version);
    std::vector<std::string> hashes;
    if (todoOk) {
        for (int i = 0; i < cantidadDeHashes; i++) {
            std::string dataHash = protocolo.recibirYFormatear();
            hashes.push_back(dataHash);
            todoOk = todoOk * this->indice->validarHashExiste(dataHash);
        }
        if (todoOk) {
            for (size_t w = 0; w < hashes.size(); w++) {
                this->indice->agregar(version, hashes[w], "t");
            }
        }
    }
    protocolo.enviarComando(todoOk);
    return 0;
}
//int Versionador::tagea() {
//    int sizeDeUINT = sizeof(unsigned int);
//    unsigned int cantidadDeHashes[1];
//    this->socket.recibirDatos((unsigned char*) cantidadDeHashes, sizeDeUINT);
//    //----------------------------------------------------------    
//    unsigned int longitudVersion[1];
//    this->socket.recibirDatos((unsigned char*) longitudVersion, sizeDeUINT);
//    Buffer bufVersion(*longitudVersion);
//    this->socket.recibirDatos(bufVersion.getData(), bufVersion.getTamanio());
//    unsigned char todoOk = this->indice->validarVersion(&bufVersion);
//    //---------------------------------------------------------
//    std::vector<std::string> hashes;
//    Conversor convertidor;
//    for (int i = 0; i < (int) *cantidadDeHashes; i++) {
//        unsigned int longitudHash[1];
//        this->socket.recibirDatos((unsigned char*) longitudHash, sizeDeUINT);
//        Buffer bufHash(*longitudHash);
//        this->socket.recibirDatos(bufHash.getData(), bufHash.getTamanio());
//        std::string dataHash = convertidor.convertirAString(&bufHash);
//        hashes.push_back(dataHash);
//        todoOk = todoOk * this->indice->validarHashExiste(&bufHash);
//    }
//    if (todoOk) {
//        for (size_t w = 0; w < hashes.size(); w++) {
//            std::string dataVersion = convertidor.convertirAString(&bufVersion);
//            this->indice->agregar(dataVersion, hashes[w], "t");
//        }
//    }
//    this->socket.enviarDatos(&todoOk, 1);
//    return 0;
//}

int Versionador::pushea() {
    Protocolo protocolo(&this->socket);
    std::string nombreArch = protocolo.recibirYFormatear();
    std::string dataHash = protocolo.recibirYFormatear();
    unsigned char respuesta = this->indice->validarHashes(nombreArch, dataHash);
    protocolo.enviarComando(respuesta);
    if (!respuesta) return 0;
    std::string contenido = protocolo.recibirYFormatear();
    File file((char *) dataHash.c_str(),
            std::ofstream::out | std::ofstream::app);
    file << contenido;
    this->indice->agregar(nombreArch, dataHash, "f");
    return 0;
}

Versionador::~Versionador() {
}

