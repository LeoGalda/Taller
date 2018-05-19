#ifndef COMMON_ACCION_H
#define COMMON_ACCION_H

#include <string>
#include <vector>
#include "common_Socket.h"
#include "common_Protocolo.h"

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
    virtual void ejecutar(Protocolo *protocolo) = 0;    
    
//llama al responder de la clase hija que corresponda    
    virtual void responder(Protocolo *protocolo) = 0;

//devuelve el valor numerico de la clase hija que corresponda    
    virtual unsigned char getValorNumerico() = 0;
};        
#endif

