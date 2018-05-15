#include "client_AccionPush.h"
#include <iostream>
#include <string.h>
#include <arpa/inet.h>
#include <vector>
#include <string>

#define MAX_TAMANIO_BUFFER 50

AccionPush::AccionPush(char *arch, char *hash) : hash(hash),
                                        file(arch, std::ios::in) {
}

void AccionPush::ejecutar(Protocolo *protocolo) {
    protocolo->enviarComando(this->getValorNumerico());
    std::string nombreArchivo = this->file.getNombreArchivo();  
    protocolo->formatearYEnviarLongitud((int)nombreArchivo.size());
    protocolo->enviarData(nombreArchivo);
    protocolo->formatearYEnviarLongitud((int)this->hash.size());
    protocolo->enviarData(this->hash);    
}

void AccionPush::enviar(Protocolo *protocolo) {
}

int AccionPush::enviarDataDeArchivo(Protocolo *protocolo, int tamanio) {
    int bytesAEnviar = 0;
    if (tamanio < MAX_TAMANIO_BUFFER) {
        bytesAEnviar = tamanio;
    } else {
        bytesAEnviar = MAX_TAMANIO_BUFFER;
    }
    if (bytesAEnviar > 0) {
        Buffer buffer(bytesAEnviar);
        this->file.leer((char *) buffer.getData(), bytesAEnviar);
        std::string data;
        data = protocolo->convertirAString(&buffer);
        protocolo->enviarData(data);      
    }
    return bytesAEnviar;
}

void AccionPush::responder(Protocolo* protocolo) {
    unsigned char tipo = protocolo->recibirComando();
    if (tipo == 1) {
        int tamanioArch = this->getSizeFile();
        protocolo->formatearYEnviarLongitud(tamanioArch);                
        int cantDeBytesDelArchivoEnviado = 0;
        int tamanio = tamanioArch;
        while (cantDeBytesDelArchivoEnviado < tamanioArch) {
            int enviados = this->enviarDataDeArchivo(protocolo,tamanio);
            cantDeBytesDelArchivoEnviado += enviados;
            tamanio -= enviados;                    
        }
    }
}

unsigned char AccionPush::getValorNumerico() {
    return 1;
}


int AccionPush::getSizeFile() {
    return this->file.getTamanioArch();
}

AccionPush::~AccionPush() {
}

