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
    explicit Protocolo(Socket *socket);
    std::string convertirAString(Buffer *buffer) const;
    std::string recibirYFormatear() const;
    void formatearYEnviarLongitud(int longitud);
    void enviarData(std::string &data);
    void enviarComando(unsigned char comando);
    unsigned char recibirComando();
    int recibirLongitud();
    virtual ~Protocolo();


};

#endif

