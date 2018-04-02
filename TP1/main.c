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

#define REQUEST_MAX_LEN 64
#define RESPONSE_MAX_LEN 50

void ejecutarDesencriptador(char *clave,int *buf,Encriptador *desencriptador,
							int *prgaI,int *prgaJ,int recibidos){		
	FILE *salida = fopen("./out", "w+");
	encriptador_crear(desencriptador, clave);	
	encriptador_fase_KSA(desencriptador);			
	encriptador_desencriptar(desencriptador,buf,recibidos,prgaI,prgaJ);	
	encriptador_guardar_en_salida(desencriptador,salida);
	encriptador_salida_estandar(desencriptador);
	encriptador_salida_errores(desencriptador);		
}


int ejecutarServidor(char *puerto,char *key){
	int status,peerskt;
	bool corriendo = true;	
	Servidor servidor;
	int *buf = 0;
	int recibidos = 0;
	servidor_create(&servidor, puerto, key);
	status = servidor_configurar(&servidor);	
	if(status) return 1;	
	Encriptador desencriptador;
	int prgaI = 0;
	int prgaJ = 0;
//	int control = 0;
	while (corriendo) {
	    printf("esperando un cliente\n");
	    peerskt = servidor_conectar(&servidor);	    
	    printf("--- conectando ---\n");
	    if (peerskt == -1) {
	        printf("Error: %s\n", strerror(errno));
	         corriendo = false;
	    }	    
	    else{
	        printf("NuevoCliente\n");
	        servidor_recibir_datos(&servidor,peerskt,buf,&recibidos);	        	        
	        ejecutarDesencriptador(key,buf,&desencriptador,&prgaI,&prgaJ,recibidos);
	    }
	}
	encriptador_destroy(&desencriptador);
	printf("terminando\n");
   	shutdown(servidor.socket, SHUT_RDWR);
   	close(servidor.socket);
		//despues del accept
		return SUCCESS;
}

void ejecutarEncriptador(char *clave,FILE *input,
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

int ejecutarCliente(int cantidad,char *ip, char* puerto, 
					char *clave,char *arch){		
	int status;
	Cliente cliente;
	cliente_create(&cliente, puerto, clave, ip);
	status = cliente_configurar(&cliente);		
	if(status) return 1;
	status = cliente_conectar(&cliente);		
	if(status) return 1;
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
			printf("idiota estas muerto\n");
			return 1;	
		} 
		encriptador_destroy(&encriptador);
		control++;
	}
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


