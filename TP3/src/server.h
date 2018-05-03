#ifndef SERVER_H
#define SERVER_H
#include <stdbool.h>
#include <fstream>
#include "common_Buffer.h"
#include "common_Socket.h"
#include "server_Indice.h"

class Server {
private:
    Socket socket;
public:
    explicit Server(char *puerto);
    int pushea(Socket *peerskt,Indice *indice);
    int tagea(Socket *peerskt,Indice *indice);
    void aceptarClientes(Indice *indice);
    virtual ~Server();
};

#endif

