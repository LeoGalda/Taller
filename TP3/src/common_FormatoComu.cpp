#include <algorithm>
#include <vector>

#include "common_FormatoComu.h"

FormatoComu::FormatoComu() {
}


void FormatoComu::parsear(const std::vector<unsigned char> vector){ 
    this->vectorInt.clear();
    std::copy(vector.begin(),vector.end(),this->vectorInt.begin());
}

void FormatoComu::mostrar(){
    printf("MOSTRAR:\n");
    for(size_t j = 0; j < this->vectorInt.size(); j++){
        printf("%02x-",this->vectorInt[j]);
    }    
}

FormatoComu::~FormatoComu() {
}