#ifndef __COMMON_SOCKET_H__
#define __COMMON_SOCKET_H__

#include "buffer.h"

typedef struct{
	char *puerto;
	char *ip;
	struct addrinfo hints;
	struct addrinfo *ptr;
	int sock,peerskt;
} Socket;


//Inicializa la instancia this para ser utilizada
void socket_crear(Socket *this,char *puerto, char *ip);

// Configura la forma en la que se va a conectar con el socket
int socket_configurar(Socket *this, bool soyServidor);

//conecta el socket
int socket_conectar(Socket *this, bool soyServidor);

//acepta un cliente
void socket_aceptar(Socket *this);


// Envia datos a traves del socket
//int socket_enviar_datos(Socket *this,char *buffer, int tamanio);

// recibe los datos del socket
int socket_recibir_datos(Socket *this,Buffer *buffer);

// Destruyo la instancia this para liberar sus recursos
void socket_destroy(Socket *this);

#endif