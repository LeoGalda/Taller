#ifndef CLIENT_ACCIONPULL_H
#define CLIENT_ACCIONPULL_H

#include "common_Accion.h"
#include "common_Socket.h"
#include <string>

class AccionPull : public Accion {
private:
    std::string hash;
    std::vector<unsigned char> data;
public:
    explicit AccionPull(char *hash);
    void ejecutar();
    virtual ~AccionPull();
    void enviar(Socket *socket);
    void responder(Socket *socket);
    void crearArchivosPull(Socket *socket);
    int getValorNumerico();
    int getTamanio();
};

#endif 

