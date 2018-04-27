#ifndef SOCKET_H
#define SOCKET_H

#include <errno.h>
#include "client_Accion.h"
#include <netdb.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include "common_Buffer.h"

class Socket {
private:
    int fd;
public:

    //Inicializa la instancia this para ser utilizada
    Socket();

    //hace el bind al puerto que se va a asociar al socket
    int doBind(char *puerto);

    //hace el listen del socket
    int doListen();

    //conecta el socket al puerto e ip pasado por parametro
    int conectar(char *puerto, char *ip);

    //acepta un cliente
    void aceptar(Socket *peer);

    // Envia datos a traves del socket
    int enviarDatos(Accion *accion);

    // recibe los datos del socket
    int recibirDatos(Buffer *buffer);
    
    // devuelve el File Descriptor
    int getFD();

    // Destruyo la instancia this para liberar sus recursos
    ~Socket();
};

#endif /* SOCKET_H */

