#include "common_Buffer.h"

Buffer::Buffer() {
}

Buffer::Buffer(int tamanio) : tamanio(tamanio) {    
    this->usado = 0;
    this->data = new unsigned int[tamanio];
}

Buffer::~Buffer() {
    delete[] this->data;
}

