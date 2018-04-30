#ifndef SERVER_H
#define SERVER_H
#include <stdbool.h>
#include <fstream>
#include "common_Buffer.h"
#include "common_Socket.h"
#include "server_Indice.h"

#define RESPONSE_MAX_LEN 128

class Server {
private:
    Socket socket;
    Indice indice;  
//    Buffer buffer;
public:
    Server(char *puerto, char *ruta);
    void aceptarClientes();
    virtual ~Server();
};

#endif

