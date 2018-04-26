#ifndef EMPAQUETADOR_H
#define EMPAQUETADOR_H

#include "Paquete.h"
#include <mutex>
#include <map>

class Empaquetador {
private:
    std::map<int, Paquete*> empaquetador;
    std::mutex mute;
    
public:
//constructor del Empaquetador
    Empaquetador();
//destruye los paquetes contenidos en el empaquetador para liberar los recursos
    ~Empaquetador();
    
//agrega un paquete al empaquetador    
    void agregarPaquete(unsigned int id,const std::string nombre,int limite);   
       
//muestra por salida estandar los remanentes    
    void mostrarRemanentes();
    
//actualiza los datos del empaquetador, recibe por parametro los valores
//leidos del archivo y verifica si se llego a completar el limite de un paquete
// y lo muestra por pantalla y sino actualiza los datos    
    void actualizarDatos(unsigned int tipo, unsigned int cant,
                         unsigned int ancho);
};

#endif
