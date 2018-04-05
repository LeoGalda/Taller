#include "Empaquetador.h"
#include <cstdio>

Empaquetador::Empaquetador(){
	empaquetador.clear();
}

Empaquetador::~Empaquetador(){
	for (size_t i = 0; i < empaquetador.size(); ++i) {
    	delete empaquetador[i];
	}
	empaquetador.clear();
}

void Empaquetador::agregarPaquete(Paquete *unPaquete){	
	this->empaquetador.push_back(unPaquete);			
}

Paquete* Empaquetador::getPaquete(int posicion){	
		return this->empaquetador[posicion];	
}

size_t Empaquetador::getTamanio(){
	return this->empaquetador.size();
}

void Empaquetador::destruir(){
    for (size_t i = 0; i < empaquetador.size(); ++i) {
    	delete empaquetador[i];
	}
	empaquetador.clear();
}

