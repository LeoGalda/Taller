#ifndef SERVIDOR_H
#define SERVIDOR_H
#include <stdbool.h>
#include <fstream>
#include "common_Buffer.h"
#include "common_Socket.h"

class Server {
private:
    Socket socket;
    std::fstream indice;
    char *ruta;    
public:
    Server();
    Server(char *puerto, char *ruta);
    virtual ~Server();
};

#endif

