#ifndef ACCION_H
#define ACCION_H

class Accion {
private:
public:
    Accion();
    Accion(const Accion& orig);
    virtual ~Accion();    
    virtual int ejecutar() = 0;
    virtual unsigned int getValorNumerico() = 0;
protected:
        bool getEndiannes();
};        
#endif

