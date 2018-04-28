#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#include "common_Socket.h"

Socket::Socket() {
}

int Socket::doBind(char *puerto) {
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

int Socket::doListen() {
    int status = listen(this->fd, 1);
    if (status == -1) {
        printf("Error: %s\n", strerror(errno));
        return 1;
    }
    return 0;
}

int Socket::conectar(char *puerto, char *ip) {
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
            status = connect(this->fd, aux->ai_addr, aux->ai_addrlen);
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

void Socket::aceptar(Socket *peerskt) {
    peerskt->fd = accept(this->fd, NULL, NULL);
}

int Socket::enviarDatos(FormatoComu *formato) {
    int bytesEnviados = 0;
    bool errorDelSocket = false, socketCerrado = false;
    int status;
    int usado = formato->getTamanio();
    printf("usado: %i\n", usado);
    printf("enviado:\n");
    while (bytesEnviados < usado && errorDelSocket == false &&
            socketCerrado == false) {
        unsigned int *putazo = formato->getDataEnPos(bytesEnviados);
        //        status = send(this->fd, putazo, usado - bytesEnviados, MSG_NOSIGNAL);
        status = send(this->fd, putazo, 100, MSG_NOSIGNAL);
        printf("putazo:\n");
        for (int i = 0; i < usado - bytesEnviados; i++) {
            printf("%02x-", putazo[i]);
        }
        if (status < 0) {
            printf("Error enviar cliente datos: %s\n", strerror(errno));
            errorDelSocket = true;
        } else if (status == 0) {
            socketCerrado = true;
        } else {
            //            bytesEnviados += status;
            bytesEnviados += 100;
        }
    }
    if (socketCerrado || errorDelSocket) {
        return 1;
    }
    return 0;
}

int Socket::recibirDatos(Buffer *buffer) {
    buffer->setUsado(0);
    int tamanio = buffer->getTamanio();
    int s = 0;
    bool socketValido = true;
    printf("puto tamanio: %i\n", tamanio);
    while (buffer->getUsado() < tamanio && socketValido) {
        printf("puto uso: %i\n", buffer->getUsado());
        unsigned int *sarasa = buffer->getData(buffer->getUsado());
        s = recv(this->fd, sarasa, tamanio - buffer->getUsado(), 0);
        if (s > 0) {
            buffer->setUsado(buffer->getUsado() + s);
        } else {
            socketValido = false;
        }
    }
    printf("\nrecibido:\n");
    for (int i = 0; i < buffer->getUsado(); i++) {
        printf("%02x-", buffer->getDataEnPos(i));
    }

    if (socketValido) {
        return 1;
    }
    return 0;
}

int Socket::getFD() {
    return this->fd;
}

Socket::~Socket() {
    //    freeaddrinfo(this->ptr);
    //    shutdown(this->sock, SHUT_RDWR);
    //    close(this->sock);
}
