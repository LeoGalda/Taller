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
    File(char *nombre, std::ios_base::openmode modo);
    std::string getNombreArchivo() const;
    int getTamanioArch();
    int getTamanioNombre();
    virtual ~File();


};

#endif 

