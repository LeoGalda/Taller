#ifndef SERVER_H
#define SERVER_H

#include "server_Thread.h"
#include "server_Aceptador.h"

class Server{
public:
//llama al constructor del server    
    Server();
    
//ejecuta los hilos de los clientes hasta que recibe por entrada estandar
//una letra q
    void aceptarCliente(Aceptador &aceptador);
    
//destructor del server    
    virtual ~Server();
private:
};

#endif

