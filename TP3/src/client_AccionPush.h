#ifndef ACCIONPUSH_H
#define ACCIONPUSH_H

#include "client_Accion.h"
#include <fstream>
#include <string>

class AccionPush : public Accion {
private:
    std::ifstream archivo;
    std::string hash;
    std::string nombreArchivo;
public:
    AccionPush(char *arch, char *hash);
    void ejecutar();
    int getValorNumerico();
    ~AccionPush();
};

#endif 

