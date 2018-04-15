#ifndef MANEJADORARCH_H
#define MANEJADORARCH_H

#include <fstream>
#include <iostream>
#include <string>
#include "Paquete.h"
#include "Empaquetador.h"

class ManejadorArch {
private:
    std::ifstream archivo;    
    
public:
    ManejadorArch();   
    ManejadorArch(char *arch);
    bool estaFin();    
    void leerConfiguracion(Empaquetador *empaquetador,char *entrada);
    Paquete* procesarLinea(const std::string linea);
    std::ifstream getArchivo();
    void parsearArchivo(Empaquetador *empaquetador,char *entrada);
    ~ManejadorArch();
};

#endif 

