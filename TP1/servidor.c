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

#define RESPONSE_MAX_LEN 50

void servidor_create(Servidor *this,char *puerto, char *key){
	this->key = key;
	this->puerto = puerto;	
	this->socket = 0;
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
	this->socket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
	if (this->socket == -1) {
	    printf("Error: %s\n", strerror(errno));
	    freeaddrinfo(ptr);
	    return 1;
	}
	status = bind(this->socket, ptr->ai_addr, ptr->ai_addrlen);
   	if (status == -1) {
        printf("Error: %s\n", strerror(errno));
      	close(this->socket);
      	freeaddrinfo(ptr);
    	return 1;
   	}
	freeaddrinfo(ptr);
	status = listen(this->socket, 1);
	if (status == -1) {
		printf("Error: %s\n", strerror(errno));
		close(this->socket);
		return 1;
	}
	return 0;
}

int servidor_conectar(Servidor *this){
	 return accept(this->socket, NULL, NULL);   // aceptamos un cliente	      	
}

int recv_message(int skt, unsigned char *buf, int size,bool *corriendo) {
   	int received = 0;
   	int s = 0;
   	bool socketValido = true;
   	while (received < size && socketValido) {
      	printf("recibiendo\n");
      	s = recv(skt, &buf[received], size - received, MSG_NOSIGNAL);

      	if(s > 0){
      		received += s;
      	}else{
      		socketValido = false;
      	}
   	}   	
/*   	printf("tamaño:%i\n", size);
   	printf("recibido:%i\n", received);
   	printf("esto tiene buf?:");   	 
   	for(int l = 0; l < received; l++){
		printf("%02x\n", *buf);
		buf++;
	}*/
    if (socketValido){ 
    	return received;
   	}else if (s == 0){
   		*corriendo = false;
   		return received;
   	}else {   		
   		printf("nooo");
      	return -1;
   	}   	
}

int servidor_recibir_datos(Servidor *this, int peerskt,unsigned char *buf,
							 int *rec,bool *corriendo){		
	*rec = recv_message(peerskt, buf, RESPONSE_MAX_LEN,corriendo);     			
	if (!*corriendo){
		shutdown(peerskt, SHUT_RDWR);
    	close(peerskt);    
    	printf("cierro socket\n");
    	return 1;
	}
	if(*rec < 0){
		printf("problema\n");
		return 1;
	}
    return 0;
}
