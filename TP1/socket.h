#ifndef __SOCKET_H__
#define __SOCKET_H__

#include <errno.h>
#include "buffer.h"
#include <netdb.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

typedef struct {
    int fd;
} Socket;


//Inicializa la instancia this para ser utilizada
void socket_crear(Socket * this);

//hace el bind al puerto que se va a asociar al socket
int socket_bind(Socket * this, char *puerto);

//hace el listen del socket
int socket_listen(Socket * this);

//conecta el socket al puerto e ip pasado por parametro
int socket_conectar(Socket * this, char *puerto, char *ip);

//acepta un cliente
void socket_aceptar(Socket * this, Socket *peer);

// Envia datos a traves del socket
int socket_enviar_datos(Socket * this, Buffer *buffer);

// recibe los datos del socket
int socket_recibir_datos(Socket * this, Buffer *buffer);

int socket_get_FD(Socket * this);

// Destruyo la instancia this para liberar sus recursos
void socket_destroy(Socket * this);

#endif
