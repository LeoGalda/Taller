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

int Versionador::tagea() {
    Protocolo protocolo(&this->socket);
    int cantidadDeHashes;
    cantidadDeHashes = protocolo.recibirLongitud();
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

