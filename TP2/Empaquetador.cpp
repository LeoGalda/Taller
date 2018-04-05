#include "Empaquetador.h"
#include <cstdio>

Empaquetador::Empaquetador(){
}

Empaquetador::~Empaquetador(){
	for(auto unPaquete : empaquetador){
		 delete unPaquete;
	}	
	this->empaquetador.clear();
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

