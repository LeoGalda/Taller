#include "common_File.h"
//#include "common_ExcpError.h"
#include <string>
#include <exception>
#include <stdexcept>

File::File(char *arch, std::ios_base::openmode modo) : nombreArchivo(arch),
                                                       modo(modo) {
    this->archivo.open(this->nombreArchivo, modo);
    if (this->archivo.fail()) {
        throw std::runtime_error("Error: archivo inexistente.");
    }
}

std::string File::getNombreArchivo() const {
    return this->nombreArchivo;
}

int File::getTamanioArch() {
    this->archivo.seekg(0, this->archivo.end);
    int length = this->archivo.tellg();    
    this->archivo.seekg(0, this->archivo.beg);    
    return length;
}

int File::getTamanioNombre() {
    return this->nombreArchivo.size();
}

void File::leer(char* buffer,int cantidad){    
    this->archivo.read(buffer,cantidad);      
}

void File::operator <<(const std::string data){
    this->archivo << data;
}


void File::getLinea(std::string &linea){
    std::getline(this->archivo,linea);
}

bool File::estaFin(){
    return this->archivo.eof();
}

File::~File() {
    this->archivo.close();
}

