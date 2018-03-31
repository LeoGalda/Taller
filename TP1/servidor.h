#ifndef __SERVIDOR_H__
#define __SERVIDOR_H__

typedef struct Servidort{
	char *key;
	char *puerto;
	int skt;
} Servidor;

struct addrinfo hints,*ptr;   	

void servidor_create(Servidor *this,char *key,char *puerto);

int servidor_configurar(Servidor *this);

int servidor_conectar(Servidor *this);

#endif