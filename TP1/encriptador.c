#include "encriptador.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

#define SUCCESS 0
#define ERROR 1

unsigned char encriptarDato(unsigned char key_stream,unsigned char unCaracter);

void agregarDatoEncriptadoAlEncriptador(Encriptador *this, 
										unsigned char datoEncriptado, unsigned char key_stream);

unsigned char fasePRGA(Encriptador *this,int *prgaI, int *prgaJ);

void encriptador_crear(Encriptador *this,char *clave) {
	this->inicio = NULL;
	this->fin = NULL;
	this->tamanio = 0;	
	this->key = clave;
}

void encriptador_encriptar(Encriptador *this, FILE *datosAEncriptar,
							int cantidad,int *prgaI, int *prgaJ){
	char unCaracter;
	unsigned char key_stream;
	unsigned char datoEncriptado;
	for(int c = 0; (c < cantidad) && 
		((unCaracter = getc(datosAEncriptar)) != EOF); c++){			
			key_stream = fasePRGA(this, prgaI, prgaJ);		
			datoEncriptado = encriptarDato(key_stream,unCaracter);
			agregarDatoEncriptadoAlEncriptador(this, datoEncriptado,
											   key_stream);	
	}
}

void encriptador_desencriptar(Encriptador *this,
							  unsigned char *datosAEncriptar,
							  int cantidad,int *prgaI, int *prgaJ){
	unsigned char unCaracter;
	unsigned char key_stream;
	unsigned char datoEncriptado;
	for(int c = 0; c < cantidad; c++){
		unCaracter = *datosAEncriptar;
		key_stream = fasePRGA(this, prgaI, prgaJ);		
		datoEncriptado = encriptarDato(key_stream,unCaracter);
		agregarDatoEncriptadoAlEncriptador(this, datoEncriptado, key_stream);
		datosAEncriptar++;
	}
}

void encriptador_guardar_en_salida(Encriptador *this, FILE *archivoSalida){	
	int datoEncriptado;
	Elemento *elemento = this->inicio;	
	while (elemento != NULL){		
		datoEncriptado = elemento->dato;		
		putc(datoEncriptado,archivoSalida);
		elemento = elemento->siguiente;
	}	
}


void encriptador_salida_estandar(Encriptador *this){
	Elemento *unElemento = this->inicio;	
	while (unElemento != NULL){
		fprintf(stdout,"%02x",unElemento->dato);		
		unElemento = unElemento->siguiente;		
	}
}

void encriptador_salida_errores(Encriptador *this){
	Elemento *unElemento = this->inicio;		
	while (unElemento != NULL){
		fprintf(stderr,"%02X",unElemento->keyStream);
		unElemento = unElemento->siguiente;
	}
}

void encriptador_destroy(Encriptador *this){
	Elemento *unElemento;	
	while (this->inicio != NULL){
		unElemento = this->inicio;
		this->inicio = this->inicio->siguiente;
		free(unElemento);	
	}
}

unsigned char encriptarDato(unsigned char key_stream,unsigned char unCaracter){
    return key_stream ^ unCaracter;
}    

void agregarDatoEncriptadoAlEncriptador(Encriptador *this, 
										unsigned char datoEncriptado,
										 unsigned char key_stream){
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

void encriptador_fase_KSA(Encriptador *this){
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

unsigned char fasePRGA(Encriptador *this,int *prgaI, int *prgaJ){		
	unsigned char k;
	*prgaI = (*prgaI + 1) & 255;
	*prgaJ = (*prgaJ + this->arrayDeEstados[*prgaI]) & 255;
	intercambiar(this->arrayDeEstados,*prgaI,*prgaJ);
	k = this->arrayDeEstados[(this->arrayDeEstados[*prgaI] + 
							  this->arrayDeEstados[*prgaJ]) & 255];
	return k;
}
