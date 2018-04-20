#ifndef ACCION_H
#define ACCION_H

class Accion {
private:
public:
    Accion();
    Accion(const Accion& orig);
    virtual ~Accion();    
    virtual void ejecutar() = 0;
    virtual int getValorNumerico() = 0;
};

#endif /* ACCION_H */

