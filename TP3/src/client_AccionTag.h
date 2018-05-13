#ifndef CLIENT_ACCIONTAG_H
#define CLIENT_ACCIONTAG_H

#include <vector>
#include <string>
#include "common_Accion.h"

class AccionTag : public Accion {
private:
    std::string version;
    std::vector<std::string> hashes;
    std::vector<unsigned char> data;
    
public:
//constructor del Accion Tag    
    explicit AccionTag(char *version);

//ejecuta la logica del tag y guarda en data los datos a enviar.            
    void ejecutar();
    
//envia los datos qeu se encuetran en data y todos sus hashes con 
//sus respectivos tamanios    
    void enviar(Socket *socket);
    
//recibe la respuesta del server    
    void responder(Socket *socket);
    
//agrega un hash al vector de hash    
    void agregarHash(char *hash);

//devuelve el valor numerico que le corresponde    
    int getValorNumerico();
    
//devuelve el tamanio de data     
    int getTamanio();
    
//destructor del AccionTag    
    virtual ~AccionTag();
};

#endif

