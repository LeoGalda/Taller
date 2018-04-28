#include <algorithm>
#include <vector>
#include <cstring>

#include "common_FormatoComu.h"

FormatoComu::FormatoComu() {
}

void FormatoComu::parsear(std::vector<unsigned char> vector) {
    this->vectorInt.clear();
    std::copy(vector.begin(), vector.end(), std::back_inserter(this->vectorInt));
}

int FormatoComu::getTamanio(){
    return this->vectorInt.size();
}

unsigned int* FormatoComu::getDataEnPos(int pos){
    return &this->vectorInt[pos];
}

//void FormatoComu::mostrar() {
//    printf("MOSTRAR:\n");
//    for (size_t j = 0; j < this->vectorInt.size(); j++) {
//        printf("%i-", this->vectorInt[j]);
//    }
//}

FormatoComu::~FormatoComu() {
}