#ifndef MANEJADORARCH_H
#define MANEJADORARCH_H

#include <fstream>
#include <iostream>
#include <string>
#include "Paquete.h"
#include "Empaquetador.h"
#include "Thread.h"

class ManejadorArch : public Thread  {
private:
    std::ifstream archivo;
    char *ruta;
    Empaquetador *emp;
    
public:
    ManejadorArch();   
    ManejadorArch(char *arch);
    ManejadorArch(Empaquetador *emp,char *arch);
    void run();
    bool estaFin();    
    Paquete* procesarLinea(const std::string linea);
    std::ifstream getArchivo();
    ~ManejadorArch();
};

#endif 

