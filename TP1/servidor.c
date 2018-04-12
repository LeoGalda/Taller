#define _POSIX_C_SOURCE 200112L

#include <errno.h>
#include <netdb.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "servidor.h"
#include "encriptador.h"

#define RESPONSE_MAX_LEN 50


static void servidor_ejecutar_desencriptador(char *clave,unsigned char *buf,
							Encriptador *desencriptador,int *prgaI,int *prgaJ,
							int recibidos, int control){			
	encriptador_crear(desencriptador, clave);	
	if (control == 0){
		encriptador_fase_KSA(desencriptador);			
	}	
	encriptador_desencriptar(desencriptador,buf,recibidos,prgaI,prgaJ);	
	encriptador_salida_estandar(desencriptador);
	encriptador_salida_errores(desencriptador);		
}


int servidor_ejecutar_servidor(char *puerto,char *key){
	int status,peerskt;
	bool corriendo = true;	
        
	Servidor servidor;
	int recibidos = 0;
        
	servidor_create(&servidor, puerto, key);        
        
	status = servidor_configurar(&servidor);
	
	if(status) return 1;	
	Encriptador desencriptador;
	FILE *salida = fopen("./out", "wg");
	int prgaI = 0;
	int prgaJ = 0;
	int control = 0;	
	peerskt = servidor_conectar(&servidor);	    	
	while (corriendo) {		
	    if (peerskt == -1) {
	        printf("Error: %s\n", strerror(errno));
	         corriendo = false;
	    }else{	      
	  unsigned char *buf;	
	  buf = (unsigned char*) malloc(sizeof(unsigned char) * RESPONSE_MAX_LEN);
	      servidor_recibir_datos(&servidor,peerskt,buf,&recibidos,&corriendo);

	      servidor_ejecutar_desencriptador(key,buf,&desencriptador,&prgaI,&prgaJ,
	       						  recibidos,control);

	      encriptador_guardar_en_salida(&desencriptador,salida);	        
	      control++;
	      encriptador_destroy(&desencriptador);
	      free(buf);
	    }
	}	
	fclose(salida);	
	servidor_destroy(&servidor);
	return 0;	
}


void servidor_create(Servidor *this,char *puerto, char *key){
	this->key = key;
	this->puerto = puerto;	
	this->socket = 0;
}

int servidor_configurar(Servidor *this){		

	this->socket = socket(this->ptr->ai_family, this->ptr->ai_socktype,
						  this->ptr->ai_protocol);
	if (this->socket == -1) {
	    printf("Error: %s\n", strerror(errno));
	    freeaddrinfo(this->ptr);
	    return 1;
	}
	status = bind(this->socket, this->ptr->ai_addr,
				  this->ptr->ai_addrlen);
   	if (status == -1) {
        printf("Error: %s\n", strerror(errno));
      	close(this->socket);
      	freeaddrinfo(this->ptr);
    	return 1;
   	}

   	
	freeaddrinfo(this->ptr);
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
      	s = recv(skt, &buf[received], size - received, MSG_NOSIGNAL);

      	if(s > 0){
      		received += s;
      	}else{
      		socketValido = false;
      	}
   	}   	
    if (socketValido){ 
    	return received;
   	}else if (s == 0){
   		*corriendo = false;
   		return received;
   	}else {   		
   		printf("Error al recibir los datos\n");
      	return -1;
   	}   	
}

int servidor_recibir_datos(Servidor *this, int peerskt,unsigned char *buf,
							 int *rec,bool *corriendo){		
	*rec = recv_message(peerskt, buf, RESPONSE_MAX_LEN,corriendo);     			
	if (!*corriendo){
		servidor_destroy(this);        	
    	return 1;
	}
	if(*rec < 0){
		printf("problema\n");
		return 1;
	}
    return 0;
}

void servidor_destroy(Servidor *this){
   	shutdown(this->socket, SHUT_RDWR);
   	close(this->socket);
}


