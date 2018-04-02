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

#include "cliente.h"

#define REQUEST_MAX_LEN 64

void cliente_create(Cliente *this,char *puerto, char *key, char *ip){
	this->key = key;
	this->puerto = puerto;	
	this->ip = ip;
	this->socket = 0;
}

int cliente_configurar(Cliente *this){	
	int status;
	memset(&hints, 0, sizeof(struct addrinfo));	
	hints.ai_family = AF_INET;       /* IPv4 */
	hints.ai_socktype = SOCK_STREAM; /* TCP */
	hints.ai_flags = 0;			     /* NONE*/

	status = getaddrinfo(this->ip, this->puerto, &hints, &ptr);

	if (status != 0) { 
      	printf("Error in getaddrinfo: %s\n", gai_strerror(status));
      	return 1;
   	}
	return 0;
}

int cliente_conectar(Cliente *this){
	bool conectado = false;
	int status;
	struct  addrinfo *aux;
	for(aux = ptr; aux != NULL && conectado == false; aux = aux->ai_next) {
    	this->socket = socket(aux->ai_family, aux->ai_socktype, aux->ai_protocol);
    	if (this->socket == -1) {
	        printf("Error: %s\n", strerror(errno));
    	    return 1;
    	}
    	else{
	        status = connect(this->socket, aux->ai_addr, aux->ai_addrlen);
    	    if (status == -1) {
        	    printf("Error: %s\n", strerror(errno));
            	close(this->socket);
            	return 1;
        	}
        	conectado = (status != -1);
    	}
	}
    freeaddrinfo(ptr);
    if (!conectado) return 1;        
    return 0;
}

int cliente_enviar_datos(Cliente *this, Encriptador *encriptador){   
   	int bytesEnviados = 0;
   	int informacion[REQUEST_MAX_LEN];   	
   	int cantidad = 0;
   	bool errorDelSocket = false, socketCerrado = false;
   	int status;

	Elemento *unElemento = encriptador->inicio;	
	while (unElemento != NULL){
		informacion[cantidad] = unElemento->dato;
		cantidad++;
		unElemento = unElemento->siguiente;
	}   	    	
	printf("cantidad:%i\n",cantidad );

   	while (bytesEnviados < cantidad && errorDelSocket == false && socketCerrado == false) {
    	status = send(this->socket, &informacion[bytesEnviados], cantidad - bytesEnviados, MSG_NOSIGNAL);

    	if (status < 0) {  // ups,  hubo un error
        	printf("Error: %s\n", strerror(errno));
            errorDelSocket = true;
        }
      	else if (status == 0) { // nos cerraron el socket :(
        	socketCerrado = true;
      	}
      	else {
         	bytesEnviados += status;
      	}
   	}   	
	if (socketCerrado || errorDelSocket) {
		shutdown(this->socket, SHUT_RDWR);
  		close(this->socket);
  		return 1;
   	}	
	return 0;
}