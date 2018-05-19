#include "client_AccionPull.h"
#include "common_File.h"
#include <iostream>
#include <string.h>
#include <string>


AccionPull::AccionPull(char *hash) : hash(hash) {
}

void AccionPull::ejecutar(Protocolo *protocolo) {
    protocolo->enviarComando(this->getValorNumerico());
    protocolo->formatearYEnviarLongitud((int)this->hash.size());
    protocolo->enviarData(this->hash);
}

void AccionPull::crearArchivosPull(Protocolo *protocolo) {
    std::string nombre = protocolo->recibirYFormatear();               
    nombre += "." + this->hash;        
    File file((char *)nombre.c_str(), std::ofstream::out | std::ofstream::app);
    std::string dataEscribir = protocolo->recibirYFormatear();
    file << dataEscribir;
}

void AccionPull::responder(Protocolo *protocolo) {    
    unsigned char tipo = protocolo->recibirComando();         
    if (tipo == 1) {
        int cantidadDeArchivos = protocolo->recibirLongitud();
        for (int i = 0; i < cantidadDeArchivos; i++) {
            this->crearArchivosPull(protocolo);
        }
    } else {
        std::cout<<"Error: tag/hash incorrecto."<<std::endl;
    }
}

unsigned char AccionPull::getValorNumerico() {
    return 3;
}

AccionPull::~AccionPull() {
}

