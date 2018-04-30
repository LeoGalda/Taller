#include "common_File.h"
#include "common_ExcpError.h"

File::File(char *arch, std::ios_base::openmode modo) : nombreArchivo(arch), modo(modo) {
    this->archivo.open(this->nombreArchivo, modo);
    if (this->archivo.fail()) {
        int linea = -1;
        std::string error = "Error al abrir archivo de ejecucion PUSH";
        throw new ExcpError(error, linea);
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

char* File::leer(int cantidad){
    char *buffer = new char [cantidad];
    this->archivo.read(buffer,cantidad);  
    return buffer;
}

File::~File() {
    this->archivo.close();
}

