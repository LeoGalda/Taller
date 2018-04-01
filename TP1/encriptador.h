#ifndef __ENCRIPTADOR_H__
#define __ENCRIPTADOR_H__

#include <string.h>
#include <stdio.h>

typedef struct ElementoEncriptador{
	int dato;
	int keyStream;
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
// Pre: this apunta un sector valido de memoria
void encriptador_crear(Encriptador *this,char *key);

void encriptador_encriptar(Encriptador *this, FILE *datos_a_encriptar, int cantidad,
							int *prgaI, int *prgaJ);

void encriptador_desencriptar(Encriptador *this, FILE *archivoSalida);

void encriptador_salida_estandar(Encriptador *this);

void encriptador_salida_errores(Encriptador *this);

void encriptador_destroy(Encriptador *this);

void encriptador_fase_KSA(Encriptador *this);

#endif
