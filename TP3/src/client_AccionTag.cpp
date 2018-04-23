#include "client_AccionTag.h"
#include <iostream>

AccionTag::AccionTag(char *version) : version(version) {
}

int AccionTag::ejecutar() {
    std::cout << "ejecutando tag" << std::endl;
    for(size_t w = 0; w < this->hashes.size();w++){
        std::cout<<this->hashes[w]<<std::endl;
    }
    return 0;
}

void AccionTag::agregarHash(char *hash){
    this->hashes.push_back(hash);
}

unsigned int AccionTag::getValorNumerico(){
    return 3;
}

AccionTag::~AccionTag() {    
}

