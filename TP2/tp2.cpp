#include <iostream>
#include "Paquete.h"
#include "Empaquetador.h"

int main (int argc,char *argv[]){
	printf("puto");
	Empaquetador empaquetador;
	Paquete paquete;
	for(int i = 1; i < 10; i++){
		paquete = new Paquete();
		paquete.setId(i);
		paquete.setNombre("hola");
		paquete.setLimite(i*3);
		empaquetador.agregarPaquete(paquete);
	}
	for(int i = 0; i < 9; i++){
		paquete = empaquetador.getPaquete(i);
		printf("id: %c y limite: %i\n", paquete.getId(), paquete.getLimite());
	}
}

