#ifndef COMMON_PROTOCOLO_H
#define COMMON_PROTOCOLO_H

#include <string>
#include "common_Buffer.h"
#include "common_Socket.h"

#define TAMANIO_DEL_COMANDO 1
#define TAMANIO_DEL_ENVIO_LONG 4

class Protocolo {
private:
    Socket *socket;
    
public:
//constructor del protocolo    
    explicit Protocolo(Socket *socket);

//convierte el dato de un buffer a un string    
    std::string convertirAString(Buffer *buffer) const;
    
//realiza la logica de recibir del socket la longitud y convertirla al idioma 
//del network y luego recibir los datos de esa longitud y 
//devolverlo como un string    
    std::string recibirYFormatear() const;
    
//formatea la longitud a 4 bytes y la convierte en big endian para enviarla    
    void formatearYEnviarLongitud(int longitud);
    
//envia los datos recibidos por parametro    
    void enviarData(std::string &data);
    
//envia el comando pasado por parametro tomando como tamanio TAMANIO_DEL_COMANDO
    void enviarComando(unsigned char comando);
    
//recibe el comando del socket leyendo la TAMANIO_DEL_COMANDO bytes    
    unsigned char recibirComando();
    
//devuelve la longitud del socket leyendo TAMANIO_DEL_ENVIO_LONG
// y la convierte a ntohl 
    int recibirLongitud();
    
//destructor del protocolo    
    virtual ~Protocolo();
};

#endif

