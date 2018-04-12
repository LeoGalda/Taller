#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdlib.h>
#include "servidor.h"
#include "cliente.h"

#define ERROR 1

static int errorParametros(){
	fprintf(stderr,"Parámetros incorrectos.");
	return ERROR;
}

int main(int argc, char* argv[]){	
	if(argc < 4){
		return errorParametros();
	}
	if(strcmp(argv[1],"server") == 0){		
		if (argc != 4){
		}
		return servidor_ejecutar_servidor(argv[2],argv[3]);
	}else if (strcmp(argv[1],"client") == 0){
		if (argc != 6){
			return errorParametros();
		}			
		return cliente_ejecutar_cliente(argc,argv[2],argv[3],argv[4],argv[5]);
	}else{
		 return errorParametros();
	}	
}


