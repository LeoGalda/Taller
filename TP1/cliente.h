#ifndef __CLIENTE_H__
#define __CLIENTE_H__

#include "encriptador.h"

typedef struct Clientet{
	char *key;
	char *puerto;
	char *ip;
	int socket;
} Cliente;

struct addrinfo hints,*ptr;   	

void cliente_create(Cliente *this, char *key, char *puerto, char* ip);

int cliente_configurar(Cliente *this);

int cliente_conectar(Cliente *this);

int cliente_enviar_datos(Cliente *this, Encriptador *encriptador);

#endif