#ifndef __CLIENTE_H__
#define __CLIENTE_H__

#include <netdb.h>
#include "buffer.h"
#include "socket.h"
#include "encriptador.h"
#include <stdbool.h>

typedef struct {
    Socket socket;
    Buffer buffer;
    FILE *entrada;
    Encriptador encriptador;
} Cliente;


// Inicializa la instancia this para ser utilizada
void cliente_create(Cliente * this, char* ip, char *puerto,
        char *key, char* arch);

// Envia datos a traves del socket
int cliente_enviar_datos(Cliente * this);

// Destruyo la instancia this para liberar sus recursos
void cliente_destroy(Cliente * this);

#endif
