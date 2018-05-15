#ifndef CLIENT_ACCIONPULL_H
#define CLIENT_ACCIONPULL_H

#include "common_Accion.h"
#include "common_Socket.h"
#include <string>
#include <vector>

class AccionPull : public Accion {
private:
    std::string hash;
    
public:
//constructor del AccionPull
    explicit AccionPull(char *hash);
    
//ejecuta la logica del pull y guarda en data los datos a enviar.    
    void ejecutar(Protocolo *protocolo);
    
//envia los datos qeu se encuetran en data;    
    void enviar(Protocolo *protocolo);

//recibe la respuesta del server y dependiendo la respuesta realiza
//las acciones pertinentes    
    void responder(Protocolo *protocolo);
        
//crea los archivos de la informacion que recibio del server    
    void crearArchivosPull(Protocolo *protocolo);
    
//devuelve el valor numerico que le corresponde    
    unsigned char getValorNumerico();
    
//destructor del AccionPull    
    virtual ~AccionPull();    
};

#endif 

