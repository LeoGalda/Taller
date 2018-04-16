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
    Empaquetador();
    ~Empaquetador();
    void agregarPaquete(Paquete *paquete);
    size_t getTamanio();
    Paquete* getPaquete(unsigned int posicion);
    Paquete* getPaquetePorTipo(unsigned int tipo);
    int existeTornillo(unsigned int tipo);
    void mostrarRemanentes();
    void actualizarDatos(unsigned int tipo, unsigned int cant, 
        unsigned int ancho);
};

#endif
