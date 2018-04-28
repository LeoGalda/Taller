#ifndef COMMON_FORMATOCOMU_H
#define COMMON_FORMATOCOMU_H

#include <vector>

class FormatoComu {
private:
    std::vector<unsigned int> vectorInt;
public:
    FormatoComu();
    void parsear(std::vector<unsigned char> vector);
    void mostrar();
    int getTamanio();
    unsigned int* getDataEnPos(int pos);
    virtual ~FormatoComu();
};

#endif 

