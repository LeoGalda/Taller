#include <fstream>
#include <iostream>
#include <math.h>
#include <exception>
#include <stdio.h>
#include <string.h>
#include "server.h"
#include "common_ExcpError.h"

Server::Server(char *puerto, char *arch) : ruta(arch), buffer(RESPONSE_MAX_LEN) {
    this->indice.open(arch);
    if (this->indice.fail()) {
        int linea = 5;
        std::string error = "NOOOO!!!! LA PUTA QUE TE PARIO";
        throw new ExcpError(error, linea);
    }
    this->socket.doBind(puerto);
    this->socket.doListen();
}

void Server::aceptarClientes() {
    Socket peerskt;
    this->socket.aceptar(&peerskt);
    int corriendo = 1;
    while (corriendo) {
        if (this->socket.getFD() == -1) {
            printf("Error: PUTO EN SOCKET\n");
            corriendo = 0;
        } else {
            unsigned char tipo = 0;
            corriendo = peerskt.recibirDatos(&tipo, 1);
            if (!corriendo) {
                std::cout << "changles" << std::endl;
                return;
            }
            unsigned char longitud[4];
            corriendo = peerskt.recibirDatos(&longitud[0], 4);
            if (!corriendo) {
                std::cout << "chanfles" << std::endl;
                return;
            }
            int size;
            memcpy(&size, &longitud, sizeof (size));
            Buffer buffer(htonl(size));
            corriendo = peerskt.recibirDatos(buffer.getData(), buffer.getTamanio());
            //----------------------------------------------------------
            unsigned char longitud2[4];
            corriendo = peerskt.recibirDatos(&longitud2[0], 4);
            if (!corriendo) {
                std::cout << "chanfles" << std::endl;
                return;
            }
            int size2;
            memcpy(&size2, &longitud2, sizeof (size2));
            Buffer buffer2(htonl(size2));
            corriendo = peerskt.recibirDatos(buffer2.getData(), buffer2.getTamanio());            
            if (corriendo) {
                printf("a correr\n");
                unsigned char respuesta = 1;
                corriendo = peerskt.enviarDatos(&respuesta,1);
                corriendo = false;
            }     
            printf("\n");
        }
    }
}

Server::~Server() {
    this->indice.close();
}

