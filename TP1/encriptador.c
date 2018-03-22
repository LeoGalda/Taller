#include "encriptador.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

#define SUCCESS 0
#define ERROR 1


char EncriptarDato(char unCaracter){
        return toupper(unCaracter);
}


void agregarDatoEncriptadoAlEncriptador(Encriptador *this, char datoEncriptado){
        Elemento *unElemento;
        unElemento = (Elemento *) malloc(sizeof(Elemento));
        unElemento->dato = datoEncriptado;
        unElemento->siguiente = NULL;

        if (this->tamanio > 0){
                 this->fin->siguiente = unElemento;
                 this->fin = unElemento;
        }else{
                this->inicio = unElemento;
                this->fin = unElemento;
        }
        this->tamanio++;
}


void encriptador_create(Encriptador *this) {
	this->inicio = NULL;
	this->fin = NULL;
	this->tamanio = 0;	
}

void encriptador_encriptar(Encriptador *this, FILE *datosAEncriptar) {
	char unCaracter = getc(datosAEncriptar);
	char datoEncriptado;
	while (unCaracter != EOF) {
		datoEncriptado = EncriptarDato(unCaracter);
		agregarDatoEncriptadoAlEncriptador(this, datoEncriptado);
		unCaracter = getc(datosAEncriptar);
	}
}


void encriptador_get_datos(Encriptador *this){
	Elemento *unElemento = this->inicio;
	while (unElemento != NULL){
		printf("%d",unElemento->dato);
		unElemento->siguiente;
	}
//	return this->datos;
}


void encriptador_destroy(Encriptador *this){
	//nada para destruir
}


