#ifndef SERVIDOR_H
#define SERVIDOR_H
#include <netdb.h>
#include <stdbool.h>
#include <fstream>
#include "Buffer.h"
#include "Socket.h"

class Servidor {
private:
    Socket socket;
    std::fstream indice;
    char *ruta;    
public:
    Servidor();
    Servidor(char *puerto, char *ruta);
    virtual ~Servidor();
};

#endif

