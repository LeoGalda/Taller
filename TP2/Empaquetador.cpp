#include "Empaquetador.h"
#include <cstdio>
#include <string.h>

Empaquetador::Empaquetador(){
}

Empaquetador::~Empaquetador(){
	for (size_t i = 0; i < empaquetador.size(); ++i) {
    	delete empaquetador[i];
	}
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

Paquete* Empaquetador::getPaquetePorTipo(int tipo){
	Paquete *paquete;
	for(size_t i = 0; i < this->getTamanio(); i++){		
		if((int)(this->getPaquete(i)->getId()) == tipo){
			return this->getPaquete(i);
		}
	}
	paquete = NULL;	
	return paquete;
}

void Empaquetador::mostrarRemanentes(){
	cout<<"# Informe de remanentes\n";
	for(size_t i = 0; i < this->getTamanio(); i++){		
		printf("* %i tornillos de tipo %s\n",
				this->getPaquete(i)->getCantidad(),
				this->getPaquete(i)->getNombre().c_str());
	}
}
