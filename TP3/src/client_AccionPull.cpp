#include "client_AccionPull.h"
#include <iostream>

AccionPull::AccionPull(char *hash) : hash(hash) {
}

void AccionPull::ejecutar(){
    std::cout<<"ejecutando puuuuull"<<std::endl;
}

int AccionPull::getValorNumerico(){
    return 2;
}

AccionPull::~AccionPull() {
}

