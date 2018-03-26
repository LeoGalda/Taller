#include "encriptador.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

#define SUCCESS 0
#define ERROR 1

int encriptarDato(unsigned char key_stream,char unCaracter);
void agregarDatoEncriptadoAlEncriptador(Encriptador *this, int datoEncriptado, int key_stream);
void faseKSA(Encriptador *this);
unsigned char fasePRGA(Encriptador *this);
int prgaI = 0;
int prgaJ = 0;

void encriptador_crear(Encriptador *this,char *clave) {
	this->inicio = NULL;
	this->fin = NULL;
	this->tamanio = 0;	
	this->key = clave;
}

void encriptador_encriptar(Encriptador *this, FILE *datosAEncriptar) {
	char unCaracter = getc(datosAEncriptar);
	unsigned char key_stream;
	int datoEncriptado;
	faseKSA(this);	
	while (unCaracter != EOF) {
		key_stream = fasePRGA(this);
		datoEncriptado = encriptarDato(key_stream,unCaracter);
		printf("encriptando: %02x\n",datoEncriptado);
		agregarDatoEncriptadoAlEncriptador(this, datoEncriptado,key_stream);
		unCaracter = getc(datosAEncriptar);
	}
}


void encriptador_get_datos(Encriptador *this){
	Elemento *unElemento = this->inicio;
	while (unElemento != NULL){
		printf("elemento: %02x\n",unElemento->dato);
		printf("key: %02X\n",unElemento->keyStream);
		unElemento = unElemento->siguiente;
	}
//	return this->datos;
}


void encriptador_destroy(Encriptador *this){
	//nada para destruir
}

int encriptarDato(unsigned char key_stream, char unCaracter){	
    return key_stream ^ unCaracter;
}    

void agregarDatoEncriptadoAlEncriptador(Encriptador *this, int datoEncriptado, int key_stream){
    Elemento *unElemento;
    unElemento = (Elemento *) malloc(sizeof(Elemento));
    unElemento->dato = datoEncriptado;
    unElemento->keyStream = key_stream;
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

void intercambiar(char *s, int i, int j){
	char auxiliar = s[i];
	s[i] = s[j];
	s[j] = auxiliar;
}

void faseKSA(Encriptador *this){
	int tamanio = strlen((char*) this->key);
	int i,j;
	for(i = 0; i < 256; i++){
		this->arrayDeEstados[i] = i;
	}
	j = 0;
	for(i = 0; i < 256; i++){		
		j = (j + this->arrayDeEstados[i] + this->key[i % tamanio]) & 255;
		intercambiar(this->arrayDeEstados,i,j);	
	}
}

unsigned char fasePRGA(Encriptador *this){		
	unsigned char k;
	prgaI = (prgaI + 1) & 255;
	prgaJ = (prgaJ + this->arrayDeEstados[prgaI]) & 255;
	intercambiar(this->arrayDeEstados,prgaI,prgaJ);
	k = this->arrayDeEstados[(this->arrayDeEstados[prgaI] + this->arrayDeEstados[prgaJ]) & 255];
	return k;
}