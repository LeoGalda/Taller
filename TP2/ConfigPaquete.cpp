#include "ConfigPaquete.h"
#include <cstdio>

ConfigPaquete::ConfigPaquete(){
	this->id = 0;
	this->nombre = "";
	this->limite = 0;
}

unsigned short ConfigPaquete::getId(){
	return this->id;
}

void ConfigPaquete::setId(unsigned short id){
	this->id = id;
}

string ConfigPaquete::getNombre(){
	return this->nombre;
}

void ConfigPaquete::setNombre(string nombre){
	this->nombre = nombre;
}

unsigned int ConfigPaquete::getLimite(){
	return this->limite;
}

void ConfigPaquete::setLimite(unsigned int limite){
	this->limite = limite;
}

ConfigPaquete::~ConfigPaquete(){
}
