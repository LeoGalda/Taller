#ifndef __SOCKET_H__
#define __SOCKET_H__

typedef struct{
	char *puerto;
	char *ip;
	struct addrinfo hints;
	struct addrinfo *ptr;
	int sock;
} Socket;


//Inicializa la instancia this para ser utilizada
void socket_crear(Socket *this,char *puerto, char *ip);

// Configura la forma en la que se va a conectar con el socket
int socket_configurar(Socket *this, bool soyServidor);

//conecta el socket
int socket_conectar(Socket *this);

// Envia datos a traves del socket
int socket_enviar(Socket *this,char *buffer, int tamanio);

// recibe los datos del socket y retorna la cantidad que se recibio
int socket_recibir(Socket *this,char *buffer, int tamanio);

// Destruyo la instancia this para liberar sus recursos
void socket_destroy(Socket *this);

#endif