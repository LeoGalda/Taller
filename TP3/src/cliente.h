#ifndef CLIENTE_H
#define CLIENTE_H

#include "common_Buffer.h"
#include "common_Socket.h"
#include "client_Accion.h"

#define REQUEST_MAX_LEN 128

class Cliente {
private:
    Socket socket;
    Buffer buffer;
    
public:
    Cliente();
    Cliente(char *ip, char *puerto);
    int ejecutar(Accion *accion);
    virtual ~Cliente();
};

#endif