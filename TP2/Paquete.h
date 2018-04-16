#ifndef PAQUETE_H
#define PAQUETE_H

#include <iostream>
#include <string>
#include <vector>

class Paquete {
protected:	
	unsigned int id;
	std::string nombre;
	unsigned int limite;
	unsigned int cantidad;
	std::vector<unsigned int> ancho;	

public:
	Paquete();
	Paquete(unsigned int id, const std::string &nombre, unsigned int limite);
	unsigned int getId();
	void setId(unsigned int id);
	std::string getNombre();
	void setNombre(const std::string &nombre);
	unsigned int getLimite();
	void setLimite(unsigned int limite);	
	unsigned int getCantidad();
	void setCantidad(unsigned int cantidad);
	void addAncho(unsigned int ancho);
        void addAnchos(unsigned int ancho,unsigned int cantidad);
	void limpiarAnchos();
	std::vector<unsigned int> getAnchos();
        int calcularMediana();
	~Paquete();
};

#endif
