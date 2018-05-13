#ifndef COMMON_CONVERSOR_H
#define COMMON_CONVERSOR_H

#include <string>

#include "common_Buffer.h"


class Conversor {
public:
//constructor del conversor    
    Conversor();
    
// convierte el data de un buffer a un string y lo devuelve   
    std::string convertirAString(Buffer *buffer) const;
    
//destructor del conversor    
    virtual ~Conversor();
private:
};

#endif
