#ifndef COMMON_FORMATOCOMU_H
#define COMMON_FORMATOCOMU_H

#include <vector>

class FormatoComu {
private:
    std::vector<unsigned int> vectorInt;
    unsigned int dataLongitud;
public:
    FormatoComu();
    void parsear(std::vector<unsigned char> vec);
    void mostrar();
    int getTamanio();
    unsigned int getDataLongitud();
    unsigned int* getDataEnPos(int pos);    
    virtual ~FormatoComu();
};

#endif 

