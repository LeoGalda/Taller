#include <fstream>
#include <iostream>
#include <cstdlib>
#include "Paquete.h"
#include "Empaquetador.h"

using namespace std;

Paquete* procesarLinea(const string &linea){
	string substring;
	size_t inicio = 0;
	size_t siguiente = linea.find("=");
	substring = linea.substr(inicio,siguiente-inicio);
	int id = atoi(substring.c_str());	
	inicio = siguiente + 1;	
	siguiente = linea.find(",");
	string nombre = linea.substr(inicio,siguiente-inicio);
	inicio = siguiente + 1;	
	int limite = atoi(linea.substr(inicio).c_str());
	Paquete* paquete = new Paquete(id,nombre,limite);
	return paquete;
}

void leerConfiguracion(char *arch,Empaquetador &empaquetador){
	ifstream archivo(arch); 
	char input[128];	
	while(!archivo.eof()){			
		archivo.getline(input,sizeof(input));
		string linea = input;
		if(!linea.empty()){		
			empaquetador.agregarPaquete(procesarLinea(linea));
		}		
	}
	archivo.close();
}

void parsearArchivo(char *arch,vector<Paquete*> *empaquetador){
	ifstream ifs;
	ifs.open(arch, std::ifstream::binary);
	unsigned char dato;
	char input[4];	
	while(!archivo.eof()){			
		archivo.getline(input,sizeof(input));
		string linea = input;
		if(!linea.empty()){		
			//empaquetador->push_back(procesarLinea(const &linea));
			empaquetador->agregarPaquete(procesarLinea(const &linea));
		}
	}
}

int main (int argc,char *argv[]){		
	if (argc < 3){
		printf("Pelotudo");
		return 1;
	}
	Empaquetador empaquetador;
	leerConfiguracion(argv[1],empaquetador);	
	for(int j = 2; j < argc; j++){
		parsearArchivo(argv[2],empaquetador);
	}
	return 0;
}