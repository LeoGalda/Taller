#include "client_AccionPull.h"
#include <iostream>

AccionPull::AccionPull(char *hash) : hash(hash) {
}

int AccionPull::ejecutar(){
    std::cout<<"ejecutando puuuuull"<<std::endl;
    return 0;
}

unsigned int AccionPull::getValorNumerico(){
    return 2;
}

AccionPull::~AccionPull() {
}

