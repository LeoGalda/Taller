#ifndef ACCION_H
#define ACCION_H

#include <string>
#include <vector>

class Accion {
private:
public:
    Accion();
    Accion(const Accion& orig);
    virtual ~Accion();    
    virtual int ejecutar() = 0;
    virtual unsigned int getValorNumerico() = 0;
    virtual int getTamanio() = 0;
    virtual std::vector<unsigned char> getData() = 0;    
    virtual std::string getNombreArchivo() const = 0;
};        
#endif

