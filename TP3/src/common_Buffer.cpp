#include <algorithm>

#include "common_Buffer.h"

Buffer::Buffer(int tamanio) : tamanio(tamanio) {        
    this->data = new unsigned char[tamanio];
}

unsigned char* Buffer::getData() {
    return this->data;
}

int Buffer::getTamanio(){
    return this->tamanio;
}

unsigned char Buffer::getDataEnPos(int pos){
    if(pos < 0 || pos > this->tamanio)
        throw -1;
    return std::move(this->data[pos]);
}
//
//unsigned char* Buffer::getMoveData() const{    
//    return std::move(this->data);
//}


Buffer::~Buffer() {
    delete[] this->data;
}

