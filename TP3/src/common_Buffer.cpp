#include "common_Buffer.h"

Buffer::Buffer(int tamanio) : tamanio(tamanio) {    
    this->usado = 0;
    this->data = new unsigned int[tamanio];
}

Buffer::setData(){
    
}

Buffer::setUsado(int usado){
    this->usado = usado;
}

Buffer::~Buffer() {
    delete[] this->data;
}

