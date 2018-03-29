#include <stdio.h>
#include "encriptador.h"

#define SUCCESS 0
#define ERROR 1

char* buscarArchivo(char* argumento);

int main(int argc, char* argv[]){


//cliente	
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
	encriptador_crear(&encriptador, clave);
	encriptador_encriptar(&encriptador,input);	
	encriptador_salida_estandar(&encriptador);
	encriptador_salida_errores(&encriptador);

	fclose(input);


//servidor
	FILE * salida = fopen ("./out", "w+");
	Encriptador desencriptador;		
	desencriptador = encriptador;
	encriptador_desencriptar(&desencriptador,salida);
	fclose(salida);
	encriptador_destroy(&encriptador);
	return SUCCESS;
}


char* buscarArchivo(char* argv){
	return argv;
}

