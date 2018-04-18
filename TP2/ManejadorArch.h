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
    std::string nombreClasificador;
    
public:    
//constructor del manejador    
    ManejadorArch();   
    
//constructor del manejador recibe un puntero a empaquetador y el archivo
//ademas abre los archivos y los conecta imprimiendo 
//el resultado por pantalla    
    ManejadorArch(Empaquetador *emp,char *arch);
    
//cada thread va a ejecutar este metodo, el cual lee de a 4 bytes el archivo
//y procesa sus binarios y llama al actualizar datos del empaquetador    
    void run();
    
//metodo que pregunta si esta en el fin del archivo    
    bool estaFin();    

//destructor del manejador el cual cierra el archivo y libera los recursos    
    ~ManejadorArch();
};

#endif 

