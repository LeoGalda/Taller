#include <fstream>
#include <iostream>
#include <math.h>
#include <exception>
#include "server.h"
#include "common_ExcpError.h"

Server::Server() {
}

Server::Server(char *puerto, char *arch): socket(puerto,NULL),ruta(arch){
    this->indice.open(arch);
    if(this->indice.fail()){
//        ExcpError exp();
        int linea = 5;
        std::string error = "NOOOO!!!! LA PUTA QUE TE PARIO";
        throw new ExcpError(error,linea);
    }
}

Server::~Server() {
    this->indice.close();
}

