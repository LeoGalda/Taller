#ifndef __CLIENTE_H__
#define __CLIENTE_H__

#include "encriptador.h"
#include <netdb.h>
#include <stdbool.h>

typedef struct{
	char *key;
	char *puerto;
	char *ip;
	int socket;
	struct addrinfo hints;
	struct addrinfo *ptr;
} Cliente;
 	

// Inicializa la instancia this para ser utilizada
void cliente_create(Cliente *this, char *key, char *puerto, char* ip);

// Configura la forma en la que se va a conectar con el socket
int cliente_configurar(Cliente *this);

// Busco en la lista que devuelve getaddrinfo y me conecto con el servidor
int cliente_conectar(Cliente *this);

// Envia datos a traves del socket
int cliente_enviar_datos(Cliente *this, Encriptador *encriptador);

// Destruyo la instancia this para liberar sus recursos
void cliente_destroy(Cliente *this);

// ejecuta el main del cliente
int cliente_ejecutar_cliente(int cantidad,char *ip, char* puerto, 
          char *clave,char *arch);

#endif
