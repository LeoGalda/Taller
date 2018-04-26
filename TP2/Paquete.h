#ifndef PAQUETE_H
#define PAQUETE_H

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class Paquete {
protected:
    std::string nombre;
    unsigned int limite;
    unsigned int cantidad;
    std::vector<unsigned int> ancho;

public:
    //constructor de paquete
    Paquete();
    //inicializa un Paquete con sus valores     
    Paquete(const std::string &nombre, unsigned int limite);

    //devuelve el valor del atributo nombre    
    std::string getNombre() const;

    //setea el valor del atributo nombre    
    void setNombre(const std::string &nombre);

    //devuelve el valor del atributo limite    
    unsigned int getLimite() const;

    //setea el valor del atributo limite    
    void setLimite(unsigned int limite);

    //devuelve el valor del atributo cantidad    
    unsigned int getCantidad() const;

    //setea el valor del atributo cantidad    
    void setCantidad(unsigned int cantidad);

    //agrega un ancho al vector de ancho    
    void addAncho(unsigned int ancho);

    //agrega una cantidad pasado por parametro al vector de anchos    
    void addAnchos(unsigned int ancho, unsigned int cantidad);

    //Elimina todos los valores del vector ancho
    void limpiarAnchos();

    //devuelve el vector del atributo ancho    
    std::vector<unsigned int> getAnchos() const;

    //calcula la mediana del atributo vector ancho    
    int calcularMediana();
    
    //asignacion por movimiento 
    void swap(Paquete& b);     

    //destructor del paquete el cual elimina todos los anchos
    //y libera sus recursos    
    ~Paquete();
};

#endif
