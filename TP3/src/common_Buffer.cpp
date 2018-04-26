#include "common_Buffer.h"

Buffer::Buffer(int tamanio) : tamanio(tamanio) {    
    this->usado = 0;
    this->data = new unsigned int[tamanio];
}

void Buffer::setUsado(int usado){
    this->usado = usado;
}

int Buffer::getUsado() {
    return this->usado;
}

unsigned int* Buffer::getData() {
    return this->data;
}

int Buffer::setDataEnPosicion(unsigned int data, int pos) {   
    this->data[pos] = data;
    return 0;
}

int Buffer::buffer_get_tamanio(){
    return this->tamanio;
}

unsigned char Buffer::getDataEnPos(int pos) {
    if (pos > this->tamanio) return 1;
    return this->data[pos];
}


Buffer::~Buffer() {
    delete[] this->data;
}

