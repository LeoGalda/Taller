#ifndef ACCIONPUSH_H
#define ACCIONPUSH_H

#include "client_Accion.h"
#include <vector>
#include <fstream>
#include <string>

class AccionPush : public Accion {
private:    
    std::string nombreArchivo;
    std::string hash;
    std::ifstream archivo;
    std::vector<unsigned char> data;
public:
    AccionPush(char *arch, char *hash);
    int ejecutar();
    unsigned int getValorNumerico();    
    int getTamanio();
    std::string getNombreArchivo() const;
    std::vector<unsigned char> getData() const;
    ~AccionPush();
};

#endif 

