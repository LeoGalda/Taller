#ifndef COMMON_FILE_H
#define COMMON_FILE_H

#include <fstream>
#include <string>
#include <iostream>

class File {
private:      
    std::string nombreArchivo;
    std::ios_base::openmode modo;
    std::fstream archivo;   
    
public:
//constructor del File y abre el archivo pasado por parametro en el 
//modo que se le paso tambien por parametro    
    File(char *nombre, std::ios_base::openmode modo);

//devuelve el nombre del Archivo    
    std::string getNombreArchivo() const;
    
//devuelve el tamanio del archivo    
    int getTamanioArch();

//devuelve el tamanio del nombre del archivo    
    int getTamanioNombre();

//realiza una lectura de la cantidad pasada por parametro    
    void leer(char *buf,int cantidad);

////escribe en el archivo la data pasada por parametro    
//    void escribir(const std::string data);    
    
//devuelve una linea del archivo    
    void getLinea(std::string &linea);
    
//devuelve true si el archivo se encuentra en el final o false en caso contrario
    bool estaFin();

//escribe en el archivo la data pasada por parametro        
    void operator<<(const std::string data);
    
//llama al destructor del file    
    virtual ~File();
};

#endif 

