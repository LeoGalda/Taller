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


void cliente_create(Cliente *this,char *puerto, char *key, char *ip){
	this->key = key;
	this->puerto = puerto;	
	this->ip = ip;
	this->skt = 0;
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
    	this->skt = socket(aux->ai_family, aux->ai_socktype, aux->ai_protocol);
    	if (this->skt == -1) {
	        printf("Error: %s\n", strerror(errno));
    	    return 1;
    	}
    	else{
	        status = connect(this->skt, aux->ai_addr, aux->ai_addrlen);
    	    if (status == -1) {
        	    printf("Error: %s\n", strerror(errno));
            	close(this->skt);
            	return 1;
        	}
        	conectado = (status != -1);
    	}
	}

    freeaddrinfo(ptr);

    if (conectado == false) {
    	return 1; 
    }
    printf("creo que me conecte");
    return 0;
}