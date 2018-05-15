#ifndef CLIENTE_H
#define CLIENTE_H

#include "common_Socket.h"
#include "common_Accion.h"
#include "common_Protocolo.h"

class Cliente {
private:
    Socket socket;    
    
public:
//constructor del cliente y realiza el connect    
    Cliente(char *ip, char *puerto);
    
//ejecuta la logica del cliente    
    int ejecutar(Accion *accion);
    
//destructor del cliente    
    virtual ~Cliente();
};

#endif
