#include "client_AccionTag.h"
#include <iostream>

AccionTag::AccionTag(char *version) : version(version) {
}

void AccionTag::ejecutar() {
    std::cout << "ejecutando tag" << std::endl;
    for(size_t w = 0; w < this->hashes.size();w++){
        std::cout<<this->hashes[w]<<std::endl;
    }
}

void AccionTag::agregarHash(char *hash){
    this->hashes.push_back(hash);
}

int AccionTag::getValorNumerico(){
    return 3;
}

AccionTag::~AccionTag() {    
}

