#ifndef ConfigPaquete_H
#define ConfigPaquete_H

#include <iostream>
#include <string>

using namespace std;

class ConfigPaquete {
private:	
	unsigned short id;
	string nombre;
	unsigned int limite;

public:
	ConfigPaquete();
	unsigned short getId();
	void setId(unsigned short id);
	string getNombre();
	void setNombre(string nombre);
	unsigned int getLimite();
	void setLimite(unsigned int limite);
	~ConfigPaquete();
};



#endif