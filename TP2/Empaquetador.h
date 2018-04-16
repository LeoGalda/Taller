#ifndef EMPAQUETADOR_H
#define EMPAQUETADOR_H

#include <vector>
#include "Paquete.h"
#include <mutex>

class Empaquetador {
private:
    std::vector<Paquete*> empaquetador;
    std::mutex mute;
    
public:
//constructor del Empaquetador
    Empaquetador();
//destruye los paquetes contenidos en el empaquetador para liberar los recursos
    ~Empaquetador();
    
//agrega un paquete al empaquetador    
    void agregarPaquete(Paquete *paquete);   
    size_t getTamanio();
    Paquete* getPaquete(unsigned int posicion);
    
//busca el paquete en el empaquetador que tenga como id el tipo de     
//tornillo pasado por parametro y devuelve el paquete encontrado o     
//una referencia a null en caso de no encontrar    
    Paquete* getPaquetePorTipo(unsigned int tipo);
    
//devuelve true si existe el tipo de tornillo en el empaquetador
// false en caso contrario    
    int existeTornillo(unsigned int tipo);
    
//muestra por salida estandar los remanentes    
    void mostrarRemanentes();
    
//actualiza los datos del empaquetador, recibe por parametro los valores
//leidos del archivo y verifica si se llego a completar el limite de un paquete
// y lo muestra por pantalla y sino actualiza los datos    
    void actualizarDatos(unsigned int tipo, unsigned int cant, 
        unsigned int ancho);
};

#endif
