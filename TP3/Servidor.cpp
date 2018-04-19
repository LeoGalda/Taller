#include <fstream>
#include <iostream>
#include <math.h>
#include <exception>
#include "Servidor.h"
#include "ExcpError.h"

Servidor::Servidor() {
}

Servidor::Servidor(char *puerto, char *arch): socket(puerto,NULL),ruta(arch){
    this->indice.open(arch);
    if(this->indice.fail()){
//        ExcpError exp();
        int linea = 5;
        std::string error = "NOOOO!!!! LA PUTA QUE TE PARIO";
        throw new ExcpError(error,linea);
    }
}

Servidor::~Servidor() {
    this->indice.close();
}

