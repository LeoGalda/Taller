#ifndef EMPAQUETADOR_H
#define EMPAQUETADOR_H

#include <vector>
#include "Paquete.h"

class Empaquetador {
private:
    std::vector<Paquete*> empaquetador;

public:
    Empaquetador();
    ~Empaquetador();
    void agregarPaquete(Paquete *paquete);
    size_t getTamanio();
    Paquete* getPaquete(int posicion);
    Paquete* getPaquetePorTipo(int tipo);
//    int existeTornillo(int tipo);
    void mostrarRemanentes();
};

#endif
