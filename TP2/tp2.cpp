#include <iostream>
#include "Paquete.h"
#include "Empaquetador.h"

int main (int argc,char *argv[]){	
	Empaquetador *empaquetador;
	empaquetador = new Empaquetador();	
	Paquete *paquete;
	for(int i = 1; i < 3; i++){				
		paquete = new Paquete();
		paquete->setId(i);
		paquete->setNombre("hola");
		paquete->setLimite(i*3);				
		empaquetador->agregarPaquete(paquete);	
	}	
	for(size_t j = 0; j < empaquetador->getTamanio(); j++){
		paquete = empaquetador->getPaquete(j);
		printf("id: %X y limite: %i\n", paquete->getId(), paquete->getLimite());
	}
	return 0;
}

