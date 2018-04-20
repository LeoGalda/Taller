#ifndef ACCIONTAG_H
#define ACCIONTAG_H

#include <vector>
#include <string>
#include "client_Accion.h"

class AccionTag : public Accion {
private:    
    std::string version;
    std::vector<std::string> hashes;
public:    
    AccionTag(char *version);
    void ejecutar();
    void agregarHash(char *hash);
    int getValorNumerico();
    virtual ~AccionTag();
};

#endif

