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
	memset(&this->hints, 0, sizeof(struct addrinfo));	
	this->hints.ai_family = AF_INET;       /* IPv4 */
	this->hints.ai_socktype = SOCK_STREAM; /* TCP */
	this->hints.ai_flags = 0;			     /* NONE*/

	status = getaddrinfo(this->ip, this->puerto, &this->hints, &this->ptr);

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
	for(aux = this->ptr; aux != NULL && conectado == false; aux = aux->ai_next) {
    	this->socket = socket(aux->ai_family, aux->ai_socktype, aux->ai_protocol);
    	if (this->socket == -1) {
	        printf("Error: %s\n", strerror(errno));
    	    return 1;
    	}else{
	        	status = connect(this->socket, aux->ai_addr, aux->ai_addrlen);
    	    	if (status == -1) {
        	    	printf("Error: %s\n", strerror(errno));
            		close(this->socket);
            		return 1;
        		}
        		conectado = (status != -1);
    		}
	}
    freeaddrinfo(this->ptr);
    if (!conectado) return 1;        
    return 0;
}

int cliente_enviar_datos(Cliente *this, Encriptador *encriptador){   
   	int bytesEnviados = 0;
   	unsigned char informacion[REQUEST_MAX_LEN];   	
   	int cantidad = 0;
   	bool errorDelSocket = false, socketCerrado = false;
   	int status;

	Elemento *unElemento = encriptador->inicio;	
	while (unElemento != NULL){
		informacion[cantidad] = unElemento->dato;
		cantidad++;
		unElemento = unElemento->siguiente;
	}   	    			
   	while (bytesEnviados < cantidad && errorDelSocket == false && 
   			socketCerrado == false) {
    	status = send(this->socket, &informacion[bytesEnviados],
    				  cantidad - bytesEnviados, MSG_NOSIGNAL);

    	if (status < 0) {
        	printf("Error enviar cliente datos: %s\n", strerror(errno));
            errorDelSocket = true;
        }else if (status == 0) {
        		socketCerrado = true;
      	}else {
         		bytesEnviados += status;
      	}
   	}   	
	if (socketCerrado || errorDelSocket) {
      cliente_destroy(this);
  		return 1;
   	}	
	return 0;
}

void cliente_destroy(Cliente *this){
    shutdown(this->socket, SHUT_RDWR);
    close(this->socket);
}

static void ejecutarEncriptador(char *clave,FILE *input,
                int *prgaI,int *prgaJ, int control,
                Encriptador *encriptador){  
  encriptador_crear(encriptador, clave);  
  if(control == 0){
    encriptador_fase_KSA(encriptador);    
  } 
  encriptador_encriptar(encriptador,input,REQUEST_MAX_LEN,prgaI,prgaJ); 
  encriptador_salida_estandar(encriptador);
  encriptador_salida_errores(encriptador);
}

int cliente_ejecutar_cliente(int cantidad,char *ip, char* puerto, 
          char *clave,char *arch){    
  int status;
  Cliente cliente;
  cliente_create(&cliente, puerto, clave, ip);
  status = cliente_configurar(&cliente);    
  if(status){
    cliente_destroy(&cliente);
    return 1;
  } 
  status = cliente_conectar(&cliente);    
  if(status){
    cliente_destroy(&cliente);
    return 1;
  } 
  FILE* input;              
  input = fopen(arch,"r");          
  int prgaI = 0;
  int prgaJ = 0;
  int control = 0;
  Encriptador encriptador;
  while(!feof(input)){      
    ejecutarEncriptador(clave, input,&prgaI,&prgaJ,control,&encriptador);
    status = cliente_enviar_datos(&cliente, &encriptador);
    if(status){
      printf("Error al enviar los datos\n");
      cliente_destroy(&cliente);
      return 1; 
    } 
    encriptador_destroy(&encriptador);
    control++;
  }
  fclose(input);    
  cliente_destroy(&cliente);
  return 0;
}