#ifndef ACCIONPUSH_H
#define ACCIONPUSH_H

#include "client_Accion.h"
#include <fstream>
#include <string>

class AccionPush : public Accion {
private:    
    std::string nombreArchivo;
    std::string hash;
    std::ifstream archivo;
    unsigned char *data;
public:
    AccionPush(char *arch, char *hash);
    int ejecutar();
    unsigned int getValorNumerico();
    ~AccionPush();
};

#endif 

