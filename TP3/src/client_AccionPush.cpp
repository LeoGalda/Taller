#include "client_AccionPush.h"
#include "common_ExcpError.h"
#include <iostream>

AccionPush::AccionPush(char *arch, char *hash): hash(hash),nombreArchivo(arch){
    this->archivo.open(arch);
    if(this->archivo.fail()){
        int linea = -1;
        std::string error = "Error al abrir archivo de ejecucion PUSH";
        throw new ExcpError(error,linea);
    }
}

void AccionPush::ejecutar(){
    std::cout<<"ejecutando push push push"<<std::endl;
}

int AccionPush::getValorNumerico(){
    return 1;
}

AccionPush::~AccionPush() {
    this->archivo.close();
}

