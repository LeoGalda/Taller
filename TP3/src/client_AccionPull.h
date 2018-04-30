#ifndef CLIENT_ACCIONPULL_H
#define CLIENT_ACCIONPULL_H

#include "client_Accion.h"
#include <string>

//class AccionPull : public Accion {
class AccionPull{
private:    
    std::string hash;
public:
    AccionPull(char *hash);
    int ejecutar();
    unsigned int getValorNumerico();
    int getTamanio();
    virtual ~AccionPull();
    std::string getNombreArchivo() const;
};

#endif 

