#include <fstream>
#include <iostream>
#include <math.h>
#include <exception>
#include <stdio.h>
#include <string.h>
#include "server.h"
#include "common_ExcpError.h"
#include "common_File.h"

Server::Server(char *puerto, char *arch) : indice(arch){
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
                std::cout << "chanfles 1" << std::endl;
                return;
            }
            unsigned char longitud[4];
            corriendo = peerskt.recibirDatos(&longitud[0], 4);
            if (!corriendo) {
                std::cout << "chanfles 2" << std::endl;
                return;
            }
            int size;
            memcpy(&size, &longitud, sizeof (size));
            Buffer bufNombreArch(htonl(size));
            corriendo = peerskt.recibirDatos(bufNombreArch.getData(),
                    bufNombreArch.getTamanio());
            //----------------------------------------------------------
            unsigned char longitud2[4];
            corriendo = peerskt.recibirDatos(&longitud2[0], 4);
            if (!corriendo) {
                std::cout << "chanfles 3" << std::endl;
                return;
            }
            int size2;
            memcpy(&size2, &longitud2, sizeof (size2));
            Buffer bufHash(htonl(size2));
            corriendo = peerskt.recibirDatos(bufHash.getData(),
                    bufHash.getTamanio());
            if (!corriendo) {
                std::cout << "chanfles 4" << std::endl;
                return;
            }
            unsigned char respuesta = 1;
            corriendo = peerskt.enviarDatos(&respuesta, 1);
            //---------------------------------------------------------
            unsigned char longitud3[4];
            corriendo = peerskt.recibirDatos(&longitud3[0], 4);
            if (!corriendo) {
                std::cout << "chanfles 6" << std::endl;
                return;
            }
            int size3;
            memcpy(&size3, &longitud3, sizeof (size3));
            size3 = htonl(size3);
            Buffer bufContenidoArch(size3);
            corriendo = peerskt.recibirDatos(bufContenidoArch.getData(),
                    bufContenidoArch.getTamanio());
            File file((char *) bufHash.getData(), std::ofstream::out | std::ofstream::app);
            file.escribir(bufContenidoArch.getData());
        }
    }
}

Server::~Server() {
}

