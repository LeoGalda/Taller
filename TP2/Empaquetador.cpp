#include "Empaquetador.h"
#include <cstdio>

Empaquetador::Empaquetador(){
}

Empaquetador::~Empaquetador(){
	for (size_t i = 0; i < empaquetador.size(); ++i) {
    	delete empaquetador[i];
	}
	empaquetador.clear();
}

void Empaquetador::agregarPaquete(ConfigPaquete *unPaquete){	
	this->empaquetador.push_back(unPaquete);			
}

ConfigPaquete* Empaquetador::getPaquete(int posicion){	
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

