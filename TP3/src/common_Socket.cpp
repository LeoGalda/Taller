#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <arpa/inet.h>
#include <exception>
#include <stdexcept>
#include "common_Socket.h"

#define MAX_CLIENTES_EN_ESPERA 20

Socket::Socket() {
    this->fd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->isOnError()) {
        throw std::runtime_error("error en instanciar socket");
    }
}

Socket::Socket(Socket&& other) {
    this->fd = other.fd;
    other.fd = 0;
}

Socket& Socket::operator=(Socket&& other) {
    if (this == &other) {
        return *this;
    }

    this->fd = other.fd;
    other.fd = 0;

    return *this;
}

int Socket::doBind(char *puerto) {
    int size = 1;
    struct addrinfo hints;
    struct addrinfo *result;
    int status = 0;

    setsockopt(this->fd, SOL_SOCKET, SO_REUSEADDR, &size, sizeof (size));
    memset(&hints, 0, sizeof (struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    status = getaddrinfo(NULL, puerto, &hints, &result);
    if (status == -1) {
        fprintf(stderr, "Error : %s\n", strerror(errno));
        return 1;
    }
    status = bind(this->fd, result->ai_addr, result->ai_addrlen);
    if (status == -1) {
        fprintf(stderr, "Error : %s\n", strerror(errno));
        return 1;
    }
    freeaddrinfo(result);
    return 0;
}

int Socket::doListen() {
    int status = listen(this->fd, MAX_CLIENTES_EN_ESPERA);
    if (status == -1) {
        printf("Error: %s\n", strerror(errno));
        return 1;
    }
    return 0;
}

int Socket::conectar(char* puerto, char* ip) {
    struct sockaddr_in hints;

    hints.sin_family = AF_INET;
    hints.sin_port = htons((uint16_t) atoi(puerto));
    hints.sin_addr.s_addr = inet_addr(ip);
    if (connect(this->fd, (struct sockaddr *) &hints, sizeof (hints)) < 0) {
        printf("Error: %s\n", strerror(errno));
        return 1;
    }
    return 0;
}

void Socket::aceptar(Socket *peerskt) {
    peerskt->fd = accept(this->fd, NULL, NULL);
}

int Socket::enviarDatos(unsigned char *buf, int tamanio) {
    int bytesEnviados = 0;
    bool errorDelSocket = false, socketCerrado = false;
    int status = 0;
//    printf("envio:");
//    for (int i = 0; i < tamanio; i++) {
//        printf("%02x-", buf[i]);
//    }
//    std::cout << std::endl;
    while (bytesEnviados < tamanio && errorDelSocket == false &&
            socketCerrado == false) {
        status = send(this->fd, &buf[bytesEnviados], tamanio - bytesEnviados,
                MSG_NOSIGNAL);
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

int Socket::recibirDatos(unsigned char *buf, int tamanio) {
    int bytesRecibidos = 0;
    int s = 0;
    bool socketValido = true;
    while (bytesRecibidos < tamanio && socketValido) {
        s = recv(this->fd, &buf[bytesRecibidos], tamanio - bytesRecibidos, 0);
        if (s > 0) {
            bytesRecibidos += s;
        } else {
            if (s == -1) {
                //                std::cout << "SOCKET INVALIDO EN RECIBIR DATOS" << std::endl;
                socketValido = false;
            } else {
                //                std::cout << "recibi 0 bytes" << std::endl;
                socketValido = false;
            }
        }
    }
//    printf("recibido:\n");
//    for (int i = 0; i < tamanio; i++) {
//        printf("%02x-", buf[i]);
//    }
//    std::cout << std::endl;
    if (socketValido)
        return bytesRecibidos;
    return 0;
}

int Socket::isOnError() {
    return this->fd == -1;
}

void Socket::destruir() {
    if (!this->isOnError()) {
        shutdown(this->fd, SHUT_RDWR);
        close(this->fd);
    }
}

Socket::~Socket() {
    this->destruir();
}
