#include "encriptador.h"

void encriptador_create(Encriptador *this) {
	this->inicio = NULL;
	this->tamaño = 0;
}

void encriptador_encriptar(Encriptador *this, FILE *datos_a_encriptar) {
	char unCaracter = getc(datos_a_encriptar);
	while (unCaracter != EOF) {
		this->datos = toupper(unCaracter);
		unCaracter = getc(datos_a_encriptar);
		this->datos 
	}
}


size_t encriptador_get_datos(Encriptador *this){
	return this->datos;
}


void encriptador_destroy(Encriptador *this){
	//nada para destruir
}


