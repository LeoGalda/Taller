#ifndef __SERVIDOR_H__
#define __SERVIDOR_H__

#include <netdb.h>
#include <stdbool.h>
#include "buffer.h"
#include "socket.h"

typedef struct{
    Socket socket;
    Buffer buffer;
    FILE *salida;
    char *key;
} Servidor;

// Inicializa la instancia this para ser utilizada
void servidor_create(Servidor *this, char *puerto, char *key);

// recibe los datos del socket
int servidor_recibir_datos(Servidor *this);

// Destruyo la instancia this para liberar sus recursos
void servidor_destroy(Servidor *this);

#endif
