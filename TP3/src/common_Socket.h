#ifndef SOCKET_H
#define SOCKET_H

#include <errno.h>
#include "common_Buffer.h"
#include <netdb.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

class Socket {
private:
    char *puerto;
    char *ip;
    struct addrinfo *ptr;
    int sock, peerskt;
public:

    Socket(char *puerto, char *ip);
    
    // Configura la forma en la que se va a conectar con el socket
    int configurar(bool soyServidor);

    //conecta el socket
    int conectar(bool soyServidor);

    //acepta un cliente
    void aceptar();

    // Envia datos a traves del socket
    int enviarDatos(Buffer *buffer);

    // recibe los datos del socket
    int recibirDatos(Buffer *buffer);
    
    int getPeerskt();

    virtual ~Socket();
};

#endif /* SOCKET_H */

