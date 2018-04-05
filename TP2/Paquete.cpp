#include "Paquete.h"
#include <cstdio>

Paquete::Paquete(){
	this->id = 0;
	this->nombre = "";
	this->limite = 0;
}

unsigned short Paquete::getId(){
	return this->id;
}

void Paquete::setId(unsigned short id){
	this->id = id;
}

string Paquete::getNombre(){
	return this->nombre;
}

void Paquete::setNombre(string nombre){
	this->nombre = nombre;
}

unsigned int Paquete::getLimite(){
	return this->limite;
}

void Paquete::setLimite(unsigned int limite){
	this->limite = limite;
}

Paquete::~Paquete(){
}
