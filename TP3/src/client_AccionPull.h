#ifndef CLIENT_ACCIONPULL_H
#define CLIENT_ACCIONPULL_H

#include "common_Accion.h"
#include "common_Socket.h"
#include <string>
#include <vector>

class AccionPull : public Accion {
private:
    std::string hash;
    std::vector<unsigned char> data;
    
public:
//constructor del AccionPull
    explicit AccionPull(char *hash);
    
//ejecuta la logica del pull y guarda en data los datos a enviar.    
    void ejecutar();
    
//envia los datos qeu se encuetran en data;    
    void enviar(Socket *socket);

//recibe la respuesta del server y dependiendo la respuesta realiza
//las acciones pertinentes    
    void responder(Socket *socket);
        
//crea los archivos de la informacion que recibio del server    
    void crearArchivosPull(Socket *socket);
    
//devuelve el valor numerico que le corresponde    
    int getValorNumerico();

//devuelve el tamanio de data    
    int getTamanio();
    
//destructor del AccionPull    
    virtual ~AccionPull();    
};

#endif 

