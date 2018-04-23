#ifndef SERVIDOR_H
#define SERVIDOR_H
#include <stdbool.h>
#include <fstream>
#include "common_Buffer.h"
#include "common_Socket.h"

#define RESPONSE_MAX_LEN 128

class Server {
private:
    Socket socket;
    char *ruta;  
    Buffer buffer;
    std::fstream indice;  
public:
    Server();
    Server(char *puerto, char *ruta);
    void recibirDatos();
    virtual ~Server();
};

#endif

