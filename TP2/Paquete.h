#ifndef PAQUETE_H
#define PAQUETE_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Paquete {
protected:	
	unsigned short id;
	string nombre;
	unsigned int limite;
	unsigned int cantidad;
	std::vector<int> ancho;	

public:
	Paquete();
	Paquete(unsigned short id, const string &nombre, unsigned int limite);
	unsigned short getId();
	void setId(unsigned short id);
	string getNombre();
	void setNombre(const string &nombre);
	unsigned int getLimite();
	void setLimite(unsigned int limite);	
	unsigned int getCantidad();
	void setCantidad(unsigned int cantidad);
	void addAncho(int ancho);
	void limpiarAnchos();
	std::vector<int> getAnchos();
	~Paquete();
};



#endif