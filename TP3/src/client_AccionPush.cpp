#include "client_AccionPush.h"
#include "common_ExcpError.h"
#include <iostream>
#include <string.h>
#include <arpa/inet.h>
#include <vector>
#include <string>

#define MAX_TAMANIO_BUFFER 50

AccionPush::AccionPush(char *arch, char *hash) : hash(hash),
file(arch, std::ios::in) {
}

void AccionPush::ejecutar() {
    unsigned char aux[4];
    unsigned int tamanioHash = (unsigned int) this->hash.size();
    unsigned int tamanioNombre = (unsigned int) this->file.getTamanioNombre();
    this->data.push_back((unsigned char) this->getValorNumerico());
    memcpy(&aux, &tamanioNombre, 4);
    for (unsigned int j = 0; j < 4; ++j) {
        this->data.push_back(aux[j]);
        aux[j] = 0;
    }
    std::string nombreArchivo = this->file.getNombreArchivo();
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
}

void AccionPush::enviar(Socket *socket) {
    int status;
    status = socket->enviarDatos(&this->data[0], this->getTamanio());
    if (status) {
        printf("Error al enviar los datos\n");
        throw -1;
    }
}

int AccionPush::enviarDataDeArchivo(Socket *socket, int tamanio) {
    int bytesAEnviar = 0;
    if (tamanio < MAX_TAMANIO_BUFFER) {
        bytesAEnviar = tamanio;
    } else {
        bytesAEnviar = MAX_TAMANIO_BUFFER;
    }
    if (bytesAEnviar > 0) {
        Buffer buffer(bytesAEnviar);
        this->file.leer((char *) buffer.getData(), bytesAEnviar);
        
        socket->enviarDatos(buffer.getData(), bytesAEnviar);        
    }
    return bytesAEnviar;
}

void AccionPush::responder(Socket* socket) {
    int status;
    unsigned char tipo = 0;
    status = socket->recibirDatos(&tipo, 1);
    if (status && tipo == 1) {
        int tamanioArch = this->getSizeFile();
        unsigned char envio[4];
        memcpy(&envio, &tamanioArch, sizeof(tamanioArch));
        status = socket->enviarDatos(&envio[0], 4);
        int cantDeBytesDelArchivoEnviado = 0;
        int tamanio = tamanioArch;
        while (cantDeBytesDelArchivoEnviado < tamanioArch) {
            int enviados = this->enviarDataDeArchivo(socket,tamanio);
            cantDeBytesDelArchivoEnviado += enviados;
            tamanio -= enviados;                    
        }
    } else {
    }
}

int AccionPush::getValorNumerico() {
    return 1;
}

int AccionPush::getTamanio() {
    return this->data.size();
}

int AccionPush::getSizeFile() {
    return this->file.getTamanioArch();
}

AccionPush::~AccionPush() {
}

