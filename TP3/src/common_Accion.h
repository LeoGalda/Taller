#ifndef COMMON_ACCION_H
#define COMMON_ACCION_H

#include <string>
#include <vector>
#include "common_Socket.h"

class Accion {
private:
public:
    Accion();
    Accion(const Accion& orig);
    virtual ~Accion();    
    virtual void ejecutar() = 0;
    virtual void enviar(Socket *socket) = 0;
    virtual void responder(Socket *socket) = 0;
    virtual int getValorNumerico() = 0;
};        
#endif

