#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "socket.h"

void socket_crear(Socket *this, char *puerto, char *ip) {
    this->puerto = puerto;
    this->ip = ip;
}

int socket_configurar(Socket *this, bool soyServidor) {
    int status;
    struct addrinfo hints;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET; /* IPv4 */
    hints.ai_socktype = SOCK_STREAM; /* TCP */
    hints.ai_flags = soyServidor ? 0 : AI_PASSIVE;
    status = getaddrinfo(this->ip, this->puerto, &hints, &this->ptr);
    if (status != 0) {
        printf("Error in getaddrinfo: %s\n", gai_strerror(status));
        return 1;
    }
    return 0;
}

int socket_conectar(Socket *this, bool soyServidor) {
    bool conectado = false;
    struct addrinfo *aux;
    int status;
    for (aux = this->ptr; aux != NULL && conectado == false;
            aux = aux->ai_next) {
        this->sock = socket(aux->ai_family, aux->ai_socktype, aux->ai_protocol);
        if (this->sock == -1) {
            printf("Error: %s\n", strerror(errno));
            return 1;
        } else {
            status = soyServidor
                    ? bind(this->sock, aux->ai_addr, aux->ai_addrlen)
                    : connect(this->sock, aux->ai_addr, aux->ai_addrlen);
            if (status == -1) {
                printf("Error: %s\n", strerror(errno));
                return 1;
            }
            conectado = (status != -1);
        }
    }
    if (!conectado) return 1;
    if (soyServidor) {
        status = listen(this->sock, 1);
        if (status == -1) {
            printf("Error: %s\n", strerror(errno));
            return 1;
        }
    }
    return 0;
}

void socket_aceptar(Socket *this) {
    this->peerskt = accept(this->sock, NULL, NULL);
}

int socket_enviar_datos(Socket *this, Buffer *buffer) {
    int bytesEnviados = 0;
    bool errorDelSocket = false, socketCerrado = false;
    int status;
    while (bytesEnviados < buffer->usado && errorDelSocket == false &&
            socketCerrado == false) {
        status = send(this->sock, &buffer->data[bytesEnviados],
                buffer->usado - bytesEnviados, 0);
        if (status < 0) {
            printf("Error enviar cliente datos: %s\n", strerror(errno));
            errorDelSocket = true;
        } else if (status == 0) {
            socketCerrado = true;
        } else {
            bytesEnviados += status;
        }
    }
    if (socketCerrado || errorDelSocket) {
        return 1;
    }
    return 0;
}

int socket_recibir_datos(Socket *this, Buffer *buffer) {
    buffer->usado = 0;
    int s = 0;
    bool socketValido = true;
    while (buffer->usado < buffer->tamanio && socketValido) {
        s = recv(this->peerskt, &buffer->data[buffer->usado],
                buffer->tamanio - buffer->usado, MSG_NOSIGNAL);
        if (s > 0) {
            buffer->usado += s;
        } else {
            socketValido = false;
        }
    }
    if (socketValido) {
        return 1;
    }
    return 0;
}

void socket_destroy(Socket *this) {
    freeaddrinfo(this->ptr);
    shutdown(this->sock, SHUT_RDWR);
    close(this->sock);
}
