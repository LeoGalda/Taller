#include "client_AccionTag.h"
#include <iostream>
#include <string.h>
#include <vector>
#include <exception>
#include <stdexcept>
#include <algorithm>

AccionTag::AccionTag(char *version) : version(version) {
}

void AccionTag::ejecutar(Protocolo *protocolo) {
    protocolo->enviarComando(this->getValorNumerico());
    protocolo->formatearYEnviarLongitud((int) this->hashes.size());
    protocolo->formatearYEnviarLongitud((int) this->version.size());
    protocolo->enviarData(this->version);
    for (size_t i = 0; i < this->hashes.size(); ++i) {
        protocolo->formatearYEnviarLongitud((int) this->hashes[i].size());
        protocolo->enviarData(this->hashes[i]);
    }
}

void AccionTag::agregarHash(char *hash) {
    this->hashes.push_back(hash);
}

unsigned char AccionTag::getValorNumerico() {
    return 2;
}

void AccionTag::responder(Protocolo *protocolo) {
    unsigned char tipo = protocolo->recibirComando();         
    if (!tipo) {
        std::cout << "Error: tag/hash incorrecto." << std::endl;
    }
}

AccionTag::~AccionTag() {
}

