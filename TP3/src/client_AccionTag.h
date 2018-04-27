#ifndef ACCIONTAG_H
#define ACCIONTAG_H

#include <vector>
#include <string>
#include "client_Accion.h"

//class AccionTag : public Accion {
class AccionTag{
private:    
    std::string version;
    std::vector<std::string> hashes;
public:    
    AccionTag(char *version);
    int ejecutar();
    void agregarHash(char *hash);
    unsigned int getValorNumerico();
    int getTamanio();
    std::string getNombreArchivo() const;
    virtual ~AccionTag();
};

#endif

