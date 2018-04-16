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
     char *entrada;
public:
    
//constructor del Configurador    
    Configurador();

//constructor del Configurador que recibe la direccion del 
//archivo que va a abrir    
    Configurador(char *entrada);   
    
//lee los archivos config y por cada uno crea un paquete y lo guarda en 
//en empaquetador    
    void leerConfiguracion(Empaquetador *empaquetador);
    
//consulta si el archivo se encuentra en el fin del archivo    
    bool estaFin();    
    
//destructor del configurador, el cual cierra el archivo    
    ~Configurador();

};

#endif 

