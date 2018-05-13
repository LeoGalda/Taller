#ifndef COMMON_ACCION_H
#define COMMON_ACCION_H

#include <string>
#include <vector>
#include "common_Socket.h"

class Accion {
private:
public:
//constructor del Accion    
    Accion();

//constructor del Accion    
    Accion(const Accion& orig);
    
//destructor del Accion    
    virtual ~Accion();    

//llama al ejecutar de la clase hija que corresponda
    virtual void ejecutar() = 0;
    
//llama al enviar de la clase hija que corresponda
    virtual void enviar(Socket *socket) = 0;
    
//llama al responder de la clase hija que corresponda    
    virtual void responder(Socket *socket) = 0;

//devuelve el valor numerico de la clase hija que corresponda    
    virtual int getValorNumerico() = 0;
};        
#endif

