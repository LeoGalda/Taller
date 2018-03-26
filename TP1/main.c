#include <stdio.h>
#include "encriptador.h"

#define SUCCESS 0
#define ERROR 1

char* buscarArchivo(char* argumento);

int main(int argc, char* argv[]){
	FILE* input;
	char* archivo;
	char* clave;
	if (argc > 1){		
		archivo = buscarArchivo(argv[2]);
		input = fopen(archivo,"r"); 
		clave = argv[1];
	}else{
		printf("ingresa la ruta del archivo nabo!\n");
		return ERROR;
	}	
	Encriptador encriptador;
	encriptador_crear(&encriptador,clave);
	encriptador_encriptar(&encriptador,input);	
//	size_t datosEncriptados =
	encriptador_get_datos(&encriptador);
//	printf("%zu\n",datosEncriptados);
	encriptador_destroy(&encriptador);
	fclose(input);
	return SUCCESS;
}


char* buscarArchivo(char* argv){
	return argv;
}

