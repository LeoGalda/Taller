#ifndef CLIENTE_H
#define CLIENTE_H

//#include "common_Buffer.h"
#include "common_Socket.h"
#include "common_Accion.h"

class Cliente {
private:
    Socket socket;
//    Buffer buffer;
    
public:
    Cliente();
    Cliente(char *ip, char *puerto);
    int ejecutar(Accion *accion);
    virtual ~Cliente();
};

#endif
