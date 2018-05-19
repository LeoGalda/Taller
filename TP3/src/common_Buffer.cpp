#include <algorithm>

#include "common_Buffer.h"
#include <exception>
#include <stdexcept>


Buffer::Buffer(unsigned int tamanio) : tamanio(tamanio) {
    this->data = new unsigned char[tamanio];
    if (this->data == NULL) {
        throw std::runtime_error("error al crear el buffer");
    }
}

unsigned char* Buffer::getData() {
    return this->data;
}

int Buffer::getTamanio() {
    return this->tamanio;
}

unsigned char Buffer::getDataEnPos(int pos) {
    if (pos < 0 || pos > this->tamanio) {
        throw std::runtime_error("quiere acceder a una posicion invalida\n");
    }
    return std::move(this->data[pos]);
}

Buffer::~Buffer() {
    delete[] this->data;
}

