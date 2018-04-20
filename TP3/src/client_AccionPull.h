#ifndef ACCIONPULL_H
#define ACCIONPULL_H

#include "client_Accion.h"
#include <string>

class AccionPull : public Accion {
private:    
    std::string hash;
public:
    AccionPull(char *hash);
    void ejecutar();
    int getValorNumerico();
    virtual ~AccionPull();
};

#endif 

