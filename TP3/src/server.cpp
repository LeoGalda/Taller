#include <fstream>
#include <iostream>
#include <math.h>
#include <exception>
#include "server.h"
#include "common_ExcpError.h"

Server::Server(char *puerto, char *arch) : socket(puerto, NULL), ruta(arch),
                                           buffer(RESPONSE_MAX_LEN){
    this->indice.open(arch);
    if (this->indice.fail()) {
        int linea = 5;
        std::string error = "NOOOO!!!! LA PUTA QUE TE PARIO";
        throw new ExcpError(error, linea);
    }
}

void Server::recibirDatos() {
    bool corriendo = true;
    if (this->socket.configurar(1)) return;
    if (this->socket.conectar(1)) return;
    this->socket.aceptar();
    while (corriendo) {
        if (this->socket.getPeerskt() == -1) {
            throw -1;            
            corriendo = false;
        } else {
            corriendo = this->socket.recibirDatos(&this->buffer);                    
        }
    }
    return;
}

Server::~Server() {
    this->indice.close();
}

