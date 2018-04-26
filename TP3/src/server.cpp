#include <fstream>
#include <iostream>
#include <math.h>
#include <exception>
#include "server.h"
#include "common_ExcpError.h"

Server::Server(char *puerto, char *arch) : ruta(arch), buffer(RESPONSE_MAX_LEN){
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
            corriendo = peerskt.recibirDatos(&this->buffer);            
        }
    }        
}

Server::~Server() {
    this->indice.close();
}

