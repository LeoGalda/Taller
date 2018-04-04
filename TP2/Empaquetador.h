#ifndef EMPAQUETADOR_H
#define EMPAQUETADOR_H
#include "Paquete.h"

class Empaquetador {
private:	
	Paquete empaquetador;
	int cantidad;

public:
	Empaquetador();
	~Empaquetador();
	void agregarPaquete(Paquete paquete);		
	Paquete getPaquete(int posicion);
};

#endif