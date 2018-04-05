#ifndef EMPAQUETADOR_H
#define EMPAQUETADOR_H

#include <vector>
#include "ConfigPaquete.h"


class Empaquetador {
private:	
	std::vector<ConfigPaquete*> empaquetador;	

public:
	Empaquetador();
	~Empaquetador();
	void agregarPaquete(ConfigPaquete *paquete);
	size_t	getTamanio();	
	ConfigPaquete* getPaquete(int posicion);
	void destruir();
};

#endif