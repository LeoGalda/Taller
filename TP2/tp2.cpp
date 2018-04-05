#include <fstream>
#include <iostream>
#include <cstdlib>
#include "Paquete.h"
#include "Empaquetador.h"

using namespace std;

Paquete* procesarLinea(string linea){
	Paquete *config;
	config = new Paquete();
	string substring;
	size_t inicio = 0;
	size_t siguiente = linea.find("=");
	substring = linea.substr(inicio,siguiente-inicio);
	int id = atoi(substring.c_str());	
	if(id != 0){
		config->setId(id);	
		inicio = siguiente + 1;	
		siguiente = linea.find(",");
		string nombre = linea.substr(inicio,siguiente-inicio);
		config->setNombre(nombre);
		inicio = siguiente + 1;	
		int limite = atoi(linea.substr(inicio).c_str());
		config->setLimite(limite);
	}
	return config;
}

void leerConfiguracion(char *arch,vector<Paquete*> *empaquetador){
	ifstream archivo(arch); 
	char input[128];	
	while(!archivo.eof()){			
		archivo.getline(input,sizeof(input));
		string linea = input;
		if(!linea.empty()){		
			empaquetador->push_back(procesarLinea(linea));
		}
	}
	archivo.close();
}

void limpiarEmpaquetador(vector<Paquete*> *empaquetador){
	for (size_t i = 0; i < empaquetador->size(); ++i) {		
    	delete (*empaquetador)[i]; 	
	}
	empaquetador->clear();
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
			empaquetador->push_back(procesarLinea(linea));
		}
	}
}

int main (int argc,char *argv[]){		
	if (argc < 3){
		printf("Pelotudo");
		return 1;
	}
	vector<Paquete*> empaquetador;
	leerConfiguracion(argv[1],&empaquetador);	
	for(int j = 2; j < argc; j++){
		parsearArchivo(argv[2],&empaquetador);
	}
	limpiarEmpaquetador(&empaquetador);
	return 0;
}