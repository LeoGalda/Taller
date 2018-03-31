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

#include "servidor.h"

void servidor_create(Servidor *this,char *puerto, char *key){
	this->key = key;
	this->puerto = puerto;	
	this->skt = 0;
}

int servidor_configurar(Servidor *this){	
	int status;
	memset(&hints, 0, sizeof(struct addrinfo));	
	hints.ai_family = AF_INET;       /* IPv4 */
	hints.ai_socktype = SOCK_STREAM; /* TCP */
	hints.ai_flags = AI_PASSIVE;     /* AI_PASSIVE for server*/		
	status = getaddrinfo(NULL, this->puerto, &hints, &ptr);
	if (status != 0) { 
      	printf("Error in getaddrinfo: %s\n", gai_strerror(status));
      	return 1;
   	}
	this->skt = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
	if (this->skt == -1) {
	    printf("Error: %s\n", strerror(errno));
	    freeaddrinfo(ptr);
	    return 1;
	}
	status = bind(this->skt, ptr->ai_addr, ptr->ai_addrlen);
   	if (status == -1) {
        printf("Error: %s\n", strerror(errno));
      	close(this->skt);
      	freeaddrinfo(ptr);
    	return 1;
   	}
	freeaddrinfo(ptr);
	status = listen(this->skt, 1);
	if (status == -1) {
		printf("Error: %s\n", strerror(errno));
		close(this->skt);
		return 1;
	}
	return 0;
}

int servidor_conectar(Servidor *this){
	 return accept(this->skt, NULL, NULL);   // aceptamos un cliente	      	
}