#include "Empaquetador.h"
#include <cstdio>

Empaquetador::Empaquetador(){
	this->empaquetador = NULL;
	this->cantidad = 0;
}

Empaquetador::~Empaquetador(){
	delete[] this->empaquetador;
}

Empaquetador::agregarPaquete(Paquete unPaquete){	
	this->paquete[cantidad] = unPaquete;
	this->cantidad++; 
}

Empaquetador::getPaquete(int posicion){
	if (posicion < cantidad){
		return this->paquete[posicion];
	}
	return NULL;
}

