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

#include "encriptador.h"
#include "servidor.h"
#include "cliente.h"

#define SUCCESS 0
#define ERROR 1

#define REQUEST_MAX_LEN 128
#define RESPONSE_MAX_LEN 1024

char* buscarArchivo(char *argumento);


int ejecutarServidor(char *puerto,char *key){
	int status,peerskt;
	bool corriendo = true;	
	Servidor servidor;
	servidor_create(&servidor, puerto, key);
	status = servidor_configurar(&servidor);	
	if(status) return 1;	
	while (corriendo) {
	    printf("esperando un cliente\n");
	    peerskt = servidor_conectar(&servidor);	    
	    printf("--- conectando ---");
	    if (peerskt == -1) {
	        printf("Error: %s\n", strerror(errno));
	         corriendo = false;
	    }	    
/*	    else{
	        printf("New client\n");
	        memset(small_buf, 0, 3);
	        recv_message(peerskt, small_buf, 2); 	         
	        len = atoi(small_buf);
	        printf("Echo %i bytes\n", len);
	        if (len == 0) {
	        	printf("Zero bytes. Bye!\n");
	            continue_running = false;
	        }
	        else{
	        	tmp = (char*) malloc(sizeof(char) * len);
	        	printf("hacer algo");
	            free(tmp);
	        }
	        shutdown(peerskt, SHUT_RDWR);
	        close(peerskt);
	    }*/
	}
		//despues del accept
		printf("aca esta mi logica");
		Encriptador encriptador;
		FILE * salida = fopen("./out", "w+");
		Encriptador desencriptador;		
		desencriptador = encriptador;
		encriptador_desencriptar(&desencriptador,salida);
		fclose(salida);
		encriptador_destroy(&encriptador);
		return SUCCESS;
}

int ejecutarCliente(int cantidad,char *ip, char* puerto, char *clave,char *arch){
		int status;
		Cliente cliente;
		cliente_create(&cliente, puerto, clave, ip);
		status = cliente_configurar(&cliente);		
		if(status) return 1;
		status = cliente_conectar(&cliente);
		if(status) return 1;
		FILE* input;
		char *archivo;		
		if (cantidad > 1){		
			archivo = buscarArchivo(arch);
			input = fopen(archivo,"r"); 			
		}else{
			printf("ingresa la ruta del archivo nabo!\n");
			return ERROR;
		}	
		Encriptador encriptador;
		encriptador_crear(&encriptador, clave);
		encriptador_encriptar(&encriptador,input);	
		encriptador_salida_estandar(&encriptador);
		encriptador_salida_errores(&encriptador);
		fclose(input);

		return SUCCESS;
}


int main(int argc, char* argv[]){
	if(strcmp(argv[1],"server") == 0){		
		return ejecutarServidor(argv[2],argv[3]);
	}else if(strcmp(argv[1],"client") == 0){
		return ejecutarCliente(argc,argv[2],argv[3],argv[4],argv[5]);
	}else{
		printf("ingresaste cualquier cosa\n");
		return ERROR;
	}
}


char* buscarArchivo(char* argv){
	return argv;
}

