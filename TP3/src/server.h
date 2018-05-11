#ifndef SERVER_H
#define SERVER_H

#include "server_Thread.h"
#include "server_Aceptador.h"

class Server{
public:
    Server();
    void aceptarCliente(Aceptador &aceptador);
    virtual ~Server();
private:
};

#endif

