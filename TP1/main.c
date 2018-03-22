#include <stdio.h>
#include "encriptador.h"

#define SUCCESS 0
#define ERROR 1

int main(int argc, char* argv[]){
	FILE* archivo;
	if (argc > 1){
		archivo = fopen(buscarArchivo(&argv),"r"); 
	}else{
		printf("ingresa la ruta del archivo nabo!");
		return ERROR;
	}	
	Encriptador encriptador;
	encriptador_crear(&encriptador);
	encriptador_encriptar(&encriptador,archivo);	
//	size_t datosEncriptados =
	encriptador_get_datos(&encriptador);
//	printf("%zu\n",datosEncriptados);
	encriptador_destroy(&datos);
	fclose(archivo);
	return SUCCESS;
}


FILE buscarArchivo(argv){
	return argv[1];
}

