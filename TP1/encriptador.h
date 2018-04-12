#ifndef __ENCRIPTADOR_H__
#define __ENCRIPTADOR_H__

#include <string.h>
#include <stdio.h>

typedef struct ElementoEncriptador{
	unsigned char dato;
	unsigned char keyStream;
	struct ElementoEncriptador *siguiente;
} Elemento;

typedef struct EncriptadorLista{
	Elemento *inicio;
	Elemento *fin;
	int tamanio;
	char *key;
	char arrayDeEstados[256];
} Encriptador;


// inicializa la instancia this para ser utilizada
void encriptador_crear(Encriptador *this,char *key);

// Encripta los datos que se encuentran en el archivo datosAEncriptar
// o hasta el limite pasado en la variable cantidad y los guarda en la 
// instancia this (usado por el cliente)
void encriptador_encriptar(Encriptador *this, FILE *datosAEncriptar, 
							int cantidad,int *prgaI, int *prgaJ);

// Encripta los datos que se encuentran en el archivo datosAEncriptar
// o hasta el limite pasado en la variable cantidad y los guarda en la 
// instancia this (usado por el servidor)
void encriptador_desencriptar(Encriptador *this,
							  unsigned char *datosAEncriptar,
 							  int cantidad,int *prgaI, int *prgaJ);

//guarda en el archivo de salida los datos que se encuentran en la 
//instancia this
void encriptador_guardar_en_salida(Encriptador *this, FILE *archivoSalida);

//imprime por salida estandar los datos que se encuentran en la instancia this
void encriptador_salida_estandar(Encriptador *this);

//imprime por salida error los datos que se encuentran en la instancia this
void encriptador_salida_errores(Encriptador *this);

// Destruyo la instancia this para liberar sus recursos
void encriptador_destroy(Encriptador *this);

//realiza la fase KSA y modifica el arrayDeEstado de la instancia this
void encriptador_fase_KSA(Encriptador *this);

#endif
