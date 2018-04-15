#ifndef CONFIGURADOR_H
#define CONFIGURADOR_H
#include <fstream>
#include <iostream>
#include <string>
#include "Paquete.h"
#include "Empaquetador.h"


class Configurador {
private:
     std::ifstream archivo;     
public:
    Configurador();    
    void leerConfiguracion(Empaquetador *empaquetador,char *entrada);
    bool estaFin();    
    ~Configurador();

};

#endif 

