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
	encriptador_t datos;
	encriptador_crear(&datos);
	encriptador_encriptar(&datos,archivo);	
	size_t datosEncriptados = encriptador_get_datos(&datos);
	printf("%zu\n",datosEncriptados);
	encriptador_destroy(&datos);
	fclose(archivo);
	return SUCCESS;
}



