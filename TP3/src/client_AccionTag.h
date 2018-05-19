#ifndef CLIENT_ACCIONTAG_H
#define CLIENT_ACCIONTAG_H

#include <vector>
#include <string>
#include "common_Accion.h"

class AccionTag : public Accion {
private:
    std::string version;
    std::vector<std::string> hashes;
    
public:
//constructor del Accion Tag    
    explicit AccionTag(char *version);

//envia los datos  de la logica del tag y todos sus hashes con 
//sus respectivos tamanios           
    void ejecutar(Protocolo *protocolo);   
    
//recibe la respuesta del server    
    void responder(Protocolo *protocolo);
    
//agrega un hash al vector de hash    
    void agregarHash(char *hash);

//devuelve el valor numerico que le corresponde    
    unsigned char getValorNumerico();   
    
//destructor del AccionTag    
    virtual ~AccionTag();
};

#endif

