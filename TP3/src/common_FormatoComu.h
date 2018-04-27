#ifndef COMMON_FORMATOCOMU_H
#define COMMON_FORMATOCOMU_H

#include <vector>

class FormatoComu {
private:
    std::vector<unsigned int> vectorInt;
public:
    FormatoComu();
    void parsear(const std::vector<unsigned char> vector);
    void mostrar();
    virtual ~FormatoComu();
};

#endif 

