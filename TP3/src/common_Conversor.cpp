#include "common_Conversor.h"
#include <string>

Conversor::Conversor() {
}

std::string Conversor::convertirAString(Buffer* buffer) const{
    std::string dataString(buffer->getData(),buffer->getData() + 
            buffer->getTamanio()/
            sizeof(buffer->getDataEnPos(0)));
    return dataString;
}

Conversor::~Conversor() {
}
