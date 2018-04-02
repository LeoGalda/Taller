#ifndef __SERVIDOR_H__
#define __SERVIDOR_H__

typedef struct Servidort{
	char *key;
	char *puerto;
	int socket;
} Servidor;

struct addrinfo hints,*ptr;   	

void servidor_create(Servidor *this,char *key,char *puerto);

int servidor_configurar(Servidor *this);

int servidor_conectar(Servidor *this);

int servidor_recibir_datos(Servidor *this, int peerskt, int *buf, int *rec);

#endif