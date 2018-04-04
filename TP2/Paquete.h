#ifndef PAQUETE_H
#define PAQUETE_H

#include <iostream>
#include <string>

using namespace std;

class Paquete {
private:	
	unsigned short id;
	string nombre;
	unsigned int limite;

public:
	Paquete();
	unsigned short getId();
	void setId(unsigned short id);
	string getNombre();
	void setNombre(string nombre);
	unsigned int getLimite();
	void setLimite(unsigned int limite);
	~Paquete();
};



#endif