#ifndef __ENCRIPTADOR_H__
#define __ENCRIPTADOR_H__

#include <string.h>
#include <stdio.h>
#include "servidor.h"
#include "cliente.h"

typedef struct {
    char *key;
    char arrayDeEstados[256];
    int prgaI;
    int prgaJ;
} Encriptador;


// inicializa la instancia this para ser utilizada
void encriptador_crear(Encriptador * this, char *key);

// Encripta los datos que se encuentran en el buffer del cliente
// y realiza las salidas (usado por el cliente)
void encriptador_encriptar(Encriptador * this, Cliente *cliente);

// Encripta los datos que se encuentran en el buffer del servidor
// y realiza las salidas (usado por el servidor)
void encriptador_desencriptar(Encriptador * this, Servidor *servidor);

// Destruyo la instancia this para liberar sus recursos
void encriptador_destroy(Encriptador * this);

//realiza la fase KSA y modifica el arrayDeEstado de la instancia this
void encriptador_fase_KSA(Encriptador * this);

#endif
