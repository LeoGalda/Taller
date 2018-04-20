#ifndef CLIENTE_H
#define CLIENTE_H

#include "common_Buffer.h"
#include "common_Socket.h"

class Cliente {
private:
    Socket socket;
public:
    Cliente();
    Cliente(char *ip, char *puerto);
    
    virtual ~Cliente();
};

#endif