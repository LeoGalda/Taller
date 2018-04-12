#define _POSIX_C_SOURCE 200112L

#include <errno.h>
#include <netdb.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include "socket.h"



void socket_crear(Socket *this,char *puerto, char *ip){
	this->puerto = puerto;
	this->ip = ip;
}


int socket_configurar(Socket *this,bool soyServidor){
	int status;
	memset(&this->hints, 0, sizeof(struct addrinfo));	
	this->hints.ai_family = AF_INET;       /* IPv4 */
	this->hints.ai_socktype = SOCK_STREAM; /* TCP */	
	this->hints.ai_flags = soyServidor ? AI_PASSIVE : 0;
	status = getaddrinfo(this->ip, this->puerto, &this->hints, &this->ptr);
	if (status != 0) { 
      	printf("Error in getaddrinfo: %s\n", gai_strerror(status));
      	return 1;
 	}
	return 0;
}


int socket_conectar(Socket *this){

}


int socket_enviar(Socket *this,char *buffer, int tamanio){

}


int socket_recibir(Socket *this,char *buffer, int tamanio){

}


void socket_destroy(Socket *this){
	freeaddrinfo(this->ptr);
	shutdown(this->sock, SHUT_RDWR);
    close(this->sock);
}