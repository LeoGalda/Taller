#include "Paquete.h"
#include <cstdio>

Paquete::Paquete(unsigned short id,const string& nombre,
				 unsigned int limite) : id(id),nombre(nombre),
				 limite(limite),cantidad(0),ancho(0){
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

void Paquete::setNombre(const string & nombre){
	this->nombre = nombre;
}

unsigned int Paquete::getLimite(){
	return this->limite;
}

void Paquete::setLimite(unsigned int limite){
	this->limite = limite;
}

unsigned int Paquete::getCantidad(){
	return this->cantidad;
}

void Paquete::setCantidad(unsigned int cantidad){
	this->cantidad = cantidad;
}

unsigned int Paquete::getAncho(){
	return this->ancho;
}

void Paquete::setAncho(unsigned int ancho){
	this->ancho = ancho;
}

Paquete::~Paquete(){
}
