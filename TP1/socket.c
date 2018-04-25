#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "socket.h"

void socket_crear(Socket *this) {

}

int socket_bind(Socket *this, char *puerto) {
    int status;
    bool conectado = false;
    struct addrinfo hints;
    struct addrinfo *ptr, *aux;
    memset(&hints, 0, sizeof (struct addrinfo));
    hints.ai_family = AF_INET; /* IPv4 */
    hints.ai_socktype = SOCK_STREAM; /* TCP */
    hints.ai_flags = 0;
    status = getaddrinfo(0, puerto, &hints, &ptr);
    if (status != 0) {
        freeaddrinfo(ptr);
        printf("Error in getaddrinfo: %s\n", gai_strerror(status));
        return 1;
    }
    for (aux = ptr; aux != NULL && conectado == false;
            aux = aux->ai_next) {
        this->fd = socket(aux->ai_family, aux->ai_socktype, aux->ai_protocol);
        if (this->fd == -1) {
            freeaddrinfo(ptr);
            printf("Error: %s\n", strerror(errno));
            return 1;
        } else {
            status = bind(this->fd, aux->ai_addr, aux->ai_addrlen);
            if (status == -1) {
                freeaddrinfo(ptr);
                printf("Error: %s\n", strerror(errno));
                return 1;
            }
            conectado = (status != -1);
        }
    }
    freeaddrinfo(ptr);
    if (!conectado) return 1;
    return 0;
}

int socket_listen(Socket *this) {
    int status = listen(this->fd, 1);
    if (status == -1) {
        printf("Error: %s\n", strerror(errno));
        return 1;
    }
    return 0;
}

int socket_conectar(Socket *this, char *puerto, char *ip) {
    bool conectado = false;
    struct addrinfo *aux, *ptr;      
    struct addrinfo hints;
    int status;  
    memset(&hints, 0, sizeof (struct addrinfo));
    hints.ai_family = AF_INET; /* IPv4 */
    hints.ai_socktype = SOCK_STREAM; /* TCP */
    hints.ai_flags = AI_PASSIVE;
    status = getaddrinfo(ip, puerto, &hints, &ptr);
    if (status != 0) {
        printf("Error in getaddrinfo: %s\n", gai_strerror(status));
        return 1;
    }
    for (aux = ptr; aux != NULL && conectado == false;
            aux = aux->ai_next) {
        this->fd = socket(aux->ai_family, aux->ai_socktype, aux->ai_protocol);
        if (this->fd == -1) {
            printf("Error: %s\n", strerror(errno));
            return 1;
        } else {
            status = connect(this->fd, aux->ai_addr, aux->ai_addrlen);
            if (status == -1) {
                printf("Error: %s\n", strerror(errno));
                return 1;
            }
            conectado = (status != -1);
        }
    }
    if (!conectado) return 1;
    return 0;
}

void socket_aceptar(Socket *this, Socket *peerskt) {
    peerskt->fd = accept(this->fd, NULL, NULL);
}

int socket_enviar_datos(Socket *this, Buffer *buffer) {
    int bytesEnviados = 0;
    bool errorDelSocket = false, socketCerrado = false;
    int status;
    while (bytesEnviados < buffer->usado && errorDelSocket == false &&
            socketCerrado == false) {
        status = send(this->fd, &buffer->data[bytesEnviados],
                buffer->usado - bytesEnviados, MSG_NOSIGNAL);
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
        s = recv(this->fd, &buffer->data[buffer->usado],
                buffer->tamanio - buffer->usado, 0);
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
    shutdown(this->fd, SHUT_RDWR);
    close(this->fd);
}
