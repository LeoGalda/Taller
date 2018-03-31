#ifndef __CLIENTE_H__
#define __CLIENTE_H__

typedef struct Clientet{
	char *key;
	char *puerto;
	char *ip;
	int skt;
} Cliente;

struct addrinfo hints,*ptr;   	

void cliente_create(Cliente *this, char *key, char *puerto, char* ip);

int cliente_configurar(Cliente *this);

int cliente_conectar(Cliente *this);

#endif