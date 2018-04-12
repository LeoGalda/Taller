#ifndef __SERVIDOR_H__
#define __SERVIDOR_H__

#include <netdb.h>
#include <stdbool.h>
#include "buffer.h"
#include "socket.h"

typedef struct{
    Socket socket;
    Buffer buffer;
} Servidor;

// Inicializa la instancia this para ser utilizada
void servidor_create(Servidor *this,char *key,char *puerto);

// Configura la forma en la que se va a conectar con el socket
// ademas realiza el bind y el listen
int servidor_configurar(Servidor *this);

// realiza el accept
int servidor_conectar(Servidor *this);

// recibe los datos del socket y retorna la cantidad que se recibio
int servidor_recibir_datos(Servidor *this, int peerskt, unsigned char *buf, 
							int *rec, bool *corriendo);

// Destruyo la instancia this para liberar sus recursos
void servidor_destroy(Servidor *this);

// Ejecuta el main del servidor
int servidor_ejecutar_servidor(char *puerto, char *key);


#endif
