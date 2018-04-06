#ifndef PAQUETE_H
#define PAQUETE_H

#include <iostream>
#include <string>

using namespace std;

class Paquete {
protected:	
	unsigned short id;
	string nombre;
	unsigned int limite;
	unsigned int cantidad;
	unsigned int ancho;

public:
	Paquete(unsigned short id, const string &nombre, unsigned int limite);
	unsigned short getId();
	void setId(unsigned short id);
	string getNombre();
	void setNombre(const string &nombre);
	unsigned int getLimite();
	void setLimite(unsigned int limite);	
	unsigned int getCantidad();
	void setCantidad(unsigned int cantidad);
	unsigned int getAncho();
	void setAncho(unsigned int ancho);
	~Paquete();
};



#endif